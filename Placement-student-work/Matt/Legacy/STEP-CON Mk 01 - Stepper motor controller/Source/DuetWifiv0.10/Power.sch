EESchema Schematic File Version 2
LIBS:DuetWifi-rescue
LIBS:power
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:DuetWifi
LIBS:DuetWifi-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 7
Title "Duet Wifi"
Date "12 jun 2016"
Rev "0.10"
Comp "Think3DPrint3D, Escher 3D"
Comment1 "CERN OSH License 1.2"
Comment2 "http://www.ohwr.org/attachments/2388/cern_ohl_v_1_2.txt"
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L LED D16
U 1 1 53B03C27
P 8600 4550
F 0 "D16" H 8600 4650 50  0000 C CNN
F 1 "3.3V" H 8600 4450 50  0000 C CNN
F 2 "" H 8600 4550 60  0001 C CNN
F 3 "" H 8600 4550 60  0001 C CNN
	1    8600 4550
	0    1    1    0   
$EndComp
$Comp
L LED D17
U 1 1 53B03C01
P 8150 4550
F 0 "D17" H 8150 4650 50  0000 C CNN
F 1 "5V+" H 8250 4400 50  0000 C CNN
F 2 "" H 8150 4550 60  0001 C CNN
F 3 "" H 8150 4550 60  0001 C CNN
	1    8150 4550
	0    1    1    0   
$EndComp
$Comp
L GND #PWR023
U 1 1 53B03BFF
P 7900 5550
AR Path="/53B03BFF" Ref="#PWR023"  Part="1" 
AR Path="/50522538/53B03BFF" Ref="#PWR023"  Part="1" 
F 0 "#PWR023" H 7900 5550 30  0001 C CNN
F 1 "GND" H 7900 5480 30  0001 C CNN
F 2 "" H 7900 5550 60  0001 C CNN
F 3 "" H 7900 5550 60  0001 C CNN
	1    7900 5550
	1    0    0    -1  
$EndComp
$Comp
L LED D15
U 1 1 53B03BD1
P 7600 4550
F 0 "D15" H 7600 4650 50  0000 C CNN
F 1 "VIN" H 7700 4450 50  0000 C CNN
F 2 "" H 7600 4550 60  0001 C CNN
F 3 "" H 7600 4550 60  0001 C CNN
	1    7600 4550
	0    1    1    0   
$EndComp
$Comp
L DIODESCH D2
U 1 1 53B02782
P 6700 1750
F 0 "D2" H 6700 1850 40  0000 C CNN
F 1 "SS3P4" H 6700 1650 40  0000 C CNN
F 2 "" H 6700 1750 60  0001 C CNN
F 3 "" H 6700 1750 60  0001 C CNN
	1    6700 1750
	0    -1   -1   0   
$EndComp
Text Notes 10500 1800 0    60   ~ 0
1A
$Comp
L DIODESCH D14
U 1 1 5220D356
P 10300 1750
F 0 "D14" H 10300 1850 40  0000 C CNN
F 1 "SS14M" H 10300 1650 40  0000 C CNN
F 2 "" H 10300 1750 60  0001 C CNN
F 3 "" H 10300 1750 60  0001 C CNN
	1    10300 1750
	0    -1   -1   0   
$EndComp
$Comp
L BSH105 TR7
U 1 1 5220C267
P 6450 4800
F 0 "TR7" H 6400 4500 70  0000 C CNN
F 1 "PMV40UN2" H 6100 5100 60  0000 C CNN
F 2 "" H 6450 4800 60  0001 C CNN
F 3 "" H 6450 4800 60  0001 C CNN
	1    6450 4800
	1    0    0    -1  
$EndComp
Text GLabel 5850 4800 0    60   Input ~ 0
PS_ON
Text Notes 5200 3850 0    60   ~ 0
PS_ON Control
$Comp
L GND #PWR024
U 1 1 5220BA8F
P 6600 5500
AR Path="/5220BA8F" Ref="#PWR024"  Part="1" 
AR Path="/50522538/5220BA8F" Ref="#PWR024"  Part="1" 
F 0 "#PWR024" H 6600 5500 30  0001 C CNN
F 1 "GND" H 6600 5430 30  0001 C CNN
F 2 "" H 6600 5500 60  0001 C CNN
F 3 "" H 6600 5500 60  0001 C CNN
	1    6600 5500
	1    0    0    -1  
