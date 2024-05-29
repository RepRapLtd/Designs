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
$Descr A3 16535 11693
encoding utf-8
Sheet 4 7
Title "Duet Wifi"
Date "12 jun 2016"
Rev "0.10"
Comp "Think3DPrint3D, Escher 3D"
Comment1 "CERN OSH License 1.2"
Comment2 "http://www.ohwr.org/attachments/2388/cern_ohl_v_1_2.txt"
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 8800 4700 1    60   Input ~ 0
+3.3V
$Comp
L CONN_4 J28
U 1 1 53C6F476
P 10300 4550
F 0 "J28" H 10300 4800 50  0000 C CNN
F 1 "Probe" V 10450 4550 50  0000 C CNN
F 2 "" H 10300 4550 60  0001 C CNN
F 3 "" H 10300 4550 60  0001 C CNN
	1    10300 4550
	1    0    0    -1  
$EndComp
Text GLabel 9750 4600 0    60   Input ~ 0
Z_PROBE_MOD
Text GLabel 9700 4300 0    50   BiDi ~ 0
Z_PROBE_IN
$Comp
L GND #PWR027
U 1 1 53B0339C
P 1050 6450
AR Path="/53B0339C" Ref="#PWR027"  Part="1" 
AR Path="/50656780/53B0339C" Ref="#PWR027"  Part="1" 
F 0 "#PWR027" H 1050 6450 30  0001 C CNN
F 1 "GND" H 1050 6380 30  0001 C CNN
F 2 "" H 1050 6450 60  0001 C CNN
F 3 "" H 1050 6450 60  0001 C CNN
	1    1050 6450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR028
U 1 1 53B0339B
P 9600 4450
AR Path="/53B0339B" Ref="#PWR028"  Part="1" 
AR Path="/50656780/53B0339B" Ref="#PWR028"  Part="1" 
F 0 "#PWR028" H 9600 4450 30  0001 C CNN
F 1 "GND" H 9600 4380 30  0001 C CNN
F 2 "" H 9600 4450 60  0001 C CNN
F 3 "" H 9600 4450 60  0001 C CNN
	1    9600 4450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR029
U 1 1 53B03391
P 1750 2600
AR Path="/53B03391" Ref="#PWR029"  Part="1" 
AR Path="/50656780/53B03391" Ref="#PWR029"  Part="1" 
F 0 "#PWR029" H 1750 2600 30  0001 C CNN
F 1 "GND" H 1750 2530 30  0001 C CNN
F 2 "" H 1750 2600 60  0001 C CNN
F 3 "" H 1750 2600 60  0001 C CNN
	1    1750 2600
	1    0    0    -1  
$EndComp
Text GLabel 1500 6450 0    60   Input ~ 0
V_FAN
$Comp
L CONN2 J24
U 1 1 53B03332
P 1900 6350
F 0 "J24" H 1900 6250 40  0000 C CNN
F 1 "GND V_IN" V 2050 6400 40  0000 C CNN
F 2 "" H 1900 6350 60  0001 C CNN
F 3 "" H 1900 6350 60  0001 C CNN
	1    1900 6350
	1    0    0    1   
$EndComp
Text GLabel 1800 2250 0    60   Input ~ 0
PS_ON_IN
$Comp
L CONN_3 J20
U 1 1 5220C30B
P 2300 2250
F 0 "J20" V 2250 2250 50  0000 C CNN
F 1 "5V_PS" V 2450 2250 40  0000 C CNN
F 2 "" H 2300 2250 60  0001 C CNN
F 3 "" H 2300 2250 60  0001 C CNN
	1    2300 2250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR030
U 1 1 5220B9D2
P 1550 1500
AR Path="/5220B9D2" Ref="#PWR030"  Part="1" 
AR Path="/50656780/5220B9D2" Ref="#PWR030"  Part="1" 
F 0 "#PWR030" H 1550 1500 30  0001 C CNN
F 1 "GND" H 1550 1430 30  0001 C CNN
F 2 "" H 1550 1500 60  0001 C CNN
F 3 "" H 1550 1500 60  0001 C CNN
	1    1550 1500
	1    0    0    -1  
$EndComp
Text GLabel 1650 2000 0    60   Input ~ 0
5V_IN
Text GLabel 7700 6850 0    60   BiDi ~ 0
VSSA
$Comp
L CONN2X25 J1
U 1 1 51052F54
P 8350 4600
F 0 "J1" H 8350 670 60  0000 C CNN
F 1 "EXPANSION" H 8350 8270 60  0000 C CNN
F 2 "" H 8350 4600 60  0001 C CNN
F 3 "" H 8350 4600 60  0001 C CNN
	1    8350 4600
	1    0    0    -1  
$EndComp
Text GLabel 7700 5800 0    60   BiDi ~ 0
SPI1_MOSI_BUFF
Text GLabel 7700 5950 0    60   BiDi ~ 0
SPI1_MISO
Text GLabel 7700 1000 0    60   Output ~ 0
+5V
Text GLabel 7700 8200 0    60   BiDi ~ 0
SPI0_MISO
Text GLabel 7700 8050 0    60   BiDi ~ 0
SPI0_MOSI
Text GLabel 9700 5300 0    60   Input ~ 0
URXD0
Text GLabel 9700 5450 0    60   Input ~ 0
UTXD0
Text GLabel 7700 7450 0    60   Input ~ 0
RESET
Text Notes 2900 1300 2    60   ~ 0
High Current\nScrew Term
Text GLabel 4100 10000 0    60   Input ~ 0
VSSA
Text GLabel 4100 9450 0    60   Input ~ 0
VSSA
Text GLabel 1400 1250 0    60   Input ~ 0
V_IN
$Comp
L CONN2 J23
U 1 1 508859F9
P 2100 1350
F 0 "J23" H 2100 1250 40  0000 C CNN
F 1 "POWER IN" V 2250 1400 40  0000 C CNN
F 2 "" H 2100 1350 60  0001 C CNN
F 3 "" H 2100 1350 60  0001 C CNN
	1    2100 1350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR031
