EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector:Conn_01x04_Female J1
U 1 1 6176E532
P 2250 1650
F 0 "J1" H 2142 1935 50  0000 C CNN
F 1 "USB IN" H 2142 1844 50  0000 C CNN
F 2 "" H 2250 1650 50  0001 C CNN
F 3 "~" H 2250 1650 50  0001 C CNN
	1    2250 1650
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Female J2
U 1 1 6176F182
P 2250 2450
F 0 "J2" H 2142 2735 50  0000 C CNN
F 1 "USB OUT" H 2142 2644 50  0000 C CNN
F 2 "" H 2250 2450 50  0001 C CNN
F 3 "~" H 2250 2450 50  0001 C CNN
	1    2250 2450
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x06_Female J3
U 1 1 617711E2
P 3150 2950
F 0 "J3" V 2996 3198 50  0000 L CNN
F 1 "INA219" V 3087 3198 50  0000 L CNN
F 2 "" H 3150 2950 50  0001 C CNN
F 3 "~" H 3150 2950 50  0001 C CNN
	1    3150 2950
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x07_Female J4
U 1 1 617730EF
P 3250 1150
F 0 "J4" V 3250 700 50  0000 C CNN
F 1 "Arduino pro mini" V 3150 450 50  0000 C CNN
F 2 "" H 3250 1150 50  0001 C CNN
F 3 "~" H 3250 1150 50  0001 C CNN
	1    3250 1150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2450 1550 2950 1550
Wire Wire Line
	2850 2750 2850 2350
Wire Wire Line
	2850 2350 2450 2350
Wire Wire Line
	2450 1850 3050 1850
Wire Wire Line
	3850 1950 3850 2000
Wire Wire Line
	3150 2750 3150 1950
Wire Wire Line
	3150 1950 3850 1950
Wire Wire Line
	3550 2300 3450 2300
Wire Wire Line
	2450 2450 2600 2450
Wire Wire Line
	2600 1650 2450 1650
Wire Wire Line
	2450 1750 2700 1750
Wire Wire Line
	2700 2550 2450 2550
Text GLabel 2200 1550 0    50   Input ~ 0
+5V
Text GLabel 2200 1650 0    50   Input ~ 0
D+
Text GLabel 2200 1750 0    50   Input ~ 0
D-
Text GLabel 2200 1850 0    50   Input ~ 0
GND
Text GLabel 2200 2350 0    50   Input ~ 0
+5V
Text GLabel 2200 2450 0    50   Input ~ 0
D+
Text GLabel 2200 2550 0    50   Input ~ 0
D-
Text GLabel 2200 2650 0    50   Input ~ 0
GND
Text GLabel 2950 1100 1    50   Input ~ 0
RAW
Text GLabel 3050 1100 1    50   Input ~ 0
GND
Text GLabel 3150 1100 1    50   Input ~ 0
VCC
Text GLabel 3250 1100 1    50   Input ~ 0
SDA(A4)
Text GLabel 3350 1100 1    50   Input ~ 0
SCL(A5)
Text GLabel 2850 3000 3    50   Input ~ 0
V-
Text GLabel 2950 3000 3    50   Input ~ 0
V+
Text GLabel 3050 3000 3    50   Input ~ 0
GND
Text GLabel 3150 3000 3    50   Input ~ 0
VCC
Text GLabel 3250 3000 3    50   Input ~ 0
SDA
Text GLabel 3350 3000 3    50   Input ~ 0
SCL
$Comp
L LED:WS2812B D1
U 1 1 61778E11
P 3850 2300
F 0 "D1" H 4194 2346 50  0000 L CNN
F 1 "WS2812B" H 4194 2255 50  0000 L CNN
F 2 "LED_SMD:LED_WS2812B_PLCC4_5.0x5.0mm_P3.2mm" H 3900 2000 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 3950 1925 50  0001 L TNN
	1    3850 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 2650 3050 2650
Wire Wire Line
	3050 2650 3050 2750
Connection ~ 3050 2650
Wire Wire Line
	3050 2650 3850 2650
Wire Wire Line
	3850 2650 3850 2600
$Comp
L Switch:SW_Push SW1
U 1 1 6179818E
P 3850 1650
F 0 "SW1" V 3804 1798 50  0000 L CNN
F 1 "SW_Push" V 3895 1798 50  0000 L CNN
F 2 "" H 3850 1850 50  0001 C CNN
F 3 "~" H 3850 1850 50  0001 C CNN
	1    3850 1650
	0    1    1    0   
$EndComp
Wire Wire Line
	2950 1350 2950 1550
Wire Wire Line
	3050 1350 3050 1850
Wire Wire Line
	3150 1350 3150 1950
Connection ~ 3150 1950
Wire Wire Line
	3250 1350 3250 2750
Wire Wire Line
	3350 1350 3350 2750
Wire Wire Line
	3450 1350 3450 2300
Wire Wire Line
	3550 1350 3550 1450
Wire Wire Line
	3550 1450 3850 1450
Wire Wire Line
	3850 1850 3050 1850
Connection ~ 3050 1850
Connection ~ 2950 1550
Wire Wire Line
	2950 1550 2950 2750
Wire Wire Line
	3050 1850 3050 2650
Wire Wire Line
	2600 1650 2600 2450
Wire Wire Line
	2700 1750 2700 2550
Text GLabel 3550 1100 1    50   Input ~ 0
IO2
Text GLabel 3450 1100 1    50   Input ~ 0
IO10
$EndSCHEMATC