$EndComp
Text GLabel 6150 4050 0    60   Input ~ 0
PS_ON_IN
$Comp
L JUMPER JP10
U 1 1 5220B966
P 9900 1500
F 0 "JP10" H 9900 1650 60  0000 C CNN
F 1 "EXT_5V_EN" H 9900 1420 40  0000 C CNN
F 2 "" H 9900 1500 60  0001 C CNN
F 3 "" H 9900 1500 60  0001 C CNN
	1    9900 1500
	1    0    0    -1  
$EndComp
Text Notes 9250 1850 0    60   ~ 0
1A
Text Notes 9800 2950 0    60   ~ 0
up to 1A
Text Notes 9800 2850 0    60   ~ 0
this design allows 
Text Notes 9800 2750 0    60   ~ 0
at least 780mA
Text Notes 9800 2650 0    60   ~ 0
ATX Spec advises
Text GLabel 10300 2200 3    60   Input ~ 0
5V_IN
Text Notes 8650 2750 0    60   ~ 0
by the USB specification
Text Notes 8650 2650 0    60   ~ 0
VBUS limited to 500mA 
$Comp
L JUMPER JP9
U 1 1 52209EAB
P 3350 2500
F 0 "JP9" H 3350 2650 60  0000 C CNN
F 1 "INT_5V_EN" H 3350 2420 40  0000 C CNN
F 2 "" H 3350 2500 60  0001 C CNN
F 3 "" H 3350 2500 60  0001 C CNN
	1    3350 2500
	0    -1   -1   0   
$EndComp
$Comp
L SS3P4 D1
U 1 1 5116BBAA
P 2050 1100
F 0 "D1" H 2050 1200 40  0000 C CNN
F 1 "SS3P4" H 2050 1000 40  0000 C CNN
F 2 "" H 2050 1100 60  0001 C CNN
F 3 "" H 2050 1100 60  0001 C CNN
	1    2050 1100
	1    0    0    -1  
$EndComp
$Comp
L DIODESCH D13
U 1 1 50F99BAC
P 9050 1800
F 0 "D13" H 9050 1900 40  0000 C CNN
F 1 "SS14M" H 9050 1700 40  0000 C CNN
F 2 "" H 9050 1800 60  0001 C CNN
F 3 "" H 9050 1800 60  0001 C CNN
	1    9050 1800
	0    -1   -1   0   
$EndComp
Text GLabel 9050 2250 3    60   Input ~ 0
VBUS
$Comp
L LM1117MP-3.3 U2
U 1 1 506B578D
P 2750 4400
F 0 "U2" H 2750 4700 60  0000 C CNN
F 1 "TC2117-3.3VDBTR" H 2800 4150 60  0000 L CNN
F 2 "" H 2750 4400 60  0001 C CNN
F 3 "" H 2750 4400 60  0001 C CNN
	1    2750 4400
	1    0    0    -1  
$EndComp
Text Notes 1500 3850 0    60   ~ 0
5V Input, 3.3V 500mA Output\nLow Drop-Out Linear Regulator
Text Notes 1500 850  0    60   ~ 0
12-24V Input, 5V 2A Output\nPWM Buck Converter\n
Text GLabel 4350 4250 2    60   Input ~ 0
+3.3V
Text GLabel 1800 4250 0    60   Input ~ 0
+5V
Text GLabel 1750 1100 0    60   Input ~ 0
V_IN
Text GLabel 9750 1000 2    60   Input ~ 0
+5V
$Comp
L GND #PWR025
U 1 1 50522574
P 2000 5550
AR Path="/50522574" Ref="#PWR025"  Part="1" 
AR Path="/50522538/50522574" Ref="#PWR025"  Part="1" 
F 0 "#PWR025" H 2000 5550 30  0001 C CNN
F 1 "GND" H 2000 5480 30  0001 C CNN
F 2 "" H 2000 5550 60  0001 C CNN
F 3 "" H 2000 5550 60  0001 C CNN
	1    2000 5550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR026