U 1 1 50659578
P 3600 8500
AR Path="/50659578" Ref="#PWR031"  Part="1" 
AR Path="/50656780/50659578" Ref="#PWR031"  Part="1" 
F 0 "#PWR031" H 3600 8500 30  0001 C CNN
F 1 "GND" H 3600 8430 30  0001 C CNN
F 2 "" H 3600 8500 60  0001 C CNN
F 3 "" H 3600 8500 60  0001 C CNN
	1    3600 8500
	1    0    0    -1  
$EndComp
Text GLabel 3700 5800 1    60   Input ~ 0
+3.3V
$Comp
L CONN2 J5
U 1 1 50656C59
P 4500 9350
F 0 "J5" H 4500 9250 40  0000 C CNN
F 1 "BED TEMP" V 4650 9400 40  0000 C CNN
F 2 "" H 4500 9350 60  0001 C CNN
F 3 "" H 4500 9350 60  0001 C CNN
	1    4500 9350
	1    0    0    1   
$EndComp
$Comp
L CONN2 J4
U 1 1 50656C44
P 1900 3600
F 0 "J4" H 1900 3500 40  0000 C CNN
F 1 "BED HEAT" V 2050 3650 40  0000 C CNN
F 2 "" H 1900 3600 60  0001 C CNN
F 3 "" H 1900 3600 60  0001 C CNN
	1    1900 3600
	1    0    0    1   
$EndComp
Text GLabel 7700 7750 0    60   Input ~ 0
TWCK0
Text GLabel 7700 7600 0    60   Input ~ 0
TWD0
Text Notes 2750 3650 2    60   ~ 0
High Current\nScrew Term
Text GLabel 1350 4000 0    60   Input ~ 0
E0-
Text GLabel 1350 4200 0    60   Input ~ 0
V_IN
Text GLabel 1400 5200 0    60   Input ~ 0
V_FAN
Text GLabel 1400 3600 0    60   Input ~ 0
V_IN
Text GLabel 1400 5050 0    60   Input ~ 0
FAN0-
Text GLabel 1350 3800 0    60   Input ~ 0
BED-
Text GLabel 4100 9300 0    60   Input ~ 0
THERMISTOR0
Text GLabel 4100 9850 0    60   Input ~ 0
THERMISTOR1
Text GLabel 4550 6000 0    60   Input ~ 0
Z_STOP_CONN
Text GLabel 4550 7600 0    60   Input ~ 0
E0_STOP_CONN
Text GLabel 4550 6500 0    60   Input ~ 0
Y_STOP_CONN
Text GLabel 4550 7050 0    60   Input ~ 0
X_STOP_CONN
Text GLabel 4250 1300 0    60   Output ~ 0
Z_MOT_1A
Text GLabel 4250 900  0    60   Output ~ 0
Z_MOT_1B
Text GLabel 4250 1450 0    60   Output ~ 0
Z_MOT_2A
Text GLabel 4250 1750 0    60   Output ~ 0
Z_MOT_2B
Text GLabel 4250 3950 0    60   Output ~ 0
E0_MOT_2B
Text GLabel 4250 3800 0    60   Output ~ 0
E0_MOT_2A
Text GLabel 4250 3500 0    60   Output ~ 0
E0_MOT_1B
Text GLabel 4250 3650 0    60   Output ~ 0
E0_MOT_1A
Text GLabel 4250 2250 0    60   Output ~ 0
Y_MOT_1A
Text GLabel 4250 2100 0    60   Output ~ 0
Y_MOT_1B
Text GLabel 4250 2400 0    60   Output ~ 0
Y_MOT_2A
Text GLabel 4250 2550 0    60   Output ~ 0
Y_MOT_2B
Text GLabel 4250 3250 0    60   Output ~ 0
X_MOT_2B
Text GLabel 4250 3100 0    60   Output ~ 0
X_MOT_2A
Text GLabel 4250 2800 0    60   Output ~ 0
X_MOT_1B
Text GLabel 4250 2950 0    60   Output ~ 0
X_MOT_1A
Text GLabel 7700 1300 0    60   Output ~ 0
+3.3V
Text GLabel 4550 8150 0    60   Input ~ 0
E1_STOP_CONN
Text GLabel 4250 4650 0    60   Output ~ 0
E1_MOT_2B
Text GLabel 4250 4500 0    60   Output ~ 0
E1_MOT_2A
Text GLabel 4250 4200 0    60   Output ~ 0
E1_MOT_1B
Text GLabel 4250 4350 0    60   Output ~ 0
E1_MOT_1A
Wire Wire Line
	4150 9850 4100 9850
Wire Wire Line
	1350 4200 1550 4200
Wire Wire Line
	8800 4700 9950 4700
Wire Wire Line
	9950 4400 9950 4300
Wire Wire Line
	9950 4300 9700 4300
Wire Wire Line
	4100 9450 4150 9450
Wire Wire Line
	1800 2250 1950 2250
Wire Wire Line
	1550 1500 1550 1350
Wire Wire Line
	1550 1350 1750 1350
Wire Wire Line
	7700 1900 7950 1900
Wire Wire Line
	7950 1600 7700 1600
Wire Wire Line
	7700 1300 7950 1300
Wire Wire Line
	7700 5950 7950 5950
Wire Wire Line
	7700 8200 7950 8200
Wire Wire Line
	7700 6400 7950 6400
Wire Wire Line
	7700 6100 7950 6100
Wire Wire Line
	7700 5650 7950 5650
Wire Wire Line
	7700 5050 7950 5050
Wire Wire Line
	7700 4750 7950 4750
Wire Wire Line
	7700 4450 7950 4450
Wire Wire Line
	7700 4150 7950 4150
Wire Wire Line
	7700 3850 7950 3850
Wire Wire Line
	7700 2950 7950 2950
Wire Wire Line
	7700 2500 7950 2500
Wire Wire Line
	1400 5200 1550 5200
