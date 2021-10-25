#include <Arduino.h>

#include <Adafruit_INA219.h>
#include <Adafruit_NeoPixel.h>
#include <Bounce2.h>

/* Button */
#define BUTTON_PIN 2
Bounce button = Bounce();

/* LEDs */
#define NEO_PIN     10
#define ONBOARD_LED 13

#define FULL_BRIGHTNESS 255

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(5, NEO_PIN, NEO_GRB + NEO_KHZ800);

/* current sensor */
Adafruit_INA219 ina219;
float           shuntvoltage;
float           busvoltage;
float           current_mA;
float           loadvoltage;
float           power_mW;

/* states */
typedef enum
{
    OFF,
    ON,
    CHARGE,
    FULL
} states_t;
states_t state     = OFF;
states_t autostate = state;

/* function declarations */
void     btn_handler();
void     colorWipe(uint32_t c, uint8_t wait);
void     pixel_show_and_powerupdate();
void     rainbow(uint8_t wait);
void     rainbowCycle(uint8_t wait);
void     set_state(states_t s);
void     theaterChase(uint32_t c, uint8_t wait);
void     theaterChaseRainbow(uint8_t wait);
void     update_power();
uint32_t wheel(byte WheelPos);

/* setup is called once on 'boot' */
void setup() {
    Serial.begin(115200);

    /* Initialize onboard LED and button */
    pinMode(ONBOARD_LED, OUTPUT);
    button.attach(BUTTON_PIN, INPUT_PULLUP);
    button.interval(15);  // interval in ms
    /* Initialize all pixels to 'off' */
    pixels.begin();
    colorWipe(pixels.Color(1, 1, 1), 0);
    pixels.show();

    /* Initialize currentsensor */
    if (!ina219.begin()) {
        digitalWrite(ONBOARD_LED, !digitalRead(ONBOARD_LED));
        Serial.println("Failed to find INA219 chip");
        while (1) {
            delay(10);
        }
    }
}

#define DELAY 50

void loop() {
    button.update();
    if (button.changed()) {
        if (button.read() == HIGH) {
            if (state == OFF) {
                set_state(ON);
            } else if ((state == ON) && (autostate != OFF)) {
                set_state(autostate);
            } else {
                set_state(OFF);
            }
        }
    }

    if (state == ON) {
        static uint8_t color = 0;
        for (size_t i = 0; i < pixels.numPixels(); i++) {
            pixels.setPixelColor(i, wheel((i + color) & 255));
        }
        pixel_show_and_powerupdate();
        delay(DELAY / 10);
        color++;
    }
    pixel_show_and_powerupdate();
}

void set_state(states_t s) {
    state = s;
    Serial.print("setting state ");
    Serial.println(s);
    switch (state) {
        case OFF:
            pixels.setBrightness(0);
            pixel_show_and_powerupdate();
            break;
        case CHARGE:
            /* Blue */
            pixels.setBrightness(FULL_BRIGHTNESS);
            colorWipe(pixels.Color(0, 0, 255), DELAY);
            break;
        case FULL:
            /* Green */
            pixels.setBrightness(FULL_BRIGHTNESS);
            colorWipe(pixels.Color(0, 255, 0), DELAY);
            break;
        case ON:
            /* manual ON/OFF, will be handled in BTN handler */
            pixels.setBrightness(FULL_BRIGHTNESS);
            break;
    }
}

/* update LEDs and measure current */
void pixel_show_and_powerupdate() {
    static uint8_t counter = 0;
    pixels.show();
    if (counter++ % (200 * pixels.numPixels()) == 0) {
        update_power();
    }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
    for (uint16_t i = 0; i < pixels.numPixels(); i++) {
        pixels.setPixelColor(i, c);
        pixel_show_and_powerupdate();
        delay(wait);
    }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
    uint16_t i, j;

    for (j = 0; j < 256 * 5; j++) {  // 5 cycles of all colors on wheel
        for (i = 0; i < pixels.numPixels(); i++) {
            pixels.setPixelColor(i, wheel(((i * 256 / pixels.numPixels()) + j) & 255));
        }
        pixel_show_and_powerupdate();
        delay(wait);
    }
}

// Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
    for (int j = 0; j < 10; j++) {  // do 10 cycles of chasing
        for (int q = 0; q < 3; q++) {
            for (uint16_t i = 0; i < pixels.numPixels(); i = i + 3) {
                pixels.setPixelColor(i + q, c);  // turn every third pixel on
            }
            pixel_show_and_powerupdate();

            delay(wait);

            for (uint16_t i = 0; i < pixels.numPixels(); i = i + 3) {
                pixels.setPixelColor(i + q, 0);  // turn every third pixel off
            }
        }
    }
}

// Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
    for (int j = 0; j < 256; j++) {  // cycle all 256 colors in the wheel
        for (int q = 0; q < 3; q++) {
            for (uint16_t i = 0; i < pixels.numPixels(); i = i + 3) {
                pixels.setPixelColor(i + q, wheel((i + j) % 255));  // turn every third pixel on
            }
            pixel_show_and_powerupdate();

            delay(wait);

            for (uint16_t i = 0; i < pixels.numPixels(); i = i + 3) {
                pixels.setPixelColor(i + q, 0);  // turn every third pixel off
            }
        }
    }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t wheel(byte WheelPos) {
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85) {
        return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    if (WheelPos < 170) {
        WheelPos -= 85;
        return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
    WheelPos -= 170;
    return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void update_power() {
    // digitalWrite(ONBOARD_LED, !digitalRead(ONBOARD_LED));

    /* Read voltage and current from INA219 */
    shuntvoltage = ina219.getShuntVoltage_mV();
    busvoltage   = ina219.getBusVoltage_V();
    current_mA   = ina219.getCurrent_mA();

    /* Compute load voltage, power */
    loadvoltage = busvoltage + (shuntvoltage / 1000);
    power_mW    = loadvoltage * current_mA;

    states_t old_state = autostate;
    if (current_mA > 400) {
        autostate = CHARGE;
    } else if ((current_mA > 20) && current_mA < 300) {
        autostate = FULL;
    } else if (current_mA < 20) {
        autostate = OFF;
    }

    if ((old_state != autostate) && ((old_state == state) || (autostate == OFF))) {
        /* state changed and in auto mode or Mobile disconnected (OFF) */
        set_state(autostate);
    }
    // Serial.print("shunt Voltage: ");
    // Serial.print(shuntvoltage);
    // Serial.println(" mV");
    // Serial.print("  bus Voltage: ");
    // Serial.print(busvoltage);
    // Serial.println(" V");
    Serial.print("      current: ");
    Serial.print(current_mA);
    // Serial.println(" mA");
    // Serial.print("state        : ");
    // Serial.print(state);
    Serial.println();
}