U 1 1 50522566
P 1900 3250
AR Path="/50522566" Ref="#PWR026"  Part="1" 
AR Path="/50522538/50522566" Ref="#PWR026"  Part="1" 
F 0 "#PWR026" H 1900 3250 30  0001 C CNN
F 1 "GND" H 1900 3180 30  0001 C CNN
F 2 "" H 1900 3250 60  0001 C CNN
F 3 "" H 1900 3250 60  0001 C CNN
	1    1900 3250
	1    0    0    -1  
$EndComp
$Comp
L A4403 U3
U 1 1 5543ACE6
P 5150 2000
F 0 "U3" H 5150 2050 70  0000 C CNN
F 1 "A4403" H 5150 1900 70  0000 C CNN
F 2 "" H 5150 2000 60  0000 C CNN
F 3 "" H 5150 2000 60  0000 C CNN
	1    5150 2000
	1    0    0    -1  
$EndComp
$Comp
L L_MINI L1
U 1 1 5543AD1D
P 6900 1500
F 0 "L1" H 6825 1450 30  0000 C CNN
F 1 "10uH" H 6900 1550 22  0000 C CNN
F 2 "" H 6900 1500 60  0000 C CNN
F 3 "" H 6900 1500 60  0000 C CNN
	1    6900 1500
	-1   0    0    1   
$EndComp
$Comp
L C_POL C3
U 1 1 5543CA8D
P 3050 1400
F 0 "C3" H 3075 1475 50  0000 L CNN
F 1 "100u 35V" V 2950 1100 50  0000 L CNN
F 2 "C_ELEC_6.3x7.7" H 3050 1400 60  0001 C CNN
F 3 "" H 3050 1400 60  0000 C CNN
	1    3050 1400
	1    0    0    -1  
$EndComp
$Comp
L C_POL C99
U 1 1 5543CF42
P 8350 1750
F 0 "C99" H 8375 1825 50  0000 L CNN
F 1 "100u" H 8350 1675 50  0000 L CNN
F 2 "C_ELEC_6.3x7.7" H 8350 1750 60  0001 C CNN
F 3 "" H 8350 1750 60  0000 C CNN
F 4 "10V" H 8450 1550 60  0000 C CNN "Voltage"
	1    8350 1750
	1    0    0    -1  
$EndComp
Text Notes 5900 2600 0    29   ~ 0
Resistors R85 and R86 should be surface mount,\nlow inductance type, rated at 250 mW at 70°C\n\nPossibly use 0R2 IOT limit current to 1A
Text Notes 3950 2750 0    29   ~ 0
C5 sets the soft start\ntime. Any value between\n20nf and 100nf is fine if\nC97 and C98 total 20uF
Text Notes 7300 3850 0    60   ~ 0
Power LEDs
Text GLabel 8600 4250 1    60   Input ~ 0
+3.3V
Text GLabel 8150 4200 1    60   Input ~ 0
+5V
Text GLabel 7600 4200 1    60   Input ~ 0
V_IN
Text Notes 7200 4400 0    30   ~ 0
Must be able to\nhandle 24V
Text Notes 7400 4750 1    60   ~ 0
Blue
Text Notes 7950 4750 1    60   ~ 0
Red
Text Notes 8450 4800 1    60   ~ 0
Green
$Comp
L C_SMALL C5
U 1 1 5682A3E5
P 3900 2550
F 0 "C5" H 3925 2625 50  0000 L CNN
F 1 "0u1" H 3900 2475 50  0000 L CNN
F 2 "~" H 3900 2550 60  0000 C CNN
F 3 "~" H 3900 2550 60  0000 C CNN
	1    3900 2550
	1    0    0    -1  