Wire Wire Line
	1750 1250 1400 1250
Wire Wire Line
	1550 3800 1350 3800
Wire Wire Line
	4250 1300 4450 1300
Wire Wire Line
	4350 1400 4450 1400
Wire Wire Line
	1550 5050 1400 5050
Wire Wire Line
	1350 4000 1550 4000
Wire Wire Line
	7700 1000 7950 1000
Wire Wire Line
	7700 2650 7950 2650
Wire Wire Line
	7700 3700 7950 3700
Wire Wire Line
	7700 4000 7950 4000
Wire Wire Line
	7700 4300 7950 4300
Wire Wire Line
	7700 4900 7950 4900
Wire Wire Line
	7700 5200 7950 5200
Wire Wire Line
	7700 6250 7950 6250
Wire Wire Line
	7700 6550 7950 6550
Wire Wire Line
	7700 8350 7950 8350
Wire Wire Line
	7700 2800 7950 2800
Wire Wire Line
	7700 1450 7950 1450
Wire Wire Line
	7700 1750 7950 1750
Wire Wire Line
	7700 2050 7950 2050
Wire Wire Line
	7700 2350 7950 2350
Wire Wire Line
	7700 8050 7950 8050
Wire Wire Line
	7700 7750 7950 7750
Wire Wire Line
	7150 7150 7950 7150
Wire Wire Line
	7700 7000 7950 7000
Wire Wire Line
	7700 6700 7950 6700
Wire Wire Line
	7700 5800 7950 5800
Wire Wire Line
	7700 7600 7950 7600
Wire Wire Line
	7700 7900 7950 7900
Wire Wire Line
	7700 7450 7950 7450
Wire Wire Line
	1650 2000 1950 2000
Wire Wire Line
	1950 2000 1950 2150
Wire Wire Line
	1950 2350 1950 2450
Wire Wire Line
	1950 2450 1750 2450
Wire Wire Line
	1750 2450 1750 2600
Wire Wire Line
	1550 3700 1550 3800
Wire Wire Line
	4100 9300 4150 9300
Wire Wire Line
	4150 9300 4150 9350
Wire Wire Line
	9750 4600 9950 4600
Wire Wire Line
	9600 4450 9600 4400
Wire Wire Line
	9600 4400 9850 4400
Wire Wire Line
	9850 4400 9850 4500
Wire Wire Line
	9850 4500 9950 4500
Wire Wire Line
	4100 10000 4150 10000
Wire Wire Line
	4150 10000 4150 9950
$Comp
L CONN2 J12
U 1 1 5547E95B
P 4500 9850
F 0 "J12" H 4500 9750 40  0000 C CNN
F 1 "E0 TEMP" V 4650 9900 40  0000 C CNN
F 2 "" H 4500 9850 60  0001 C CNN
F 3 "" H 4500 9850 60  0001 C CNN
	1    4500 9850
	1    0    0    1   
$EndComp
Text Notes 2150 6400 0    28   ~ 0
Always on FAN 0
$Comp
L CONN2 J25
U 1 1 5547EAD4
P 1900 5050
F 0 "J25" H 1900 4950 40  0000 C CNN
F 1 "FAN0" V 2050 5100 40  0000 C CNN
F 2 "" H 1900 5050 60  0001 C CNN
F 3 "" H 1900 5050 60  0001 C CNN
	1    1900 5050
	1    0    0    1   
$EndComp
Wire Wire Line
	1550 5200 1550 5150
Text GLabel 1400 5600 0    60   Input ~ 0
V_FAN
Text GLabel 1400 5450 0    60   Input ~ 0
FAN1-
Wire Wire Line
	1400 5600 1550 5600
Wire Wire Line
	1550 5450 1400 5450
$Comp
L CONN2 J29
U 1 1 5547EC20
P 1900 5450
F 0 "J29" H 1900 5350 40  0000 C CNN
F 1 "FAN1" V 2050 5500 40  0000 C CNN
F 2 "" H 1900 5450 60  0001 C CNN
F 3 "" H 1900 5450 60  0001 C CNN
	1    1900 5450
	1    0    0    1   
$EndComp
Wire Wire Line
	1550 5600 1550 5550
Text GLabel 4100 10450 0    60   Input ~ 0
VSSA
Text GLabel 1350 4500 0    60   Input ~ 0
E1-
Text GLabel 1350 4700 0    60   Input ~ 0
V_IN
Text GLabel 4100 10300 0    60   Input ~ 0
THERMISTOR2
Wire Wire Line
	4150 10300 4100 10300
Wire Wire Line
	1350 4700 1550 4700
Wire Wire Line
	1350 4500 1550 4500
Wire Wire Line
	4100 10450 4150 10450
Wire Wire Line
	4150 10450 4150 10400
$Comp
L CONN2 J14
U 1 1 5547EE93
P 4500 10300
F 0 "J14" H 4500 10200 40  0000 C CNN
F 1 "E1 TEMP" V 4650 10350 40  0000 C CNN
F 2 "" H 4500 10300 60  0001 C CNN
F 3 "" H 4500 10300 60  0001 C CNN
	1    4500 10300
	1    0    0    1   
$EndComp
Wire Wire Line
	7950 2200 7700 2200
Wire Wire Line
	7700 3550 7950 3550
Wire Wire Line
	7950 3400 7700 3400
Wire Wire Line
	7950 3100 7700 3100
Wire Wire Line
	7700 3250 7950 3250
Wire Wire Line
	7950 4600 7700 4600
Wire Wire Line
	7700 6850 7950 6850
$Comp
L CONN2 J13
U 1 1 5561BA4E
P 1900 4500
F 0 "J13" H 1900 4400 40  0000 C CNN
F 1 "E1 HEAT" V 2050 4550 40  0000 C CNN
F 2 "" H 1900 4500 60  0001 C CNN
F 3 "" H 1900 4500 60  0001 C CNN
	1    1900 4500
	1    0    0    1   
$EndComp
Wire Wire Line
	1550 4700 1550 4600
$Comp
L CONN2 J11
U 1 1 5561BB83
P 1900 4000
F 0 "J11" H 1900 3900 40  0000 C CNN
F 1 "E0 HEAT" V 2050 4050 40  0000 C CNN
F 2 "" H 1900 4000 60  0001 C CNN
F 3 "" H 1900 4000 60  0001 C CNN
	1    1900 4000
	1    0    0    1   
$EndComp
Wire Wire Line
	1550 4200 1550 4100
$Comp
L CONN_4 J30
U 1 1 5561C4A6
P 10300 5250
F 0 "J30" H 10300 5500 50  0000 C CNN
F 1 "PanelDUE" V 10450 5250 50  0000 C CNN
F 2 "" H 10300 5250 60  0001 C CNN
F 3 "" H 10300 5250 60  0001 C CNN
	1    10300 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 6350 1050 6350
Wire Wire Line
	1050 6350 1050 6450
Wire Wire Line
	1500 6450 1550 6450
$Comp
L GND #PWR032
U 1 1 556996C5
P 1050 6750
AR Path="/556996C5" Ref="#PWR032"  Part="1" 
AR Path="/50656780/556996C5" Ref="#PWR032"  Part="1" 
F 0 "#PWR032" H 1050 6750 30  0001 C CNN
F 1 "GND" H 1050 6680 30  0001 C CNN
F 2 "" H 1050 6750 60  0001 C CNN
F 3 "" H 1050 6750 60  0001 C CNN
	1    1050 6750
	1    0    0    -1  
$EndComp
Text GLabel 1500 6750 0    60   Input ~ 0
V_FAN
$Comp
L CONN2 J31
U 1 1 556996CC
P 1900 6650
F 0 "J31" H 1900 6550 40  0000 C CNN
F 1 "GND V_IN" V 2050 6700 40  0000 C CNN
F 2 "" H 1900 6650 60  0001 C CNN
F 3 "" H 1900 6650 60  0001 C CNN
	1    1900 6650
	1    0    0    1   
$EndComp
Text Notes 2150 6700 0    28   ~ 0
Always on FAN1
Wire Wire Line
	1550 6650 1050 6650
Wire Wire Line
	1050 6650 1050 6750
Wire Wire Line
	1500 6750 1550 6750
Wire Wire Line
	7200 950  7400 950 
Wire Wire Line
	7400 950  7400 1150
Wire Wire Line
	7400 1150 7950 1150
Text GLabel 7700 3700 0    60   Output ~ 0
E5_STOP
Text GLabel 7700 3850 0    60   Input ~ 0
E5_STEP
Text GLabel 7700 4000 0    60   Input ~ 0
E5_DIR
Text GLabel 7700 4150 0    60   Input ~ 0
E5_EN
Text GLabel 7700 4300 0    60   Input ~ 0
HEATER6
Text GLabel 7700 1600 0    60   Input ~ 0
E2_STEP
Text GLabel 7700 1750 0    60   Input ~ 0
E2_DIR
Text GLabel 7700 2050 0    60   Input ~ 0
HEATER3
Text GLabel 7700 2800 0    60   Input ~ 0
HEATER4
Text GLabel 7700 3550 0    60   Input ~ 0
HEATER5
Text GLabel 7700 1900 0    60   Input ~ 0
E2_EN
Text GLabel 7700 5650 0    60   BiDi ~ 0
SPI1_SCK_BUFF_EXP
Text GLabel 7700 6550 0    60   Output ~ 0
THERMISTOR6
Text GLabel 7700 6100 0    60   Output ~ 0
THERMISTOR3
Text GLabel 7700 6250 0    60   Output ~ 0
THERMISTOR4
Text GLabel 7700 6400 0    60   Output ~ 0
THERMISTOR5
Text GLabel 7700 2350 0    60   Input ~ 0
E3_STEP
Text GLabel 7700 3100 0    60   Input ~ 0
E4_STEP
Text GLabel 7700 2500 0    60   Input ~ 0
E3_DIR
Text GLabel 7700 3250 0    60   Input ~ 0
E4_DIR
Text GLabel 7700 2650 0    60   Input ~ 0
E3_EN
Text GLabel 7700 3400 0    60   Input ~ 0
E4_EN
Text GLabel 7700 1450 0    60   Input ~ 0
E2_STOP
Text GLabel 7700 2200 0    60   Input ~ 0
E3_STOP
Text GLabel 7700 2950 0    60   Input ~ 0
E4_STOP
Text GLabel 7700 5500 0    60   BiDi ~ 0
TIOA1_BUFF_EXP
Text GLabel 7700 7900 0    60   BiDi ~ 0
SPI0_SCK
$Comp
L CONN_4 J6
U 1 1 568448F7
P 5100 4350
F 0 "J6" H 5100 4600 50  0000 C CNN
F 1 "E1 MOT" V 5250 4350 50  0000 C CNN
F 2 "" H 5100 4350 60  0001 C CNN
F 3 "" H 5100 4350 60  0001 C CNN
	1    5100 4350
	1    0    0    -1  
$EndComp
$Comp
L CONN_3 J35
U 1 1 5684491A
P 5050 8250
F 0 "J35" V 5000 8250 50  0000 C CNN
F 1 "E1_STOP" V 5200 8250 40  0000 C CNN
F 2 "" H 5050 8250 60  0001 C CNN
F 3 "" H 5050 8250 60  0001 C CNN
	1    5050 8250
	1    0    0    -1  
$EndComp
$Comp
L CONN_3 J34
U 1 1 56844970
P 5050 7700
F 0 "J34" V 5000 7700 50  0000 C CNN
F 1 "E0_STOP" V 5200 7700 40  0000 C CNN
F 2 "" H 5050 7700 60  0001 C CNN
F 3 "" H 5050 7700 60  0001 C CNN
	1    5050 7700
	1    0    0    -1  