$EndComp
$Comp
L C_SMALL C1
U 1 1 5682A437
P 2800 1400
F 0 "C1" H 2825 1475 50  0000 L CNN
F 1 "10u 35V" V 2700 1100 50  0000 L CNN
F 2 "~" H 2800 1400 60  0000 C CNN
F 3 "~" H 2800 1400 60  0000 C CNN
F 4 "~" H 2600 1200 60  0000 C CNN "Voltage"
	1    2800 1400
	1    0    0    -1  
$EndComp
$Comp
L C_SMALL C96
U 1 1 5682A451
P 6150 1200
F 0 "C96" H 6175 1275 50  0000 L CNN
F 1 "22nF" H 6150 1125 50  0000 L CNN
F 2 "~" H 6150 1200 60  0000 C CNN
F 3 "~" H 6150 1200 60  0000 C CNN
	1    6150 1200
	1    0    0    -1  
$EndComp
$Comp
L C_SMALL C95
U 1 1 5682A46B
P 2150 4800
F 0 "C95" H 2175 4875 50  0000 L CNN
F 1 "DNP 1u" H 2150 4725 50  0000 L CNN
F 2 "~" H 2150 4800 60  0000 C CNN
F 3 "~" H 2150 4800 60  0000 C CNN
	1    2150 4800
	1    0    0    -1  
$EndComp
$Comp
L C_POL C4
U 1 1 5682A502
P 3850 4750
F 0 "C4" H 3875 4825 50  0000 L CNN
F 1 "10u TANT" H 3850 4675 50  0000 L CNN
F 2 "~" H 3850 4750 60  0000 C CNN
F 3 "~" H 3850 4750 60  0000 C CNN
	1    3850 4750
	1    0    0    -1  
$EndComp
$Comp
L C_SMALL C97
U 1 1 5682A52A
P 7250 1750
F 0 "C97" H 7275 1825 50  0000 L CNN
F 1 "10u" H 7250 1675 50  0000 L CNN
F 2 "~" H 7250 1750 60  0000 C CNN
F 3 "~" H 7250 1750 60  0000 C CNN
	1    7250 1750
	1    0    0    -1  
$EndComp
$Comp
L C_SMALL C98
U 1 1 5682A546
P 7500 1750
F 0 "C98" H 7525 1825 50  0000 L CNN
F 1 "10u" H 7500 1675 50  0000 L CNN
F 2 "~" H 7500 1750 60  0000 C CNN
F 3 "~" H 7500 1750 60  0000 C CNN
	1    7500 1750
	1    0    0    -1  
$EndComp
$Comp
L R_SMALL R84
U 1 1 5682A579
P 4200 1500
F 0 "R84" V 4275 1508 50  0000 C CNN
F 1 "100K" V 4132 1512 50  0000 C CNN
F 2 "~" H 4200 1500 60  0000 C CNN
F 3 "~" H 4200 1500 60  0000 C CNN
	1    4200 1500
	1    0    0    -1  
$EndComp
$Comp
L R_SMALL R54
U 1 1 5682A5A4
P 6000 5200
F 0 "R54" V 6075 5208 50  0000 C CNN
F 1 "4K7" V 5932 5212 50  0000 C CNN
F 2 "~" H 6000 5200 60  0000 C CNN
F 3 "~" H 6000 5200 60  0000 C CNN
	1    6000 5200
	1    0    0    -1  
$EndComp
$Comp
L R_SMALL R55
U 1 1 5682A617
P 7600 5000
F 0 "R55" V 7675 5008 50  0000 C CNN
F 1 "4K7" V 7532 5012 50  0000 C CNN
F 2 "~" H 7600 5000 60  0000 C CNN
F 3 "~" H 7600 5000 60  0000 C CNN
	1    7600 5000
	1    0    0    -1  
$EndComp
$Comp
L R_SMALL R61
U 1 1 5682A63C
P 8150 5000
F 0 "R61" V 8225 5008 50  0000 C CNN
F 1 "2K2" V 8082 5012 50  0000 C CNN
F 2 "~" H 8150 5000 60  0000 C CNN
F 3 "~" H 8150 5000 60  0000 C CNN
	1    8150 5000
	1    0    0    -1  
$EndComp
$Comp
L R_SMALL R60
U 1 1 5682A656
P 8600 5000
F 0 "R60" V 8675 5008 50  0000 C CNN
F 1 "470R" V 8532 5012 50  0000 C CNN
F 2 "~" H 8600 5000 60  0000 C CNN
F 3 "~" H 8600 5000 60  0000 C CNN
	1    8600 5000
	1    0    0    -1  
$EndComp
$Comp
L R_SMALL R88
U 1 1 5682A83B
P 7850 2650
F 0 "R88" V 7925 2658 50  0000 C CNN
F 1 "750R" V 7782 2662 50  0000 C CNN
F 2 "~" H 7850 2650 60  0000 C CNN
F 3 "~" H 7850 2650 60  0000 C CNN
	1    7850 2650
	1    0    0    -1  
$EndComp
$Comp
L R_SMALL R87
U 1 1 5682A886
P 7850 1800
F 0 "R87" V 7925 1808 50  0000 C CNN
F 1 "3K92" V 7782 1812 50  0000 C CNN
F 2 "~" H 7850 1800 60  0000 C CNN
F 3 "~" H 7850 1800 60  0000 C CNN
	1    7850 1800
	1    0    0    -1  
$EndComp
$Comp
L R_SMALL R85
U 1 1 5682A8A0
P 6400 2200
F 0 "R85" V 6475 2208 50  0000 C CNN
F 1 "0R1" V 6332 2212 50  0000 C CNN
F 2 "~" H 6400 2200 60  0000 C CNN
F 3 "~" H 6400 2200 60  0000 C CNN
	1    6400 2200
	0    -1   -1   0   
$EndComp
$Comp
L R_SMALL R86
U 1 1 5682A8B0
P 6400 2400
F 0 "R86" V 6475 2408 50  0000 C CNN
F 1 "0R1" V 6332 2412 50  0000 C CNN
F 2 "~" H 6400 2400 60  0000 C CNN
F 3 "~" H 6400 2400 60  0000 C CNN
	1    6400 2400
	0    -1   -1   0   
$EndComp
$Comp
L L_MINI L2
U 1 1 56847F52
P 3650 1100
F 0 "L2" H 3575 1050 30  0000 C CNN
F 1 "1uH" H 3650 1150 22  0000 C CNN
F 2 "" H 3650 1100 60  0000 C CNN
F 3 "" H 3650 1100 60  0000 C CNN
F 4 "2A" H 3650 1000 60  0000 C CNN "Rating"
	1    3650 1100
	-1   0    0    1   
$EndComp
$Comp
L C_SMALL C6
U 1 1 56848254
P 3900 1400
F 0 "C6" H 3925 1475 50  0000 L CNN
F 1 "10u 35V" V 3800 1100 50  0000 L CNN
F 2 "~" H 3900 1400 60  0000 C CNN
F 3 "~" H 3900 1400 60  0000 C CNN
	1    3900 1400
	1    0    0    -1  
$EndComp
Connection ~ 2150 4250
Wire Wire Line
	2150 4700 2150 4250
Wire Wire Line
	2000 5450 3850 5450
Connection ~ 6000 4800
Wire Wire Line
	6000 5000 6000 4800
Connection ~ 9050 1500
Wire Wire Line
	9050 1500 9050 1600
Wire Wire Line
	6600 4450 6600 4050
Wire Wire Line
	6600 4050 6150 4050
Wire Notes Line
	7000 5800 5000 5800
Wire Notes Line
	7000 5800 7000 3650
Wire Notes Line
	5000 5800 5000 3650
Wire Notes Line
	5000 3650 7000 3650
Wire Wire Line
	10200 1500 10300 1500
Wire Wire Line
	9750 1000 9500 1000
Connection ~ 9500 1500
Wire Wire Line
	9500 1000 9500 1500
Wire Wire Line
	2000 5450 2000 5550
Wire Notes Line
	1400 3650 4850 3650
Wire Notes Line
	10650 650  1400 650 
Wire Notes Line
	10650 650  10650 3550