$EndComp
$Comp
L CONN_3 J33
U 1 1 568449A8
P 5050 7150
F 0 "J33" V 5000 7150 50  0000 C CNN
F 1 "X_STOP" V 5200 7150 40  0000 C CNN
F 2 "" H 5050 7150 60  0001 C CNN
F 3 "" H 5050 7150 60  0001 C CNN
	1    5050 7150
	1    0    0    -1  
$EndComp
$Comp
L CONN_3 J32
U 1 1 568449AE
P 5050 6600
F 0 "J32" V 5000 6600 50  0000 C CNN
F 1 "Y_STOP" V 5200 6600 40  0000 C CNN
F 2 "" H 5050 6600 60  0001 C CNN
F 3 "" H 5050 6600 60  0001 C CNN
	1    5050 6600
	1    0    0    -1  
$EndComp
$Comp
L CONN_3 J19
U 1 1 568449B4
P 5050 6100
F 0 "J19" V 5000 6100 50  0000 C CNN
F 1 "Z_STOP" V 5200 6100 40  0000 C CNN
F 2 "" H 5050 6100 60  0001 C CNN
F 3 "" H 5050 6100 60  0001 C CNN
	1    5050 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 6200 3600 8500
Wire Wire Line
	3600 8350 4700 8350
Wire Wire Line
	3600 7800 4700 7800
Connection ~ 3600 8350
Wire Wire Line
	3600 7250 4700 7250
Connection ~ 3600 7800
Wire Wire Line
	3600 6700 4700 6700
Connection ~ 3600 7250
Wire Wire Line
	3600 6200 4700 6200
Connection ~ 3600 6700
Wire Wire Line
	3700 5800 3700 8250
Wire Wire Line
	3700 6100 4700 6100
Wire Wire Line
	3700 6600 4700 6600
Connection ~ 3700 6100
Wire Wire Line
	3700 7150 4700 7150
Connection ~ 3700 6600
Wire Wire Line
	3700 7700 4700 7700
Connection ~ 3700 7150
Wire Wire Line
	3700 8250 4700 8250
Connection ~ 3700 7700
Wire Wire Line
	4550 8150 4700 8150
Wire Wire Line
	4550 7600 4700 7600
Wire Wire Line
	4550 7050 4700 7050
Wire Wire Line
	4550 6500 4700 6500
Wire Wire Line
	4550 6000 4700 6000
$Comp
L CONN_4 J10
U 1 1 56845A17
P 5100 3650
F 0 "J10" H 5100 3900 50  0000 C CNN
F 1 "E0 MOT" V 5250 3650 50  0000 C CNN
F 2 "" H 5100 3650 60  0001 C CNN
F 3 "" H 5100 3650 60  0001 C CNN
	1    5100 3650
	1    0    0    -1  
$EndComp
$Comp
L CONN_4 J9
U 1 1 56845A1D
P 5100 2950
F 0 "J9" H 5100 3200 50  0000 C CNN
F 1 "X MOT" V 5250 2950 50  0000 C CNN
F 2 "" H 5100 2950 60  0001 C CNN
F 3 "" H 5100 2950 60  0001 C CNN
	1    5100 2950
	1    0    0    -1  
$EndComp
$Comp
L CONN_4 J8
U 1 1 56845A23
P 5100 2250
F 0 "J8" H 5100 2500 50  0000 C CNN
F 1 "Y MOT" V 5250 2250 50  0000 C CNN
F 2 "" H 5100 2250 60  0001 C CNN
F 3 "" H 5100 2250 60  0001 C CNN
	1    5100 2250
	1    0    0    -1  
$EndComp
$Comp
L CONN_4 J7
U 1 1 56845A29
P 4800 1350
F 0 "J7" H 4800 1600 50  0000 C CNN
F 1 "Z B" V 4950 1350 50  0000 C CNN
F 2 "" H 4800 1350 60  0001 C CNN
F 3 "" H 4800 1350 60  0001 C CNN
	1    4800 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 2550 4550 2400
Wire Wire Line
	4550 2400 4750 2400
Wire Wire Line
	4450 2250 4450 2200
Wire Wire Line
	4450 2200 4750 2200
Wire Wire Line
	4500 2400 4500 2300
Wire Wire Line
	4500 2300 4750 2300
Wire Wire Line
	4250 2100 4750 2100
Wire Wire Line
	4250 2250 4450 2250
Wire Wire Line
	4250 2400 4500 2400
Wire Wire Line
	4250 2550 4550 2550
Wire Wire Line
	4550 3250 4550 3100
Wire Wire Line
	4550 3100 4750 3100
Wire Wire Line
	4450 2950 4450 2900
Wire Wire Line
	4450 2900 4750 2900
Wire Wire Line
	4500 3100 4500 3000
Wire Wire Line
	4500 3000 4750 3000
Wire Wire Line
	4250 2800 4750 2800
Wire Wire Line
	4250 2950 4450 2950
Wire Wire Line
	4250 3100 4500 3100
Wire Wire Line
	4250 3250 4550 3250
Wire Wire Line
	4550 3950 4550 3800
Wire Wire Line
	4550 3800 4750 3800
Wire Wire Line
	4450 3650 4450 3600
Wire Wire Line
	4450 3600 4750 3600
Wire Wire Line
	4500 3800 4500 3700
Wire Wire Line
	4500 3700 4750 3700
Wire Wire Line
	4250 3500 4750 3500
Wire Wire Line
	4250 3650 4450 3650
Wire Wire Line
	4250 3800 4500 3800
Wire Wire Line
	4250 3950 4550 3950
Wire Wire Line
	4550 4650 4550 4500
Wire Wire Line
	4550 4500 4750 4500
Wire Wire Line
	4450 4350 4450 4300
Wire Wire Line
	4450 4300 4750 4300
Wire Wire Line
	4500 4500 4500 4400
Wire Wire Line
	4500 4400 4750 4400
Wire Wire Line
	4250 4200 4750 4200
Wire Wire Line
	4250 4350 4450 4350
Wire Wire Line
	4250 4500 4500 4500
Wire Wire Line
	4250 4650 4550 4650
Wire Wire Line
	1550 3600 1400 3600
Wire Notes Line
	700  700  3100 700 
Wire Notes Line
	3100 700  3100 2700
Wire Notes Line
	3100 2700 700  2700
Wire Notes Line
	700  2700 700  700 
Text Notes 1100 850  2    60   ~ 0
POWER
Wire Notes Line
	700  2900 3100 2900
Wire Notes Line
	3100 2900 3100 6950
Wire Notes Line
	3100 6950 700  6950
Wire Notes Line
	700  6950 700  2900
Text Notes 800  3050 0    60   ~ 0
Heater and Fans
Wire Notes Line
	3300 8750 3300 10750
Wire Notes Line
	3300 10750 5700 10750
Wire Notes Line
	5700 10750 5700 8750
Wire Notes Line
	5700 8750 3300 8750
Text Notes 3400 8900 0    60   ~ 0
Temperature
Wire Notes Line
	3300 700  3300 4850
Wire Notes Line
	3300 4850 5900 4850
Wire Notes Line
	5900 4850 5900 700 
Wire Notes Line
	5900 700  3300 700 
Text Notes 3350 850  0    60   ~ 0
Motors
Wire Notes Line
	3300 5050 5900 5050
Wire Notes Line
	5900 5050 5900 8650
Wire Notes Line
	5900 8650 3300 8650
Wire Notes Line
	3300 8650 3300 5050
Text Notes 3350 5200 0    60   ~ 0
Endstops
Wire Notes Line
	6100 700  6100 8650
Wire Notes Line
	6100 8650 10850 8650
Wire Notes Line
	10850 8650 10850 700 
Wire Notes Line
	10850 700  6100 700 
Text Notes 6200 850  0    60   ~ 0
Expansion &\nMiscellaneous
$Comp
L GND #PWR033
U 1 1 56846E9B
P 10250 3200
AR Path="/56846E9B" Ref="#PWR033"  Part="1" 
AR Path="/50656780/56846E9B" Ref="#PWR033"  Part="1" 
F 0 "#PWR033" H 10250 3200 30  0001 C CNN
F 1 "GND" H 10250 3130 30  0001 C CNN
F 2 "" H 10250 3200 60  0001 C CNN
F 3 "" H 10250 3200 60  0001 C CNN
	1    10250 3200
	1    0    0    -1  
$EndComp
Text GLabel 10250 3400 2    60   BiDi ~ 0
SPI0_SCK
Text GLabel 10250 3550 2    60   BiDi ~ 0
SPI0_MISO
Text GLabel 10250 3700 2    60   Output ~ 0
+3.3V
$Comp
L CONN_4 J36
U 1 1 56847679
P 5550 1350
F 0 "J36" H 5550 1600 50  0000 C CNN
F 1 "Z A" V 5700 1350 50  0000 C CNN
F 2 "" H 5550 1350 60  0001 C CNN
F 3 "" H 5550 1350 60  0001 C CNN
	1    5550 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 1450 4350 1450
Wire Wire Line
	4350 1450 4350 1400
Wire Wire Line
	4250 900  5200 900 
Wire Wire Line
	5200 900  5200 1200
Wire Wire Line
	4250 1750 5200 1750
Wire Wire Line
	5200 1750 5200 1500
Wire Wire Line
	5200 1400 5050 1400
Wire Wire Line
	5050 1400 5050 1600
Wire Wire Line
	5050 1600 4400 1600
Wire Wire Line
	4400 1600 4400 1500
Wire Wire Line
	4400 1500 4450 1500
Wire Wire Line
	5200 1300 5000 1300
Wire Wire Line
	5000 1300 5000 1000
Wire Wire Line
	5000 1000 4400 1000
Wire Wire Line
	4400 1000 4400 1200
Wire Wire Line
	4400 1200 4450 1200
$Comp
L GND #PWR034
U 1 1 5686D8F2
P 7200 1000
AR Path="/5686D8F2" Ref="#PWR034"  Part="1" 
AR Path="/50656780/5686D8F2" Ref="#PWR034"  Part="1" 
F 0 "#PWR034" H 7200 1000 30  0001 C CNN
F 1 "GND" H 7200 930 30  0001 C CNN
F 2 "" H 7200 1000 60  0001 C CNN
F 3 "" H 7200 1000 60  0001 C CNN
	1    7200 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 950  7200 1000
$Comp
L CONN_5X2 P1
U 1 1 5686E16E
P 9700 1800
F 0 "P1" H 9700 2100 60  0000 C CNN
F 1 "CONN_SD" V 9700 1800 50  0000 C CNN
F 2 "~" H 9700 1800 60  0000 C CNN
F 3 "~" H 9700 1800 60  0000 C CNN
	1    9700 1800
	1    0    0    -1  
$EndComp
$Comp
L CONN_5X2 P2
U 1 1 5686E2DF
P 9700 2500
F 0 "P2" H 9700 2800 60  0000 C CNN
F 1 "CONN_LCD" V 9700 2500 50  0000 C CNN
F 2 "~" H 9700 2500 60  0000 C CNN
F 3 "~" H 9700 2500 60  0000 C CNN
	1    9700 2500
	1    0    0    -1  
$EndComp
Text GLabel 9200 1800 0    60   BiDi ~ 0
SPI0_MOSI
Text GLabel 10250 1800 2    60   BiDi ~ 0
SPI0_MISO
Text GLabel 10250 1650 2    60   BiDi ~ 0
SPI0_SCK
Text GLabel 9200 1650 0    60   BiDi ~ 0
SPI0_CS0
Wire Wire Line
	10100 1350 10400 1350
$Comp
L GND #PWR035
U 1 1 5686E302
P 10400 1400
AR Path="/5686E302" Ref="#PWR035"  Part="1" 
AR Path="/50656780/5686E302" Ref="#PWR035"  Part="1" 
F 0 "#PWR035" H 10400 1400 30  0001 C CNN
F 1 "GND" H 10400 1330 30  0001 C CNN
F 2 "" H 10400 1400 60  0001 C CNN
F 3 "" H 10400 1400 60  0001 C CNN
	1    10400 1400
	-1   0    0    -1  