Wire Notes Line
	10650 3550 1400 3550
Wire Notes Line
	1400 3550 1400 650 
Connection ~ 3850 4250
Connection ~ 2750 5450
Wire Wire Line
	2750 5450 2750 4750
Wire Notes Line
	1400 3650 1400 5800
Wire Wire Line
	3850 4250 3850 4650
Wire Notes Line
	4850 3650 4850 5800
Wire Wire Line
	1800 4250 2350 4250
Wire Notes Line
	4850 5800 1400 5800
Wire Wire Line
	3150 4350 3250 4350
Wire Wire Line
	3250 4350 3250 4250
Connection ~ 3250 4250
Wire Wire Line
	9050 2250 9050 2000
Wire Wire Line
	10300 2200 10300 1950
Wire Wire Line
	10300 1500 10300 1550
Wire Wire Line
	6600 5150 6600 5500
Wire Wire Line
	5850 4800 6150 4800
Wire Wire Line
	6000 5400 6600 5400
Connection ~ 6600 5400
Wire Wire Line
	2150 4900 2150 5450
Connection ~ 2150 5450
Wire Wire Line
	3150 4250 4350 4250
Connection ~ 4250 4250
Wire Wire Line
	1750 1100 1850 1100
Connection ~ 1800 1100
Wire Wire Line
	2250 1100 3550 1100
Wire Wire Line
	3750 1100 4900 1100
Wire Wire Line
	4900 1100 4900 1150
Wire Wire Line
	4200 1300 4200 1100
Connection ~ 4200 1100
Wire Wire Line
	3050 1300 3050 1100
Wire Wire Line
	2800 1100 2800 1300
Connection ~ 2800 1100
Wire Wire Line
	1650 3100 8650 3100
Wire Wire Line
	1900 3100 1900 3250
Wire Wire Line
	7850 3100 7850 2850
Connection ~ 1900 3100
Wire Wire Line
	3350 2800 3350 3100
Connection ~ 3350 3100
Connection ~ 2800 3100
Wire Wire Line
	4200 1700 4300 1700
Wire Wire Line
	3350 2200 3350 2000
Wire Wire Line
	3350 2000 4300 2000
Wire Wire Line
	4300 2200 3900 2200
Wire Wire Line
	3900 2200 3900 2450
Wire Wire Line
	3900 2650 3900 3100
Connection ~ 3900 3100
Wire Wire Line
	4650 2850 4650 3100
Connection ~ 4650 3100
Wire Wire Line
	4750 2850 4750 3100
Connection ~ 4750 3100
Wire Wire Line
	4950 2850 5450 2850
Connection ~ 5050 2850
Connection ~ 5150 2850
Wire Wire Line
	5250 2850 5250 3100
Connection ~ 5250 3100
Connection ~ 5250 2850
Connection ~ 5350 2850
Wire Wire Line
	7600 2500 7600 2300
Wire Wire Line
	7600 2300 7850 2300
Wire Wire Line
	7850 2000 7850 2450
Connection ~ 7850 2300
Wire Wire Line
	6150 2200 6150 3100
Wire Wire Line
	6700 2300 6650 2300
Wire Wire Line
	6700 1950 6700 2300
Connection ~ 6650 2300
Wire Wire Line
	6700 2000 6000 2000
Connection ~ 6700 2000
Wire Wire Line
	5400 1150 5400 1000
Wire Wire Line
	5400 1000 6150 1000
Wire Wire Line
	6150 1000 6150 1100
Wire Wire Line
	6000 1500 6800 1500
Wire Wire Line
	6150 1300 6150 1500
Connection ~ 6150 1500
Wire Wire Line
	6700 1550 6700 1500
Connection ~ 6700 1500
Wire Wire Line
	7250 1650 7250 1500
Connection ~ 7250 1500
Wire Wire Line
	7500 1500 7500 1650
Connection ~ 7500 1500
Wire Wire Line
	7850 1500 7850 1600
Connection ~ 7850 1500
Wire Notes Line
	9100 5800 7100 5800
Wire Notes Line
	9100 5800 9100 3650