$EndComp
Wire Wire Line
	10400 1350 10400 1400
Text GLabel 10250 1950 2    60   Output ~ 0
+3.3V
NoConn ~ 9300 1600
NoConn ~ 9300 2000
NoConn ~ 10100 2000
Wire Wire Line
	10100 1350 10100 1600
Wire Wire Line
	10100 1700 10200 1700
Wire Wire Line
	10200 1700 10200 1650
Wire Wire Line
	10200 1650 10250 1650
Wire Wire Line
	10250 1800 10100 1800
Wire Wire Line
	9200 1800 9300 1800
Wire Wire Line
	10100 1900 10200 1900
Wire Wire Line
	10200 1900 10200 1950
Wire Wire Line
	10200 1950 10250 1950
Wire Wire Line
	9200 1650 9250 1650
Wire Wire Line
	9250 1650 9250 1700
Wire Wire Line
	9250 1700 9300 1700
Text GLabel 9200 1950 0    60   Input ~ 0
ENC_SW
Wire Wire Line
	9200 1950 9250 1950
Wire Wire Line
	9250 1950 9250 1900
Wire Wire Line
	9250 1900 9300 1900
Text GLabel 10250 2500 2    60   Input ~ 0
LCD_RS
Text GLabel 9150 2350 0    60   Output ~ 0
ENC_B
Text GLabel 10250 2350 2    60   Output ~ 0
ENC_A
Text GLabel 9150 2200 0    60   Output ~ 0
+3.3V
Wire Wire Line
	10100 2150 10400 2150
$Comp
L GND #PWR036
U 1 1 5686EDE8
P 10400 2200
AR Path="/5686EDE8" Ref="#PWR036"  Part="1" 
AR Path="/50656780/5686EDE8" Ref="#PWR036"  Part="1" 
F 0 "#PWR036" H 10400 2200 30  0001 C CNN
F 1 "GND" H 10400 2130 30  0001 C CNN
F 2 "" H 10400 2200 60  0001 C CNN
F 3 "" H 10400 2200 60  0001 C CNN
	1    10400 2200
	-1   0    0    -1  
$EndComp
Wire Wire Line
	10400 2150 10400 2200
Wire Wire Line
	10100 2150 10100 2300
Text GLabel 10250 2650 2    60   Input ~ 0
LCD_E
Wire Wire Line
	10100 2400 10200 2400
Wire Wire Line
	10200 2400 10200 2350
Wire Wire Line
	10200 2350 10250 2350
Wire Wire Line
	10100 2500 10250 2500
Wire Wire Line
	10100 2600 10200 2600
Wire Wire Line
	10200 2600 10200 2650
Wire Wire Line
	10200 2650 10250 2650
Text GLabel 10250 2800 2    60   Input ~ 0
LCD_DB4
Wire Wire Line
	10100 2700 10150 2700
Wire Wire Line
	10150 2700 10150 2800
Wire Wire Line
	10150 2800 10250 2800
Text GLabel 9150 2800 0    60   Input ~ 0
LCD_DB5
Text GLabel 9150 2650 0    60   Input ~ 0
LCD_DB6
Text GLabel 9150 2500 0    60   Input ~ 0
LCD_DB7
Wire Wire Line
	9150 2200 9300 2200
Wire Wire Line
	9300 2200 9300 2300
Wire Wire Line
	9150 2350 9250 2350
Wire Wire Line
	9250 2350 9250 2400
Wire Wire Line
	9250 2400 9300 2400
Wire Wire Line
	9150 2500 9300 2500
Wire Wire Line
	9150 2650 9250 2650
Wire Wire Line
	9250 2650 9250 2600
Wire Wire Line
	9250 2600 9300 2600
Wire Wire Line
	9150 2800 9300 2800
Wire Wire Line
	9300 2800 9300 2700
$Comp
L GND #PWR037
U 1 1 56893024
P 9700 7150
AR Path="/56893024" Ref="#PWR037"  Part="1" 
AR Path="/50656780/56893024" Ref="#PWR037"  Part="1" 
F 0 "#PWR037" H 9700 7150 30  0001 C CNN
F 1 "GND" H 9700 7080 30  0001 C CNN
F 2 "" H 9700 7150 60  0001 C CNN
F 3 "" H 9700 7150 60  0001 C CNN
	1    9700 7150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9700 7150 9700 7050
Wire Wire Line
	9700 7050 10000 7050
Wire Wire Line
	10000 7050 10000 7300
Text GLabel 9850 7450 0    60   Output ~ 0
UTXD1_CONN
Text GLabel 9850 7300 0    60   Input ~ 0
URXD1_CONN
Wire Wire Line
	9850 7450 9900 7450
Wire Wire Line
	9900 7450 9900 7500
Wire Wire Line
	9900 7500 10000 7500
Wire Wire Line
	9850 7300 9950 7300
Wire Wire Line
	9950 7300 9950 7400
Wire Wire Line
	9950 7400 10000 7400
Text Notes 9050 7700 0    60   ~ 0
J39 Not populated in production boards
Text GLabel 9150 3400 0    60   Input ~ 0
SPI0_CS1
Text GLabel 9150 3550 0    60   BiDi ~ 0
SPI0_MOSI
Text GLabel 9150 3250 0    60   Input ~ 0
SPI0_CS2
Text GLabel 9150 3700 0    60   Input ~ 0
CS3
$Comp
L CONN_5X2 J37
U 1 1 568FF45C
P 9700 3550
F 0 "J37" H 9700 3850 60  0000 C CNN
F 1 "SPI0" V 9700 3550 50  0000 C CNN
F 2 "~" H 9700 3550 60  0000 C CNN
F 3 "~" H 9700 3550 60  0000 C CNN
	1    9700 3550
	1    0    0    -1  