Wire Notes Line
	7100 5800 7100 3650
Wire Notes Line
	7100 3650 9100 3650
Wire Wire Line
	3850 5450 3850 4850
Wire Wire Line
	7600 4200 7600 4350
Wire Wire Line
	8150 4200 8150 4350
Wire Wire Line
	8600 4250 8600 4350
Wire Wire Line
	7600 5300 8600 5300
Wire Wire Line
	7900 5300 7900 5550
Connection ~ 7900 5300
Connection ~ 8150 5300
Wire Wire Line
	7600 4800 7600 4750
Wire Wire Line
	8150 4800 8150 4750
Wire Wire Line
	8600 4800 8600 4750
Connection ~ 6150 3100
Wire Wire Line
	7250 1850 7250 3100
Connection ~ 7250 3100
Wire Wire Line
	7500 3100 7500 1850
Connection ~ 7500 3100
Wire Wire Line
	6000 2300 6150 2300
Connection ~ 6150 2300
Wire Wire Line
	6150 2300 6150 2400
Wire Wire Line
	6650 2200 6650 2400
Wire Wire Line
	8600 5300 8600 5200
Wire Wire Line
	8150 5300 8150 5200
Wire Wire Line
	7600 5300 7600 5200
Wire Wire Line
	6150 2200 6200 2200
Wire Wire Line
	6600 2200 6650 2200
Wire Wire Line
	6650 2400 6600 2400
Wire Wire Line
	6150 2400 6200 2400
Connection ~ 6150 2400
Wire Wire Line
	3050 1500 3050 1800
Wire Wire Line
	2800 1800 3900 1800
Connection ~ 2800 1800
Connection ~ 3050 1100
Wire Wire Line
	3900 1300 3900 1100
Connection ~ 3900 1100
Wire Wire Line
	3900 1800 3900 1500
Connection ~ 3050 1800
Wire Wire Line
	6000 2500 7600 2500
Wire Wire Line
	8350 1500 8350 1650
Connection ~ 8350 1500
Wire Wire Line
	8350 3100 8350 1850
Connection ~ 7850 3100
$Comp
L C_SMALL C7
U 1 1 568486DB
P 8650 1750
F 0 "C7" H 8675 1825 50  0000 L CNN
F 1 "10u" H 8650 1675 50  0000 L CNN
F 2 "~" H 8650 1750 60  0000 C CNN
F 3 "~" H 8650 1750 60  0000 C CNN
	1    8650 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8650 1500 8650 1650
Connection ~ 8650 1500
Wire Wire Line
	8650 3100 8650 1850
Connection ~ 8350 3100
Wire Wire Line
	7000 1500 8000 1500
Wire Wire Line
	8200 1500 9600 1500
$Comp
L L_MINI L3
U 1 1 5684940F
P 8100 1500
F 0 "L3" H 8025 1450 30  0000 C CNN
F 1 "1uH" H 8100 1550 22  0000 C CNN
F 2 "" H 8100 1500 60  0000 C CNN
F 3 "" H 8100 1500 60  0000 C CNN
F 4 "2A" H 8100 1400 60  0000 C CNN "Rating"
	1    8100 1500
	-1   0    0    1   
$EndComp
Wire Wire Line
	2800 1500 2800 3100
$Comp
L R_SMALL R15
U 1 1 5684A68A
P 2500 2100
F 0 "R15" V 2575 2108 50  0000 C CNN
F 1 "47K" V 2432 2112 50  0000 C CNN
F 2 "~" H 2500 2100 60  0000 C CNN
F 3 "~" H 2500 2100 60  0000 C CNN
	1    2500 2100
	1    0    0    -1  
$EndComp
$Comp
L R_SMALL R16
U 1 1 5684A690
P 2500 2600
F 0 "R16" V 2575 2608 50  0000 C CNN
F 1 "4K7" V 2432 2612 50  0000 C CNN
F 2 "~" H 2500 2600 60  0000 C CNN
F 3 "~" H 2500 2600 60  0000 C CNN
	1    2500 2600
	1    0    0    -1  
$EndComp
Text GLabel 2450 2350 0    60   Input ~ 0
PWR_FAIL_DET1
Wire Wire Line
	2450 2350 2500 2350
Wire Wire Line
	2500 2300 2500 2400
Connection ~ 2500 2350
Wire Wire Line
	2500 2800 2500 3100
Connection ~ 2500 3100
Wire Wire Line
	2500 1900 2500 1100
Connection ~ 2500 1100
$Comp
L C_POL C12
U 1 1 5693ADFC
P 3350 1400
F 0 "C12" H 3375 1475 50  0000 L CNN
F 1 "100u 35V" V 3250 1100 50  0000 L CNN
F 2 "C_ELEC_6.3x7.7" H 3350 1400 60  0001 C CNN
F 3 "" H 3350 1400 60  0000 C CNN
	1    3350 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 1300 3350 1100
Connection ~ 3350 1100
Wire Wire Line
	3350 1500 3350 1800
Connection ~ 3350 1800
$Comp
L R_SMALL R80
U 1 1 56945575
P 1650 1550
F 0 "R80" V 1725 1558 50  0000 C CNN
F 1 "47K" V 1582 1562 50  0000 C CNN
F 2 "~" H 1650 1550 60  0000 C CNN
F 3 "~" H 1650 1550 60  0000 C CNN
	1    1650 1550
	1    0    0    -1  
$EndComp
$Comp
L R_SMALL R81
U 1 1 5694557B
P 1650 2050
F 0 "R81" V 1725 2058 50  0000 C CNN
F 1 "4K7" V 1582 2062 50  0000 C CNN
F 2 "~" H 1650 2050 60  0000 C CNN
F 3 "~" H 1650 2050 60  0000 C CNN
	1    1650 2050
	1    0    0    -1  
$EndComp
Text GLabel 1700 1800 2    60   Input ~ 0
PWR_FAIL_DET2
Wire Wire Line
	1650 1750 1650 1850
Connection ~ 1650 1800
Wire Wire Line
	1650 1350 1650 1250
Wire Wire Line
	1650 1250 1800 1250
Wire Wire Line
	1800 1250 1800 1100
Wire Wire Line
	1650 2250 1650 3100
Wire Wire Line
	1700 1800 1650 1800
$Comp
L C_SMALL C81
U 1 1 56A121C4
P 8050 1800
F 0 "C81" H 8075 1875 50  0000 L CNN
F 1 "0u01" H 8050 1725 50  0000 L CNN
F 2 "~" H 8050 1800 60  0000 C CNN
F 3 "~" H 8050 1800 60  0000 C CNN
	1    8050 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	8050 1700 8050 1600
Wire Wire Line
	8050 1600 7850 1600
Wire Wire Line
	7850 2000 8050 2000
Wire Wire Line
	8050 2000 8050 1900
$Comp
L C_SMALL C80
U 1 1 56A12338
P 2250 2600
F 0 "C80" H 2275 2675 50  0000 L CNN
F 1 "0u1" H 2250 2525 50  0000 L CNN
F 2 "~" H 2250 2600 60  0000 C CNN
F 3 "~" H 2250 2600 60  0000 C CNN
	1    2250 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 2400 2250 2400
Wire Wire Line
	2250 2400 2250 2500
Wire Wire Line
	2250 2700 2250 2800
Wire Wire Line
	2250 2800 2500 2800
$Comp
L C_SMALL C79
U 1 1 56A124BD
P 1850 2050
F 0 "C79" H 1875 2125 50  0000 L CNN
F 1 "0u1" H 1850 1975 50  0000 L CNN
F 2 "~" H 1850 2050 60  0000 C CNN
F 3 "~" H 1850 2050 60  0000 C CNN
	1    1850 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 1850 1850 1850
Wire Wire Line
	1850 1850 1850 1950
Wire Wire Line
	1650 2250 1850 2250
Wire Wire Line
	1850 2250 1850 2150
Text Notes 1700 5100 0    60   ~ 0
C95 Do Not Populate
$EndSCHEMATC