$EndComp
Text GLabel 9150 3850 0    60   Input ~ 0
CS4
Wire Wire Line
	9150 3250 9300 3250
Wire Wire Line
	9300 3250 9300 3350
Wire Wire Line
	10100 3350 10100 3100
Wire Wire Line
	10100 3100 10250 3100
Wire Wire Line
	9150 3400 9250 3400
Wire Wire Line
	9250 3400 9250 3450
Wire Wire Line
	9250 3450 9300 3450
Wire Wire Line
	9150 3550 9300 3550
Wire Wire Line
	9150 3700 9250 3700
Wire Wire Line
	9250 3700 9250 3650
Wire Wire Line
	9250 3650 9300 3650
Wire Wire Line
	9150 3850 9300 3850
Wire Wire Line
	9300 3850 9300 3750
Wire Wire Line
	10250 3700 10150 3700
Wire Wire Line
	10150 3700 10150 3650
Wire Wire Line
	10150 3650 10100 3650
Wire Wire Line
	10250 3400 10150 3400
Wire Wire Line
	10150 3400 10150 3450
Wire Wire Line
	10150 3450 10100 3450
Wire Wire Line
	10250 3550 10100 3550
Wire Wire Line
	10250 3100 10250 3200
NoConn ~ 10100 3750
Text GLabel 7700 8350 0    60   Input ~ 0
CS5
$Comp
L CONN3 J39
U 1 1 5713BEA8
P 10350 7400
F 0 "J39" H 10300 7600 50  0000 C CNN
F 1 "ESP_COMMS" V 10500 7400 40  0000 C CNN
F 2 "~" H 10350 7400 60  0000 C CNN
F 3 "~" H 10350 7400 60  0000 C CNN
	1    10350 7400
	1    0    0    -1  
$EndComp
Text GLabel 7700 4450 0    60   Output ~ 0
E6_STOP
Text GLabel 7700 4600 0    60   Input ~ 0
E6_STEP
Text GLabel 7700 4750 0    60   Input ~ 0
E6_DIR
Text GLabel 7700 4900 0    60   Input ~ 0
E6_EN
Text GLabel 7700 5050 0    60   Input ~ 0
HEATER7
Text GLabel 9700 5050 0    60   Output ~ 0
+5V
Wire Wire Line
	9200 5000 9400 5000
Wire Wire Line
	9400 5000 9400 5200
Wire Wire Line
	9400 5200 9950 5200
$Comp
L GND #PWR038
U 1 1 5714CD6A
P 9200 5050
AR Path="/5714CD6A" Ref="#PWR038"  Part="1" 
AR Path="/50656780/5714CD6A" Ref="#PWR038"  Part="1" 
F 0 "#PWR038" H 9200 5050 30  0001 C CNN
F 1 "GND" H 9200 4980 30  0001 C CNN
F 2 "" H 9200 5050 60  0001 C CNN
F 3 "" H 9200 5050 60  0001 C CNN
	1    9200 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	9200 5000 9200 5050
Wire Wire Line
	9700 5050 9800 5050
Wire Wire Line
	9800 5050 9800 5100
Wire Wire Line
	9800 5100 9950 5100
Wire Wire Line
	9700 5300 9950 5300
Wire Wire Line
	9700 5450 9800 5450
Wire Wire Line
	9800 5450 9800 5400
Wire Wire Line
	9800 5400 9950 5400
Text GLabel 7700 7300 0    60   Output ~ 0
+3.3V
Wire Wire Line
	6950 6950 7150 6950
Wire Wire Line
	7150 6950 7150 7150
$Comp
L GND #PWR039
U 1 1 5714D0D9
P 6950 7000
AR Path="/5714D0D9" Ref="#PWR039"  Part="1" 
AR Path="/50656780/5714D0D9" Ref="#PWR039"  Part="1" 
F 0 "#PWR039" H 6950 7000 30  0001 C CNN
F 1 "GND" H 6950 6930 30  0001 C CNN
F 2 "" H 6950 7000 60  0001 C CNN
F 3 "" H 6950 7000 60  0001 C CNN
	1    6950 7000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6950 6950 6950 7000
$Comp
L GND #PWR040
U 1 1 5714D332
P 6850 5300
AR Path="/5714D332" Ref="#PWR040"  Part="1" 
AR Path="/50656780/5714D332" Ref="#PWR040"  Part="1" 
F 0 "#PWR040" H 6850 5300 30  0001 C CNN
F 1 "GND" H 6850 5230 30  0001 C CNN
F 2 "" H 6850 5300 60  0001 C CNN
F 3 "" H 6850 5300 60  0001 C CNN
	1    6850 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 5300 6850 5150
Wire Wire Line
	6850 5150 7050 5150
Wire Wire Line
	7050 5150 7050 5350
Text GLabel 7700 7000 0    60   Input ~ 0
ADVREF
Text GLabel 7700 6700 0    60   Output ~ 0
THERMISTOR7
Wire Wire Line
	7050 5350 7950 5350
Wire Wire Line
	7700 5500 7950 5500
Wire Wire Line
	7950 7300 7700 7300
Text GLabel 1400 5950 0    60   Input ~ 0
V_FAN
Text GLabel 1400 5800 0    60   Input ~ 0
FAN2-
Wire Wire Line
	1400 5950 1550 5950
Wire Wire Line
	1550 5800 1400 5800
$Comp
L CONN2 J2
U 1 1 571B8385
P 1900 5800
F 0 "J2" H 1900 5700 40  0000 C CNN
F 1 "FAN2" V 2050 5850 40  0000 C CNN
F 2 "" H 1900 5800 60  0001 C CNN
F 3 "" H 1900 5800 60  0001 C CNN
	1    1900 5800
	1    0    0    1   
$EndComp
Wire Wire Line
	1550 5950 1550 5900
Text GLabel 7700 5200 0    60   BiDi ~ 0
PB6/TMS
$EndSCHEMATC
