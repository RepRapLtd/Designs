EESchema Schematic File Version 2
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
$Descr A2 23386 16535
encoding utf-8
Sheet 7 7
Title "Duet Wifi"
Date "02 Jul 2016"
Rev "1.0"
Comp "Think3DPrint3D, Escher 3D"
Comment1 "CERN OSH License 1.2"
Comment2 "http://www.ohwr.org/attachments/2388/cern_ohl_v_1_2.txt"
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 8350 9950 0    50   Input ~ 0
VSSA
$Comp
L CRYSTAL_4PIN X2
U 1 1 51758028
P 14450 14950
F 0 "X2" H 14450 15200 60  0000 C CNN
F 1 "CRYSTAL_4PIN" H 14450 14800 60  0000 C CNN
F 2 "complib:Xtal_5x3.2" H 14450 14950 60  0001 C CNN
F 3 "" H 14450 14950 60  0001 C CNN
F 4 "12MHz" H 14450 15100 60  0000 C CNN "Frequency"
	1    14450 14950
	1    0    0    1   
$EndComp
Text Notes 13400 12650 0    60   ~ 0
(approx)100 kΩ pullup internally
Text GLabel 7950 9700 0    50   Input ~ 0
Z_PROBE_IN
Text GLabel 13000 10150 2    50   Input ~ 0
E1_STOP
Text Label 10100 4550 0    60   ~ 0
VDDIO
Text Label 11900 4550 0    60   ~ 0
VDDCORE
Text GLabel 10000 15150 0    60   Input ~ 0
VSSA
$Comp
L SW_TACT S2
U 1 1 50F1C331
P 16750 12700
F 0 "S2" H 16900 12550 60  0000 C CNN
F 1 "ERASE" H 16750 12900 60  0000 C CNN
F 2 "FE Footprints:SW_SIDE_1_lugs" H 16750 12700 60  0001 C CNN
F 3 "" H 16750 12700 60  0001 C CNN
	1    16750 12700
	0    -1   -1   0   
$EndComp
Text GLabel 16750 12400 1    60   Input ~ 0
+3.3V
$Comp
L R_SMALL R52
U 1 1 50F1B6A2
P 19700 12550
F 0 "R52" V 19775 12558 50  0000 C CNN
F 1 "DNP 100K" V 19632 12562 50  0000 C CNN
F 2 "complib:R_0603" H 19700 12550 60  0001 C CNN
F 3 "" H 19700 12550 60  0001 C CNN
	1    19700 12550
	1    0    0    -1  
$EndComp
$Comp
L R_SMALL R49
U 1 1 50F1B672
P 19450 12550
F 0 "R49" V 19525 12558 50  0000 C CNN
F 1 "DNP 100K" V 19382 12562 50  0000 C CNN
F 2 "complib:R_0603" H 19450 12550 60  0001 C CNN
F 3 "" H 19450 12550 60  0001 C CNN
	1    19450 12550
	1    0    0    -1  
$EndComp
$Comp
L R_SMALL R36
U 1 1 50F1B65F
P 18950 12550
F 0 "R36" V 19025 12558 50  0000 C CNN
F 1 "DNP 100K" V 18882 12562 50  0000 C CNN
F 2 "complib:R_0603" H 18950 12550 60  0001 C CNN
F 3 "" H 18950 12550 60  0001 C CNN
	1    18950 12550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR063
U 1 1 50F1B3A2
P 8400 4800
AR Path="/50F1B3A2" Ref="#PWR063"  Part="1" 
AR Path="/50523307/50F1B3A2" Ref="#PWR064"  Part="1" 
F 0 "#PWR064" H 8400 4800 30  0001 C CNN
F 1 "GND" H 8400 4730 30  0001 C CNN
F 2 "" H 8400 4800 60  0001 C CNN
F 3 "" H 8400 4800 60  0001 C CNN
	1    8400 4800
	1    0    0    -1  
$EndComp
$Comp
L C_SMALL C64
U 1 1 50F1B031
P 11050 2900
F 0 "C64" H 11075 2975 50  0000 L CNN
F 1 "0u1" H 11050 2825 50  0000 L CNN
F 2 "complib:C_0603" H 11050 2900 60  0001 C CNN
F 3 "" H 11050 2900 60  0001 C CNN
	1    11050 2900
	1    0    0    -1  
$EndComp
Text Notes 12000 2650 2    50   ~ 0
VDDPLL
$Comp
L GND #PWR064
U 1 1 50F1AE7F
P 11900 3850
AR Path="/50F1AE7F" Ref="#PWR064"  Part="1" 
AR Path="/50523307/50F1AE7F" Ref="#PWR065"  Part="1" 
F 0 "#PWR065" H 11900 3850 30  0001 C CNN
F 1 "GND" H 11900 3780 30  0001 C CNN
F 2 "" H 11900 3850 60  0001 C CNN
F 3 "" H 11900 3850 60  0001 C CNN
	1    11900 3850
	1    0    0    -1  
$EndComp
$Comp
L L_MINI L6
U 1 1 50F1ADDF
P 11600 2700
F 0 "L6" H 11525 2650 30  0000 C CNN
F 1 "10uH 100Mhz" H 11550 2750 22  0000 C CNN
F 2 "complib:R_0603" H 11600 2700 60  0001 C CNN
F 3 "" H 11600 2700 60  0001 C CNN
	1    11600 2700
	1    0    0    -1  
$EndComp
$Comp
L C_SMALL C67
U 1 1 50F1ADC9
P 12000 2900
F 0 "C67" H 12025 2975 50  0000 L CNN
F 1 "0u1" H 12000 2825 50  0000 L CNN
F 2 "complib:C_0603" H 12000 2900 60  0001 C CNN
F 3 "" H 12000 2900 60  0001 C CNN
	1    12000 2900
	1    0    0    -1  
$EndComp
$Comp
L C_SMALL C66
U 1 1 50F1ADC8
P 11800 3550
F 0 "C66" H 11825 3625 50  0000 L CNN
F 1 "4u7" H 11800 3475 50  0000 L CNN
F 2 "FE Footprints:C_0805" H 11800 3550 60  0001 C CNN
F 3 "MLCC or Tantalum" H 11800 3550 60  0001 C CNN
	1    11800 3550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR065
U 1 1 50F1AB2F
P 13300 4500
AR Path="/50F1AB2F" Ref="#PWR065"  Part="1" 
AR Path="/50523307/50F1AB2F" Ref="#PWR066"  Part="1" 
F 0 "#PWR066" H 13300 4500 30  0001 C CNN
F 1 "GND" H 13300 4430 30  0001 C CNN
F 2 "" H 13300 4500 60  0001 C CNN
F 3 "" H 13300 4500 60  0001 C CNN
	1    13300 4500
	1    0    0    -1  
$EndComp
$Comp
L C_SMALL C72
U 1 1 50F1AAC9
P 13900 4250
F 0 "C72" H 13925 4325 50  0000 L CNN
F 1 "0u1" H 13900 4175 50  0000 L CNN
F 2 "complib:C_0603" H 13900 4250 60  0001 C CNN
F 3 "" H 13900 4250 60  0001 C CNN
	1    13900 4250
	1    0    0    -1  
$EndComp
$Comp
L C_SMALL C70
U 1 1 50F1AAC6
P 13400 4250
F 0 "C70" H 13425 4325 50  0000 L CNN
F 1 "0u1" H 13400 4175 50  0000 L CNN
F 2 "complib:C_0603" H 13400 4250 60  0001 C CNN
F 3 "" H 13400 4250 60  0001 C CNN
	1    13400 4250
	1    0    0    -1  
$EndComp
$Comp
L C_SMALL C71
U 1 1 50F1AAC5
P 13650 4250
F 0 "C71" H 13675 4325 50  0000 L CNN
F 1 "0u1" H 13650 4175 50  0000 L CNN
F 2 "complib:C_0603" H 13650 4250 60  0001 C CNN
F 3 "" H 13650 4250 60  0001 C CNN
	1    13650 4250
	1    0    0    -1  
$EndComp
Text Notes 13400 3950 2    50   ~ 0
VDDCORE
Text Notes 7350 4050 2    50   ~ 0
VDDIO
Text Notes 10550 3350 2    50   ~ 0
VDDIN
$Comp
L C_SMALL C47
U 1 1 50F1A935
P 10350 3550
F 0 "C47" H 10375 3625 50  0000 L CNN
F 1 "10u" H 10350 3475 50  0000 L CNN
F 2 "FE Footprints:C_0805" H 10350 3550 60  0001 C CNN
F 3 "MLCC or Tantalum" H 10350 3550 60  0001 C CNN
	1    10350 3550
	1    0    0    -1  
$EndComp
$Comp
L C_SMALL C68
U 1 1 50F1A8A0
P 11650 4250
F 0 "C68" H 11675 4325 50  0000 L CNN
F 1 "2u2" H 11650 4175 50  0000 L CNN
F 2 "complib:C_0603" H 11650 4250 60  0001 C CNN
F 3 "MLCC or Tantalum" H 11650 4250 60  0001 C CNN
	1    11650 4250
	1    0    0    -1  
$EndComp
$Comp
L C_SMALL C69
U 1 1 50F1A84E
P 12700 4250
F 0 "C69" H 12725 4325 50  0000 L CNN
F 1 "0u1" H 12700 4175 50  0000 L CNN
F 2 "complib:C_0603" H 12700 4250 60  0001 C CNN
F 3 "" H 12700 4250 60  0001 C CNN
	1    12700 4250
	1    0    0    -1  
$EndComp
Text GLabel 18900 13450 0    60   BiDi ~ 0
RESET
Text GLabel 15150 12650 2    60   BiDi ~ 0
RESET
Text GLabel 14700 12050 1    60   Input ~ 0
+3.3V
Text GLabel 17900 12150 1    60   Input ~ 0
+3.3V
NoConn ~ 17900 13150
$Comp
L C_SMALL C2
U 1 1 509ADAE1
P 14700 12350
F 0 "C2" H 14725 12425 50  0000 L CNN
F 1 "0u01" H 14700 12275 50  0000 L CNN
F 2 "complib:C_0603" H 14700 12350 60  0001 C CNN
F 3 "" H 14700 12350 60  0001 C CNN
	1    14700 12350
	1    0    0    -1  
$EndComp
$Comp
L SW_TACT S1
U 1 1 5075E99F
P 14500 13150
F 0 "S1" H 14650 13000 60  0000 C CNN
F 1 "RESET" H 14500 13350 60  0000 C CNN
F 2 "FE Footprints:SW_SIDE_1_lugs" H 14500 13150 60  0001 C CNN
F 3 "" H 14500 13150 60  0001 C CNN
	1    14500 13150
	0    -1   -1   0   
$EndComp
$Comp
L C_SMALL C45
U 1 1 50657171
P 14050 15300
F 0 "C45" H 14075 15375 50  0000 L CNN
F 1 "10p" H 14050 15225 50  0000 L CNN
F 2 "complib:C_0603" H 14050 15300 60  0001 C CNN
F 3 "" H 14050 15300 60  0001 C CNN
	1    14050 15300
	-1   0    0    -1  
$EndComp
$Comp
L C_SMALL C44
U 1 1 5065716C
P 14900 15300
F 0 "C44" H 14925 15375 50  0000 L CNN
F 1 "10p" H 14900 15225 50  0000 L CNN
F 2 "complib:C_0603" H 14900 15300 60  0001 C CNN
F 3 "" H 14900 15300 60  0001 C CNN
	1    14900 15300
	-1   0    0    -1  
$EndComp
$Comp
L C_SMALL C52
U 1 1 50657150
P 12900 4250
F 0 "C52" H 12925 4325 50  0000 L CNN
F 1 "0u1" H 12900 4175 50  0000 L CNN
F 2 "complib:C_0603" H 12900 4250 60  0001 C CNN
F 3 "" H 12900 4250 60  0001 C CNN
	1    12900 4250
	1    0    0    -1  
$EndComp
$Comp
L C_SMALL C51
U 1 1 5065714E
P 10600 3550
F 0 "C51" H 10625 3625 50  0000 L CNN
F 1 "0u1" H 10600 3475 50  0000 L CNN
F 2 "complib:C_0603" H 10600 3550 60  0001 C CNN
F 3 "" H 10600 3550 60  0001 C CNN
	1    10600 3550
	1    0    0    -1  
$EndComp
$Comp
L C_SMALL C50
U 1 1 50657145
P 9200 4400
F 0 "C50" H 9225 4475 50  0000 L CNN
F 1 "0u1" H 9200 4325 50  0000 L CNN
F 2 "complib:C_0603" H 9200 4400 60  0001 C CNN
F 3 "" H 9200 4400 60  0001 C CNN
	1    9200 4400
	1    0    0    -1  
$EndComp
$Comp
L C_SMALL C49
U 1 1 50657143
P 9700 4400
F 0 "C49" H 9725 4475 50  0000 L CNN
F 1 "0u1" H 9700 4325 50  0000 L CNN
F 2 "complib:C_0603" H 9700 4400 60  0001 C CNN
F 3 "" H 9700 4400 60  0001 C CNN
	1    9700 4400
	1    0    0    -1  
$EndComp
$Comp
L C_SMALL C48
U 1 1 5065713D
P 8650 4400
F 0 "C48" H 8675 4475 50  0000 L CNN
F 1 "0u1" H 8650 4325 50  0000 L CNN
F 2 "complib:C_0603" H 8650 4400 60  0001 C CNN
F 3 "" H 8650 4400 60  0001 C CNN
	1    8650 4400
	1    0    0    -1  
$EndComp
$Comp
L C_SMALL C46
U 1 1 50657104
P 8100 4400
F 0 "C46" H 8125 4475 50  0000 L CNN
F 1 "0u1" H 8100 4325 50  0000 L CNN
F 2 "complib:C_0603" H 8100 4400 60  0001 C CNN
F 3 "" H 8100 4400 60  0001 C CNN
	1    8100 4400
	1    0    0    -1  
$EndComp
$Comp
L CONN_JTAG J21
U 1 1 505F8BB9
P 18400 13050
F 0 "J21" H 18400 12750 50  0000 C CNN
F 1 "JTAG" H 18400 13350 35  0000 C CNN
F 2 "FE Footprints:MICRO_5x2" H 18400 13050 60  0001 C CNN
F 3 "" H 18400 13050 60  0001 C CNN
	1    18400 13050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR066
U 1 1 505DBB16
P 11400 15650
AR Path="/505DBB16" Ref="#PWR066"  Part="1" 
AR Path="/50523307/505DBB16" Ref="#PWR067"  Part="1" 
F 0 "#PWR067" H 11400 15650 30  0001 C CNN
F 1 "GND" H 11400 15580 30  0001 C CNN
F 2 "" H 11400 15650 60  0001 C CNN
F 3 "" H 11400 15650 60  0001 C CNN
	1    11400 15650
	1    0    0    -1  
$EndComp
Text GLabel 13000 7750 2    50   Output ~ 0
X_STEP
$Comp
L GND #PWR067
U 1 1 5057A432
P 14500 13650
AR Path="/5057A432" Ref="#PWR067"  Part="1" 
AR Path="/50523307/5057A432" Ref="#PWR068"  Part="1" 
F 0 "#PWR068" H 14500 13650 30  0001 C CNN
F 1 "GND" H 14500 13580 30  0001 C CNN
F 2 "" H 14500 13650 60  0001 C CNN
F 3 "" H 14500 13650 60  0001 C CNN
	1    14500 13650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR068
U 1 1 50579E73
P 17850 13300
AR Path="/50579E73" Ref="#PWR068"  Part="1" 
AR Path="/50523307/50579E73" Ref="#PWR069"  Part="1" 
F 0 "#PWR069" H 17850 13300 30  0001 C CNN
F 1 "GND" H 17850 13230 30  0001 C CNN
F 2 "" H 17850 13300 60  0001 C CNN
F 3 "" H 17850 13300 60  0001 C CNN
	1    17850 13300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR069
U 1 1 5057957F
P 14450 15800
AR Path="/5057957F" Ref="#PWR069"  Part="1" 
AR Path="/50523307/5057957F" Ref="#PWR070"  Part="1" 
F 0 "#PWR070" H 14450 15800 30  0001 C CNN
F 1 "GND" H 14450 15730 30  0001 C CNN
F 2 "" H 14450 15800 60  0001 C CNN
F 3 "" H 14450 15800 60  0001 C CNN
	1    14450 15800
	-1   0    0    -1  
$EndComp
$Comp
L ATSAM4E8E U1
U 1 1 567A16A1
P 11200 10150
AR Path="/50523307/567A16A1" Ref="U1"  Part="1" 
AR Path="/50577C6A/567A16A1" Ref="U1"  Part="1" 
F 0 "U1" H 11200 10800 60  0000 C CNN
F 1 "ATSAM4E8E" H 11200 10650 60  0000 C CNN
F 2 "FE Footprints:LQFP144" H 11200 10500 60  0001 C CNN
F 3 "~" H 11200 10150 60  0000 C CNN
	1    11200 10150
	1    0    0    -1  
$EndComp
Text GLabel 13000 12800 2    60   Input ~ 0
ERASE
Text GLabel 16750 13050 3    60   Input ~ 0
ERASE
Text Notes 13000 12950 0    60   ~ 0
(approx)100 kΩ pulldown internally
Text GLabel 13000 13050 2    50   BiDi ~ 0
PB6/TMS
Text GLabel 13000 13200 2    50   BiDi ~ 0
PB7/TCK
Text GLabel 13000 13350 2    50   BiDi ~ 0
PB4/TDI
Text GLabel 13000 13500 2    50   BiDi ~ 0
PB5/TDO
Text GLabel 20100 12650 2    50   BiDi ~ 0
PB6/TMS
Text GLabel 20100 12850 2    50   BiDi ~ 0
PB7/TCK
Text GLabel 20100 13250 2    50   BiDi ~ 0
PB4/TDI
Text GLabel 20100 13050 2    50   BiDi ~ 0
PB5/TDO
Text GLabel 9350 9850 0    50   Output ~ 0
Z_PROBE_MOD
$Comp
L C_SMALL C62
U 1 1 567D1280
P 13100 4250
F 0 "C62" H 13125 4325 50  0000 L CNN
F 1 "0u1" H 13100 4175 50  0000 L CNN
F 2 "complib:C_0603" H 13100 4250 60  0001 C CNN
F 3 "" H 13100 4250 60  0001 C CNN
	1    13100 4250
	1    0    0    -1  
$EndComp
Text GLabel 10950 2600 0    50   Input ~ 0
ADVREF
Text GLabel 11050 2100 1    60   Input ~ 0
+3.3V
$Comp
L GND #PWR070
U 1 1 567D1646
P 11050 3150
AR Path="/567D1646" Ref="#PWR070"  Part="1" 
AR Path="/50523307/567D1646" Ref="#PWR071"  Part="1" 
F 0 "#PWR071" H 11050 3150 30  0001 C CNN
F 1 "GND" H 11050 3080 30  0001 C CNN
F 2 "" H 11050 3150 60  0001 C CNN
F 3 "" H 11050 3150 60  0001 C CNN
	1    11050 3150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR071
U 1 1 567D180B
P 11750 4450
AR Path="/567D180B" Ref="#PWR071"  Part="1" 
AR Path="/50523307/567D180B" Ref="#PWR072"  Part="1" 
F 0 "#PWR072" H 11750 4450 30  0001 C CNN
F 1 "GND" H 11750 4380 30  0001 C CNN
F 2 "" H 11750 4450 60  0001 C CNN
F 3 "" H 11750 4450 60  0001 C CNN
	1    11750 4450
	1    0    0    -1  
$EndComp
Text GLabel 9250 2950 1    60   Input ~ 0
+3.3V
$Comp
L GND #PWR072
U 1 1 567D1815
P 10350 3900
AR Path="/567D1815" Ref="#PWR072"  Part="1" 
AR Path="/50523307/567D1815" Ref="#PWR073"  Part="1" 
F 0 "#PWR073" H 10350 3900 30  0001 C CNN
F 1 "GND" H 10350 3830 30  0001 C CNN
F 2 "" H 10350 3900 60  0001 C CNN
F 3 "" H 10350 3900 60  0001 C CNN
	1    10350 3900
	1    0    0    -1  
$EndComp
$Comp
L C_SMALL C16
U 1 1 567D1B9F
P 7600 4400
F 0 "C16" H 7625 4475 50  0000 L CNN
F 1 "0u1" H 7600 4325 50  0000 L CNN
F 2 "complib:C_0603" H 7600 4400 60  0001 C CNN
F 3 "" H 7600 4400 60  0001 C CNN
	1    7600 4400
	1    0    0    -1  
$EndComp
$Comp
L C_SMALL C11
U 1 1 567D1BA5
P 7100 4400
F 0 "C11" H 7125 4475 50  0000 L CNN
F 1 "0u1" H 7100 4325 50  0000 L CNN
F 2 "complib:C_0603" H 7100 4400 60  0001 C CNN
F 3 "" H 7100 4400 60  0001 C CNN
	1    7100 4400
	1    0    0    -1  
$EndComp
$Comp
L C_SMALL C9
U 1 1 567D1BB5
P 6600 4400
F 0 "C9" H 6625 4475 50  0000 L CNN
F 1 "0u1" H 6600 4325 50  0000 L CNN
F 2 "complib:C_0603" H 6600 4400 60  0001 C CNN
F 3 "" H 6600 4400 60  0001 C CNN
	1    6600 4400
	1    0    0    -1  
$EndComp
Text GLabel 9400 5800 0    50   Input ~ 0
E2_STOP
Text GLabel 9400 5950 0    50   Input ~ 0
E3_STOP
Text GLabel 9400 6100 0    50   Input ~ 0
E4_STOP
Text GLabel 9400 6250 0    50   Input ~ 0
E5_STOP
Text GLabel 13000 10000 2    50   Input ~ 0
E0_STOP
Text GLabel 9400 7750 0    50   BiDi ~ 0
SPI0_MOSI
Text GLabel 5850 6550 0    50   Input ~ 0
THERMISTOR6
Text GLabel 9400 6700 0    50   Output ~ 0
FAN1
Text GLabel 5850 6850 0    50   Input ~ 0
THERMISTOR5
Text GLabel 5850 7000 0    50   Input ~ 0
THERMISTOR4
Text GLabel 5850 7150 0    50   Input ~ 0
THERMISTOR3
Text GLabel 4500 7300 0    50   Input ~ 0
THERMISTOR2
Text GLabel 4500 7450 0    50   Input ~ 0
THERMISTOR1
Text GLabel 4500 7600 0    50   Input ~ 0
THERMISTOR0
Text GLabel 9400 7900 0    50   BiDi ~ 0
SPI0_MISO
Text GLabel 13000 6550 2    50   BiDi ~ 0
SPI0_CS0
Text GLabel 9400 8050 0    50   Output ~ 0
HEATER1
Text GLabel 9400 8200 0    50   Output ~ 0
HEATER0
Text GLabel 9400 9100 0    50   Input ~ 0
PWR_FAIL_DET1
Text GLabel 5850 8350 0    50   Input ~ 0
THERMISTOR7
Text GLabel 13000 9550 2    50   Output ~ 0
PS_ON
Text GLabel 9400 9250 0    50   BiDi ~ 0
SPI1_MISO
Text GLabel 9400 9550 0    50   BiDi ~ 0
SPI1_MOSI
Text GLabel 9400 10300 0    50   BiDi ~ 0
MOSI
Text GLabel 9400 10450 0    50   Output ~ 0
HEATER2
Text GLabel 9400 10600 0    50   BiDi ~ 0
SPI1_SCK
Text GLabel 8550 11650 0    50   Output ~ 0
ENN
Text GLabel 9400 11350 0    50   Output ~ 0
E4_EN
Text GLabel 9400 11200 0    50   BiDi ~ 0
SPCK
Text GLabel 9400 11500 0    50   Output ~ 0
E5_EN
Text GLabel 9400 11800 0    50   Output ~ 0
E3_EN
Text GLabel 9400 11950 0    50   BiDi ~ 0
CS5
Text GLabel 9400 12100 0    50   Output ~ 0
E2_EN
Text GLabel 9400 12250 0    50   Output ~ 0
HEATER4
Text GLabel 9400 12400 0    50   Output ~ 0
LCD_E
Text GLabel 13000 6100 2    50   Output ~ 0
E1_EN
Text GLabel 9400 12700 0    50   BiDi ~ 0
MCDA2
Text GLabel 13000 9700 2    50   Output ~ 0
E0_EN
Text GLabel 13000 11350 2    50   Output ~ 0
Z_EN
Text GLabel 9400 13000 0    50   BiDi ~ 0
NPCS0
Text GLabel 9400 13300 0    50   BiDi ~ 0
UTXD0
Text GLabel 13000 11650 2    50   Output ~ 0
Y_EN
Text GLabel 9400 13600 0    50   BiDi ~ 0
MISO
Text GLabel 13000 11800 2    50   Output ~ 0
X_EN
Text GLabel 9400 13900 0    50   BiDi ~ 0
MCDA3
Text GLabel 13000 10900 2    50   Input ~ 0
Y_STOP
Text GLabel 9400 14200 0    50   BiDi ~ 0
URXD1
Text GLabel 9400 14350 0    50   Output ~ 0
E5_DIR
Text GLabel 9400 14500 0    50   BiDi ~ 0
URXD0
Text GLabel 13000 9400 2    50   Input ~ 0
Z_STOP
Text GLabel 13000 12100 2    50   Output ~ 0
E4_DIR
Text GLabel 13000 12250 2    50   BiDi ~ 0
TWCK0
Text GLabel 13000 11950 2    50   Output ~ 0
HEATER5
Text GLabel 9400 14050 0    50   Output ~ 0
E2_DIR
Text GLabel 13000 9250 2    50   Output ~ 0
E1_DIR
Text GLabel 13000 11200 2    50   BiDi ~ 0
TWD0
Text GLabel 13000 10300 2    50   Output ~ 0
E0_DIR
Text GLabel 9400 9400 0    50   BiDi ~ 0
SAM_TFR_RDY
Text GLabel 13000 10750 2    50   Output ~ 0
HEATER6
Text GLabel 13000 11500 2    50   Output ~ 0
Z_DIR
Text GLabel 9400 5650 0    50   BiDi ~ 0
ESP_DATA_RDY
Text GLabel 13000 11050 2    50   Output ~ 0
Y_DIR
Text GLabel 13000 9850 2    50   Output ~ 0
FAN2
Text GLabel 9400 8800 0    50   BiDi ~ 0
ESP_RST
Text GLabel 9400 12550 0    50   Output ~ 0
E3_Dir
Text GLabel 13000 10450 2    50   Output ~ 0
X_DIR
Text GLabel 13000 9100 2    50   BiDi ~ 0
SPI0_CS2
Text GLabel 13000 8950 2    50   BiDi ~ 0
MCCDA
Text GLabel 13000 6850 2    50   Output ~ 0
E5_STEP
Text GLabel 13000 8650 2    50   BiDi ~ 0
UTXD1
Text GLabel 13000 8500 2    50   BiDi ~ 0
MCDA0
Text GLabel 13000 8350 2    50   BiDi ~ 0
CS3
Text GLabel 13000 8200 2    50   BiDi ~ 0
MCDA1
Text GLabel 9400 5500 0    50   Output ~ 0
E4_STEP
Text GLabel 13000 7900 2    50   BiDi ~ 0
CS4
Text GLabel 13000 6250 2    50   Output ~ 0
E3_STEP
Text GLabel 13000 7600 2    50   Input ~ 0
SD_CD
Text GLabel 13000 6400 2    50   Output ~ 0
E2_STEP
Text GLabel 13000 7150 2    50   Output ~ 0
E1_STEP
Text GLabel 13000 7000 2    50   Output ~ 0
FAN0
Text GLabel 13000 7300 2    50   Output ~ 0
E0_STEP
Text GLabel 13000 6700 2    50   BiDi ~ 0
MCCK
Text GLabel 13000 8800 2    50   Output ~ 0
Z_STEP
Text GLabel 13000 8050 2    50   Output ~ 0
Y_STEP
Text GLabel 13000 5950 2    50   BiDi ~ 0
DDM
Text GLabel 13000 5800 2    50   BiDi ~ 0
DDP
Text GLabel 13000 5500 2    50   BiDi ~ 0
SPI0_SCK
Text Notes 8550 3500 0    47   ~ 0
A 4.7 μF or higher ceramic capacitor must be\nconnected between VDDIN and the closest\nGND pin of the device. \nThis large decoupling capacitor is mandatory\nto reduce startup current,  improving transient\nresponse and noise rejection.
Text Notes 12500 2800 0    47   ~ 0
To ensure stability, an external 2.2 μF output capacitor, CDOUT must be\n connected between the VDDOUT and the closest GND pin of the device. \nThe ESR (Equivalent Series Resistance) of the capacitor must be in the range\n0.1Ω to 10Ω. Solid tantalum and multilayer ceramic capacitors are all\nsuitable as output capacitor. A 100 nF bypass capacitor between VDDOUT\nand the closest GND pin of the device helps decrease output noise and\nimproves the load transient response.
$Comp
L C_SMALL C61
U 1 1 567EA0B0
P 11850 4250
F 0 "C61" H 11875 4325 50  0000 L CNN
F 1 "0u1" H 11850 4175 50  0000 L CNN
F 2 "complib:C_0603" H 11850 4250 60  0001 C CNN
F 3 "" H 11850 4250 60  0001 C CNN
	1    11850 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	8450 9900 8450 9950
Wire Wire Line
	8450 9950 8350 9950
Connection ~ 14050 15600
Wire Wire Line
	13900 15600 14900 15600
Wire Wire Line
	13900 15600 13900 14900
Wire Wire Line
	13900 14900 14150 14900
Connection ~ 14900 14900
Wire Wire Line
	14750 14900 14900 14900
Connection ~ 14050 15000
Wire Wire Line
	11050 3150 11050 3000
Wire Wire Line
	10750 15100 10750 15450
Connection ~ 14700 12650
Wire Wire Line
	12900 12650 15150 12650
Wire Wire Line
	14700 12050 14700 12250
Connection ~ 14500 13500
Wire Wire Line
	14500 13650 14500 13500
Connection ~ 14500 12800
Connection ~ 14500 12650
Wire Wire Line
	14500 12650 14500 12800
Connection ~ 16750 12450
Wire Wire Line
	16750 12400 16750 12450
Connection ~ 16750 13000
Wire Wire Line
	16750 13000 16750 13050
Connection ~ 18950 12250
Wire Wire Line
	17900 12250 19700 12250
Connection ~ 19450 12250
Connection ~ 19700 12850
Wire Wire Line
	19700 12750 19700 12850
Connection ~ 10300 4550
Wire Wire Line
	10300 4550 10300 4700
Connection ~ 10600 4550
Wire Wire Line
	10600 4550 10600 4700
Connection ~ 10900 4550
Wire Wire Line
	10900 4550 10900 4700
Connection ~ 9700 4150
Wire Wire Line
	11050 3300 11050 4700
Wire Wire Line
	6400 4150 10000 4150
Wire Wire Line
	10000 4550 10900 4550
Connection ~ 8400 4600
Wire Wire Line
	8400 4600 8400 4800
Wire Wire Line
	10600 3800 10600 3650
Connection ~ 8100 4600
Connection ~ 9200 4600
Wire Wire Line
	8650 4600 8650 4500
Connection ~ 8650 4150
Wire Wire Line
	8100 3200 8100 4300
Wire Wire Line
	11050 2750 11250 2750
Connection ~ 12900 4100
Wire Wire Line
	12900 4100 12900 4150
Connection ~ 13650 4100
Wire Wire Line
	13900 4100 13900 4150
Wire Wire Line
	11400 4100 14200 4100
Connection ~ 13650 4400
Wire Wire Line
	13900 4400 13900 4350
Wire Wire Line
	12700 4400 14200 4400
Connection ~ 13300 4400
Wire Wire Line
	13400 4400 13400 4350
Connection ~ 12900 4400
Wire Wire Line
	12700 4350 12700 4400
Wire Wire Line
	12250 3950 11550 3950
Wire Wire Line
	12250 2700 12250 3950
Wire Wire Line
	12000 3750 12000 3000
Wire Wire Line
	11800 3750 12000 3750
Wire Wire Line
	11800 3750 11800 3650
Connection ~ 11800 2700
Wire Wire Line
	11550 3950 11550 4700
Wire Wire Line
	12300 4550 12300 4700
Connection ~ 12000 4550
Wire Wire Line
	12150 4550 12150 4700
Connection ~ 11700 4550
Wire Wire Line
	11850 4700 11850 4550
Wire Wire Line
	18900 13150 20000 13150
Wire Wire Line
	18900 12950 20050 12950
Wire Wire Line
	20100 13050 18900 13050
Connection ~ 11500 15450
Wire Wire Line
	11500 15450 11500 15100
Connection ~ 11350 15450
Wire Wire Line
	11350 15450 11350 15100
Connection ~ 11050 15450
Wire Wire Line
	11050 15450 11050 15100
Wire Wire Line
	14050 15600 14050 15400
Connection ~ 17850 13250
Wire Wire Line
	17850 12950 17850 13300
Wire Wire Line
	17900 13050 17850 13050
Wire Wire Line
	17850 12950 17900 12950
Wire Wire Line
	18950 13450 18950 13250
Wire Wire Line
	14450 15600 14450 15800
Connection ~ 14450 15600
Wire Wire Line
	17850 13250 17900 13250
Connection ~ 17850 13050
Wire Wire Line
	10900 15450 10900 15100
Wire Wire Line
	14900 15600 14900 15400
Wire Wire Line
	11400 15450 11400 15650
Wire Wire Line
	11200 15450 11200 15100
Connection ~ 11200 15450
Connection ~ 11400 15450
Wire Wire Line
	11650 15450 11650 15100
Connection ~ 11650 15450
Wire Wire Line
	18900 12850 19950 12850
Wire Wire Line
	18950 13450 18900 13450
Wire Wire Line
	11700 4700 11700 4550
Wire Wire Line
	12000 4550 12000 4700
Connection ~ 11850 4550
Connection ~ 12150 4550
Connection ~ 12300 4550
Wire Wire Line
	11400 2700 11400 4700
Wire Wire Line
	11400 2700 11500 2700
Wire Wire Line
	11700 2700 12250 2700
Wire Wire Line
	12000 2700 12000 2800
Connection ~ 12000 2700
Wire Wire Line
	11900 3850 11900 3750
Connection ~ 11900 3750
Connection ~ 11400 4100
Wire Wire Line
	13400 4100 13400 4150
Wire Wire Line
	12900 4400 12900 4350
Connection ~ 12700 4400
Wire Wire Line
	13300 4400 13300 4500
Wire Wire Line
	13650 4400 13650 4350
Connection ~ 13400 4400
Wire Wire Line
	13650 4100 13650 4150
Connection ~ 13400 4100
Wire Wire Line
	12700 4100 12700 4150
Connection ~ 12700 4100
Wire Wire Line
	11700 4550 12500 4550
Wire Wire Line
	12500 4550 12500 4100
Connection ~ 12500 4100
Wire Wire Line
	10350 3450 10350 3400
Wire Wire Line
	10350 3400 10600 3400
Wire Wire Line
	10600 3200 10600 3450
Connection ~ 10600 3400
Wire Wire Line
	8650 4150 8650 4300
Connection ~ 8100 4150
Wire Wire Line
	9700 4150 9700 4300
Connection ~ 9200 4150
Wire Wire Line
	9700 4600 9700 4500
Wire Wire Line
	9200 4600 9200 4500
Wire Wire Line
	8100 4600 8100 4500
Connection ~ 8650 4600
Wire Wire Line
	6400 4600 9700 4600
Wire Wire Line
	10350 3650 10350 3900
Wire Wire Line
	10750 4550 10750 4700
Connection ~ 10750 4550
Wire Wire Line
	10450 4550 10450 4700
Connection ~ 10450 4550
Wire Wire Line
	18950 12750 18950 13150
Connection ~ 18950 13150
Wire Wire Line
	19450 12750 19450 12950
Connection ~ 19450 12950
Wire Wire Line
	19700 12250 19700 12350
Wire Wire Line
	19450 12350 19450 12250
Wire Wire Line
	18950 12250 18950 12350
Wire Wire Line
	17900 12150 17900 12850
Connection ~ 17900 12250
Wire Wire Line
	16700 12950 16700 13000
Wire Wire Line
	16700 13000 16800 13000
Wire Wire Line
	16800 13000 16800 12950
Wire Wire Line
	16700 12450 16800 12450
Wire Wire Line
	14450 12900 14450 12800
Wire Wire Line
	14450 12800 14550 12800
Wire Wire Line
	14550 12800 14550 12900
Wire Wire Line
	14450 13400 14450 13500
Wire Wire Line
	14450 13500 14550 13500
Wire Wire Line
	14550 13500 14550 13400
Wire Wire Line
	14700 12650 14700 12450
Wire Wire Line
	18950 13250 18900 13250
Connection ~ 10750 15150
Connection ~ 11050 2750
Wire Wire Line
	14150 15000 14050 15000
Wire Wire Line
	14900 14600 14900 15200
Wire Wire Line
	14750 15000 14750 15600
Connection ~ 14750 15600
Connection ~ 10900 15450
Wire Wire Line
	8350 9700 9500 9700
Connection ~ 8450 9700
Wire Wire Line
	12900 12800 13000 12800
Wire Wire Line
	12900 13050 13000 13050
Wire Wire Line
	12900 13200 13000 13200
Wire Wire Line
	12900 13350 13000 13350
Wire Wire Line
	12900 13500 13000 13500
Wire Wire Line
	20050 12950 20050 12850
Wire Wire Line
	20050 12850 20100 12850
Wire Wire Line
	19950 12850 19950 12650
Wire Wire Line
	19950 12650 20100 12650
Wire Wire Line
	20000 13150 20000 13250
Wire Wire Line
	20000 13250 20100 13250
Wire Wire Line
	9350 9850 9500 9850
Wire Wire Line
	11250 2750 11250 4700
Wire Wire Line
	12450 4700 12450 4550
Connection ~ 12450 4550
Wire Wire Line
	10150 4700 10150 4550
Connection ~ 10150 4550
Wire Wire Line
	10000 4150 10000 4700
Connection ~ 10000 4550
Wire Wire Line
	13100 4150 13100 4100
Connection ~ 13100 4100
Wire Wire Line
	13100 4350 13100 4400
Connection ~ 13100 4400
Connection ~ 11650 4100
Wire Wire Line
	11650 4100 11650 4150
Wire Wire Line
	11650 4350 11650 4400
Connection ~ 10350 3800
Connection ~ 10600 3800
Wire Wire Line
	6600 4600 6600 4500
Wire Wire Line
	7100 4600 7100 4500
Connection ~ 7100 4600
Wire Wire Line
	7600 4600 7600 4500
Connection ~ 7600 4600
Wire Wire Line
	7600 4150 7600 4300
Wire Wire Line
	7100 4150 7100 4300
Connection ~ 7600 4150
Wire Wire Line
	6600 4150 6600 4300
Connection ~ 7100 4150
Wire Wire Line
	6150 6550 5850 6550
Wire Wire Line
	6150 6850 5850 6850
Wire Wire Line
	6150 7000 5850 7000
Wire Wire Line
	6150 7150 5850 7150
Wire Wire Line
	6550 7300 9500 7300
Wire Wire Line
	6550 7450 9500 7450
Wire Wire Line
	6550 7600 9500 7600
Wire Wire Line
	9500 5500 9400 5500
Wire Wire Line
	9400 5650 9500 5650
Wire Wire Line
	9500 5800 9400 5800
Wire Wire Line
	9400 5950 9500 5950
Wire Wire Line
	9500 6100 9400 6100
Wire Wire Line
	9400 6250 9500 6250
Wire Wire Line
	9500 6400 9400 6400
Wire Wire Line
	6550 6550 9500 6550
Wire Wire Line
	9500 6700 9400 6700
Wire Wire Line
	6550 6850 9500 6850
Wire Wire Line
	6550 7000 9500 7000
Wire Wire Line
	6550 7150 9500 7150
Wire Wire Line
	9400 7750 9500 7750
Wire Wire Line
	9500 7900 9400 7900
Wire Wire Line
	9400 8050 9500 8050
Wire Wire Line
	9500 8200 9400 8200
Wire Wire Line
	9500 8500 9400 8500
Wire Wire Line
	9400 8650 9500 8650
Wire Wire Line
	9500 8800 9400 8800
Wire Wire Line
	9500 9100 9400 9100
Wire Wire Line
	9400 9250 9500 9250
Wire Wire Line
	9500 9400 9400 9400
Wire Wire Line
	9400 9550 9500 9550
Wire Wire Line
	9500 10300 9400 10300
Wire Wire Line
	9400 10450 9500 10450
Wire Wire Line
	9500 10600 9400 10600
Wire Wire Line
	9400 10750 9500 10750
Wire Wire Line
	9400 11050 9500 11050
Wire Wire Line
	9500 11200 9400 11200
Wire Wire Line
	9400 11350 9500 11350
Wire Wire Line
	9500 11500 9400 11500
Wire Wire Line
	9500 11800 9400 11800
Wire Wire Line
	9400 11950 9500 11950
Wire Wire Line
	9500 12100 9400 12100
Wire Wire Line
	9400 12250 9500 12250
Wire Wire Line
	9500 12400 9400 12400
Wire Wire Line
	9400 12550 9500 12550
Wire Wire Line
	9500 12700 9400 12700
Wire Wire Line
	9400 12850 9500 12850
Wire Wire Line
	9500 13000 9400 13000
Wire Wire Line
	9400 13150 9500 13150
Wire Wire Line
	9500 13300 9400 13300
Wire Wire Line
	9400 13450 9500 13450
Wire Wire Line
	9500 13600 9400 13600
Wire Wire Line
	9400 13750 9500 13750
Wire Wire Line
	9500 13900 9400 13900
Wire Wire Line
	9400 14050 9500 14050
Wire Wire Line
	9500 14200 9400 14200
Wire Wire Line
	9400 14350 9500 14350
Wire Wire Line
	9500 14500 9400 14500
Wire Wire Line
	12900 11800 13000 11800
Wire Wire Line
	12900 11950 13000 11950
Wire Wire Line
	12900 12100 13000 12100
Wire Wire Line
	12900 12250 13000 12250
Wire Wire Line
	12900 11500 13000 11500
Wire Wire Line
	12900 10750 13000 10750
Wire Wire Line
	12900 10900 13000 10900
Wire Wire Line
	12900 11050 13000 11050
Wire Wire Line
	12900 11200 13000 11200
Wire Wire Line
	12900 10300 13000 10300
Wire Wire Line
	12900 10450 13000 10450
Wire Wire Line
	12900 9550 13000 9550
Wire Wire Line
	12900 9700 13000 9700
Wire Wire Line
	12900 9850 13000 9850
Wire Wire Line
	12900 10000 13000 10000
Wire Wire Line
	12900 8950 13000 8950
Wire Wire Line
	12900 9100 13000 9100
Wire Wire Line
	12900 9250 13000 9250
Wire Wire Line
	12900 9400 13000 9400
Wire Wire Line
	12900 8350 13000 8350
Wire Wire Line
	12900 8500 13000 8500
Wire Wire Line
	12900 8650 13000 8650
Wire Wire Line
	12900 8800 13000 8800
Wire Wire Line
	12900 7750 13000 7750
Wire Wire Line
	12900 7900 13000 7900
Wire Wire Line
	12900 8050 13000 8050
Wire Wire Line
	12900 8200 13000 8200
Wire Wire Line
	12900 7600 13000 7600
Wire Wire Line
	12900 6850 13000 6850
Wire Wire Line
	12900 7000 13000 7000
Wire Wire Line
	12900 7150 13000 7150
Wire Wire Line
	12900 7300 13000 7300
Wire Wire Line
	12900 6700 13000 6700
Wire Wire Line
	12900 6400 13000 6400
Wire Wire Line
	12900 6250 13000 6250
Wire Wire Line
	12900 5500 13000 5500
Wire Wire Line
	12900 5650 13000 5650
Wire Wire Line
	12900 5800 13000 5800
Wire Wire Line
	12900 5950 13000 5950
Wire Wire Line
	11850 4150 11850 4100
Connection ~ 11850 4100
Wire Wire Line
	11850 4400 11850 4350
Wire Wire Line
	11650 4400 11850 4400
Wire Wire Line
	11750 4400 11750 4450
Connection ~ 11750 4400
$Comp
L R_SMALL R13
U 1 1 56815975
P 11800 3150
F 0 "R13" V 11875 3158 50  0000 C CNN
F 1 "1R" V 11732 3162 50  0000 C CNN
F 2 "complib:R_0603" H 11800 3150 60  0001 C CNN
F 3 "" H 11800 3150 60  0001 C CNN
	1    11800 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	11800 2950 11800 2700
Wire Wire Line
	11800 3450 11800 3350
$Comp
L C_SMALL C8
U 1 1 56815DA9
P 6400 4400
F 0 "C8" H 6425 4475 50  0000 L CNN
F 1 "10u" H 6400 4325 50  0000 L CNN
F 2 "FE Footprints:C_0805" H 6400 4400 60  0001 C CNN
F 3 "" H 6400 4400 60  0001 C CNN
	1    6400 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6400 4300 6400 4150
Connection ~ 6600 4150
Wire Wire Line
	6400 4500 6400 4600
Connection ~ 6600 4600
Wire Wire Line
	12900 13800 12950 13800
Wire Wire Line
	12950 13650 12950 13900
$Comp
L GND #PWR073
U 1 1 56817783
P 12950 13900
AR Path="/56817783" Ref="#PWR073"  Part="1" 
AR Path="/50523307/56817783" Ref="#PWR074"  Part="1" 
F 0 "#PWR074" H 12950 13900 30  0001 C CNN
F 1 "GND" H 12950 13830 30  0001 C CNN
F 2 "" H 12950 13900 60  0001 C CNN
F 3 "" H 12950 13900 60  0001 C CNN
	1    12950 13900
	1    0    0    -1  
$EndComp
Wire Wire Line
	12900 13650 12950 13650
Connection ~ 12950 13800
$Comp
L R_SMALL R62
U 1 1 5682A294
P 8150 9700
F 0 "R62" V 8225 9708 50  0000 C CNN
F 1 "10K" V 8082 9712 50  0000 C CNN
F 2 "complib:R_0603" H 8150 9700 60  0001 C CNN
F 3 "" H 8150 9700 60  0001 C CNN
	1    8150 9700
	0    -1   -1   0   
$EndComp
$Comp
L C_SMALL C90
U 1 1 5682A2BC
P 8450 9800
F 0 "C90" H 8475 9875 50  0000 L CNN
F 1 "0u01" H 8450 9725 50  0000 L CNN
F 2 "complib:C_0603" H 8450 9800 60  0001 C CNN
F 3 "" H 8450 9800 60  0001 C CNN
	1    8450 9800
	1    0    0    -1  
$EndComp
$Comp
L R_SMALL R9
U 1 1 56834C19
P 6350 7150
F 0 "R9" V 6400 7300 50  0000 C CNN
F 1 "10K" V 6282 7162 50  0000 C CNN
F 2 "complib:R_0603" H 6350 7150 60  0001 C CNN
F 3 "" H 6350 7150 60  0001 C CNN
	1    6350 7150
	0    -1   -1   0   
$EndComp
$Comp
L R_SMALL R8
U 1 1 56834C1F
P 6350 7000
F 0 "R8" V 6400 7150 50  0000 C CNN
F 1 "10K" V 6282 7012 50  0000 C CNN
F 2 "complib:R_0603" H 6350 7000 60  0001 C CNN
F 3 "" H 6350 7000 60  0001 C CNN
	1    6350 7000
	0    -1   -1   0   
$EndComp
$Comp
L R_SMALL R7
U 1 1 56834C25
P 6350 6850
F 0 "R7" V 6400 7000 50  0000 C CNN
F 1 "10K" V 6282 6862 50  0000 C CNN
F 2 "complib:R_0603" H 6350 6850 60  0001 C CNN
F 3 "" H 6350 6850 60  0001 C CNN
	1    6350 6850
	0    -1   -1   0   
$EndComp
$Comp
L R_SMALL R6
U 1 1 56834C79
P 6350 6550
F 0 "R6" V 6400 6700 50  0000 C CNN
F 1 "10K" V 6282 6562 50  0000 C CNN
F 2 "complib:R_0603" H 6350 6550 60  0001 C CNN
F 3 "" H 6350 6550 60  0001 C CNN
	1    6350 6550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9400 10000 9500 10000
$Comp
L R_SMALL F1
U 1 1 5684AC3F
P 10350 15150
F 0 "F1" V 10425 15158 50  0000 C CNN
F 1 "0.25A VFA" V 10282 15162 50  0000 C CNN
F 2 "FE Footprints:FUSE_0603" H 10350 15150 60  0001 C CNN
F 3 "" H 10350 15150 60  0001 C CNN
	1    10350 15150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10550 15150 10750 15150
Wire Wire Line
	10150 15150 10000 15150
Text Notes 9000 15450 0    60   ~ 0
Fuse to protect the SAM from \nVIN applied to VSSA in error.
Text GLabel 9400 8650 0    50   BiDi ~ 0
SPI0_CS1
Wire Wire Line
	13000 6550 12900 6550
Text GLabel 9400 8950 0    50   BiDi ~ 0
ESP_EN
Wire Wire Line
	13000 10600 12900 10600
Text GLabel 9400 13750 0    50   Output ~ 0
LCD_DB7
Text GLabel 9400 13450 0    50   Output ~ 0
LCD_DB6
Wire Wire Line
	12900 10150 13000 10150
Text GLabel 9400 13150 0    50   Output ~ 0
LCD_DB5
Wire Wire Line
	12900 11350 13000 11350
Text GLabel 9400 12850 0    50   Output ~ 0
LCD_DB4
Wire Wire Line
	12900 11650 13000 11650
Text GLabel 13000 12400 2    50   Output ~ 0
LCD_RS
Wire Wire Line
	12900 12400 13000 12400
Text GLabel 9400 11050 0    50   Output ~ 0
HEATER7
Wire Wire Line
	8550 11650 9500 11650
Text GLabel 9400 10900 0    50   Output ~ 0
ENC_B
Wire Wire Line
	9500 10900 9400 10900
Text GLabel 13050 14300 2    50   Output ~ 0
ENC_A
Wire Wire Line
	9500 10150 9400 10150
Text GLabel 13050 14150 2    50   Output ~ 0
ENC_SW
Wire Wire Line
	9500 8950 9400 8950
Wire Wire Line
	10950 2600 11050 2600
Connection ~ 11050 2600
Wire Wire Line
	8100 3200 10600 3200
Wire Wire Line
	9250 3200 9250 2950
Connection ~ 9250 3200
Text Notes 11600 4050 0    47   ~ 0
The ESR  of C68 must be in the range 0.1Ω to 10Ω.
Wire Wire Line
	9200 4150 9200 4300
$Comp
L C_SMALL C10
U 1 1 568928F2
P 14200 4250
F 0 "C10" H 14225 4325 50  0000 L CNN
F 1 "10u" H 14200 4175 50  0000 L CNN
F 2 "FE Footprints:C_0805" H 14200 4250 60  0001 C CNN
F 3 "" H 14200 4250 60  0001 C CNN
	1    14200 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	14200 4100 14200 4150
Connection ~ 13900 4100
Wire Wire Line
	14200 4400 14200 4350
Connection ~ 13900 4400
$Comp
L R_SMALL R12
U 1 1 5693B013
P 6350 7600
F 0 "R12" V 6400 7750 50  0000 C CNN
F 1 "10K" V 6282 7612 50  0000 C CNN
F 2 "complib:R_0603" H 6350 7600 60  0001 C CNN
F 3 "" H 6350 7600 60  0001 C CNN
	1    6350 7600
	0    -1   -1   0   
$EndComp
$Comp
L R_SMALL R11
U 1 1 5693B019
P 6350 7450
F 0 "R11" V 6400 7600 50  0000 C CNN
F 1 "10K" V 6282 7462 50  0000 C CNN
F 2 "complib:R_0603" H 6350 7450 60  0001 C CNN
F 3 "" H 6350 7450 60  0001 C CNN
	1    6350 7450
	0    -1   -1   0   
$EndComp
$Comp
L R_SMALL R10
U 1 1 5693B01F
P 6350 7300
F 0 "R10" V 6400 7450 50  0000 C CNN
F 1 "10K" V 6282 7312 50  0000 C CNN
F 2 "complib:R_0603" H 6350 7300 60  0001 C CNN
F 3 "" H 6350 7300 60  0001 C CNN
	1    6350 7300
	0    -1   -1   0   
$EndComp
Text GLabel 7200 9250 3    50   Input ~ 0
VSSA
$Comp
L C_SMALL C53
U 1 1 5693B035
P 7350 8900
F 0 "C53" H 7375 8975 50  0000 L CNN
F 1 "2u2" H 7350 8825 50  0000 L CNN
F 2 "complib:C_0603" H 7350 8900 60  0001 C CNN
F 3 "" H 7350 8900 60  0001 C CNN
	1    7350 8900
	1    0    0    -1  
$EndComp
$Comp
L C_SMALL C18
U 1 1 5693B04C
P 7100 8900
F 0 "C18" H 7125 8975 50  0000 L CNN
F 1 "2u2" H 7100 8825 50  0000 L CNN
F 2 "complib:C_0603" H 7100 8900 60  0001 C CNN
F 3 "" H 7100 8900 60  0001 C CNN
	1    7100 8900
	1    0    0    -1  
$EndComp
$Comp
L C_SMALL C19
U 1 1 5693B057
P 6850 8900
F 0 "C19" H 6875 8975 50  0000 L CNN
F 1 "2u2" H 6850 8825 50  0000 L CNN
F 2 "complib:C_0603" H 6850 8900 60  0001 C CNN
F 3 "" H 6850 8900 60  0001 C CNN
	1    6850 8900
	1    0    0    -1  
$EndComp
$Comp
L C_SMALL C59
U 1 1 5693B062
P 7600 8900
F 0 "C59" H 7625 8975 50  0000 L CNN
F 1 "2u2" H 7600 8825 50  0000 L CNN
F 2 "complib:C_0603" H 7600 8900 60  0001 C CNN
F 3 "" H 7600 8900 60  0001 C CNN
	1    7600 8900
	1    0    0    -1  
$EndComp
$Comp
L C_SMALL C60
U 1 1 5693B068
P 7850 8900
F 0 "C60" H 7875 8975 50  0000 L CNN
F 1 "2u2" H 7850 8825 50  0000 L CNN
F 2 "complib:C_0603" H 7850 8900 60  0001 C CNN
F 3 "" H 7850 8900 60  0001 C CNN
	1    7850 8900
	1    0    0    -1  
$EndComp
$Comp
L C_SMALL C63
U 1 1 5693B06E
P 8050 8900
F 0 "C63" H 8075 8975 50  0000 L CNN
F 1 "2u2" H 8050 8825 50  0000 L CNN
F 2 "complib:C_0603" H 8050 8900 60  0001 C CNN
F 3 "" H 8050 8900 60  0001 C CNN
	1    8050 8900
	1    0    0    -1  
$EndComp
$Comp
L C_SMALL C65
U 1 1 5693B074
P 8300 8900
F 0 "C65" H 8325 8975 50  0000 L CNN
F 1 "2u2" H 8300 8825 50  0000 L CNN
F 2 "complib:C_0603" H 8300 8900 60  0001 C CNN
F 3 "" H 8300 8900 60  0001 C CNN
	1    8300 8900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 9050 8300 9050
Wire Wire Line
	6850 9050 6850 9000
Wire Wire Line
	7100 9050 7100 9000
Connection ~ 7100 9050
Wire Wire Line
	7350 9050 7350 9000
Connection ~ 7200 9050
Wire Wire Line
	7600 9050 7600 9000
Connection ~ 7350 9050
Wire Wire Line
	7850 9050 7850 9000
Connection ~ 7600 9050
Wire Wire Line
	8050 9050 8050 9000
Connection ~ 7850 9050
Wire Wire Line
	8300 9050 8300 9000
Connection ~ 8050 9050
Wire Wire Line
	6850 8800 6850 7600
Connection ~ 6850 7600
Wire Wire Line
	7100 8800 7100 7450
Connection ~ 7100 7450
Wire Wire Line
	7350 8800 7350 7300
Connection ~ 7350 7300
Wire Wire Line
	7850 8800 7850 7000
Connection ~ 7850 7000
Wire Wire Line
	7600 8800 7600 7150
Connection ~ 7600 7150
Wire Wire Line
	8050 8800 8050 6850
Connection ~ 8050 6850
Wire Wire Line
	8300 8800 8300 6550
Connection ~ 8300 6550
Wire Wire Line
	4500 7300 6150 7300
Wire Wire Line
	4500 7450 6150 7450
Wire Wire Line
	4500 7600 6150 7600
$Comp
L R_SMALL R53
U 1 1 5693CC1D
P 5100 6600
F 0 "R53" V 5150 6750 50  0000 C CNN
F 1 "4K7 1%" V 5032 6612 50  0000 C CNN
F 2 "complib:R_0603" H 5100 6600 60  0001 C CNN
F 3 "" H 5100 6600 60  0001 C CNN
	1    5100 6600
	-1   0    0    1   
$EndComp
$Comp
L R_SMALL R19
U 1 1 5693CC2D
P 4850 6600
F 0 "R19" V 4900 6750 50  0000 C CNN
F 1 "4K7 1%" V 4782 6612 50  0000 C CNN
F 2 "complib:R_0603" H 4850 6600 60  0001 C CNN
F 3 "" H 4850 6600 60  0001 C CNN
	1    4850 6600
	-1   0    0    1   
$EndComp
$Comp
L R_SMALL R21
U 1 1 5693CC38
P 4600 6600
F 0 "R21" V 4650 6750 50  0000 C CNN
F 1 "4K7 1%" V 4532 6612 50  0000 C CNN
F 2 "complib:R_0603" H 4600 6600 60  0001 C CNN
F 3 "" H 4600 6600 60  0001 C CNN
	1    4600 6600
	-1   0    0    1   
$EndComp
Wire Wire Line
	4600 6250 4600 6400
Wire Wire Line
	5100 6350 5100 6400
Connection ~ 4850 6350
Wire Wire Line
	4600 6800 4600 7600
Connection ~ 4600 7600
Wire Wire Line
	4850 6800 4850 7450
Connection ~ 4850 7450
Wire Wire Line
	5100 6800 5100 7300
Connection ~ 5100 7300
Wire Wire Line
	7200 9050 7200 9250
Wire Wire Line
	13050 14300 12900 14300
Text GLabel 9400 10150 0    50   BiDi ~ 0
PWR_FAIL_DET2
Wire Wire Line
	10750 15450 11650 15450
Text GLabel 13000 10600 2    50   Input ~ 0
X_STOP
Wire Wire Line
	13050 14150 12900 14150
Wire Wire Line
	14900 14600 13450 14600
Wire Wire Line
	13450 14600 13450 14750
Wire Wire Line
	13450 14750 12900 14750
Wire Wire Line
	12900 14600 13100 14600
Wire Wire Line
	13100 14600 13100 14850
Wire Wire Line
	13100 14850 14050 14850
Wire Wire Line
	14050 14850 14050 15200
Wire Wire Line
	11050 3300 10600 3300
Connection ~ 10600 3300
Wire Wire Line
	10600 3800 10350 3800
Wire Wire Line
	13000 6100 12900 6100
Wire Wire Line
	4600 6350 5100 6350
Text GLabel 4600 6250 1    60   Input ~ 0
ADVREF
Text Notes 3500 6450 0    28   ~ 0
All thermistors should be pulled up to ADVREF\n
Text GLabel 13000 7450 2    60   Input ~ 0
USB_PWR_MON
Wire Wire Line
	12900 7450 13000 7450
Wire Wire Line
	4850 6350 4850 6400
Connection ~ 4600 6350
Text GLabel 9400 10750 0    50   Output ~ 0
E6_STEP
Text GLabel 6250 9650 0    50   Output ~ 0
Z_PROBE_MOD_BUFF
$Comp
L LED D4
U 1 1 57195014
P 6600 9650
F 0 "D4" H 6450 9600 50  0000 C CNN
F 1 "Diag" H 6600 9500 50  0000 C CNN
F 2 "complib:D_0603" H 6600 9650 60  0001 C CNN
F 3 "" H 6600 9650 60  0001 C CNN
	1    6600 9650
	1    0    0    -1  
$EndComp
$Comp
L R_SMALL R104
U 1 1 5719501A
P 7000 9850
F 0 "R104" V 6950 10000 50  0000 C CNN
F 1 "2K2" V 6900 9850 50  0000 C CNN
F 2 "complib:R_0603" H 7000 9850 60  0001 C CNN
F 3 "~" H 7000 9850 60  0000 C CNN
	1    7000 9850
	-1   0    0    1   
$EndComp
Wire Wire Line
	7000 9650 6800 9650
$Comp
L GND #PWR074
U 1 1 57195021
P 7000 10150
AR Path="/57195021" Ref="#PWR074"  Part="1" 
AR Path="/50523307/57195021" Ref="#PWR075"  Part="1" 
F 0 "#PWR075" H 7000 10150 30  0001 C CNN
F 1 "GND" H 7000 10080 30  0001 C CNN
F 2 "" H 7000 10150 60  0001 C CNN
F 3 "" H 7000 10150 60  0001 C CNN
	1    7000 10150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 10150 7000 10050
$Comp
L R_SMALL R50
U 1 1 57195D3F
P 6350 8350
F 0 "R50" V 6400 8500 50  0000 C CNN
F 1 "10K" V 6282 8362 50  0000 C CNN
F 2 "complib:R_0603" H 6350 8350 60  0001 C CNN
F 3 "" H 6350 8350 60  0001 C CNN
	1    6350 8350
	0    -1   -1   0   
$EndComp
$Comp
L C_SMALL C84
U 1 1 57195D45
P 6600 8900
F 0 "C84" H 6625 8975 50  0000 L CNN
F 1 "2u2" H 6600 8825 50  0000 L CNN
F 2 "complib:C_0603" H 6600 8900 60  0001 C CNN
F 3 "" H 6600 8900 60  0001 C CNN
	1    6600 8900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 9000 6600 9050
Connection ~ 6850 9050
Wire Wire Line
	6600 8800 6600 8350
Wire Wire Line
	6550 8350 9500 8350
Connection ~ 6600 8350
Wire Wire Line
	5850 8350 6150 8350
Wire Wire Line
	6400 9650 6250 9650
Text GLabel 9400 8500 0    60   Output ~ 0
E6_STOP
Text GLabel 9400 6400 0    60   Input ~ 0
E6_DIR
Text GLabel 13000 5650 2    60   Input ~ 0
E6_EN
Text GLabel 9400 10000 0    50   Output ~ 0
HEATER3
$Comp
L L_MINI L5
U 1 1 571982F1
P 11050 2300
F 0 "L5" H 10975 2250 30  0000 C CNN
F 1 "10uH 100Mhz" H 11000 2350 22  0000 C CNN
F 2 "complib:R_0603" H 11050 2300 60  0001 C CNN
F 3 "" H 11050 2300 60  0001 C CNN
	1    11050 2300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	11050 2400 11050 2800
Wire Wire Line
	11050 2200 11050 2100
Text Label 11100 2550 0    60   ~ 0
ADVREF
Text Notes 17900 13750 0    60   ~ 0
Do Not Populate the JTAG header or resistors R36,R49,R52
Text Notes 11200 2300 0    60   ~ 0
ADVREF requires a filter
$Comp
L FID M1
U 1 1 571B67A6
P 1000 15700
F 0 "M1" H 1000 15600 60  0000 C CNN
F 1 "FID" H 1000 15800 60  0000 C CNN
F 2 "complib:Fiducial_1mm_Dia_2.54mm_Outer_CopperTop" H 1000 15700 60  0001 C CNN
F 3 "" H 1000 15700 60  0000 C CNN
	1    1000 15700
	1    0    0    -1  
$EndComp
$Comp
L FID M2
U 1 1 571B67B3
P 1200 15700
F 0 "M2" H 1200 15600 60  0000 C CNN
F 1 "FID" H 1200 15800 60  0000 C CNN
F 2 "complib:Fiducial_1mm_Dia_2.54mm_Outer_CopperTop" H 1200 15700 60  0001 C CNN
F 3 "" H 1200 15700 60  0000 C CNN
	1    1200 15700
	1    0    0    -1  
$EndComp
$Comp
L FID M3
U 1 1 571B67B9
P 1400 15700
F 0 "M3" H 1400 15600 60  0000 C CNN
F 1 "FID" H 1400 15800 60  0000 C CNN
F 2 "complib:Fiducial_1mm_Dia_2.54mm_Outer_CopperTop" H 1400 15700 60  0001 C CNN
F 3 "" H 1400 15700 60  0000 C CNN
	1    1400 15700
	1    0    0    -1  
$EndComp
$Comp
L Mounting M4
U 1 1 571B67C1
P 1800 15700
AR Path="/571B67C1" Ref="M4"  Part="1" 
AR Path="/50523307/571B67C1" Ref="M4"  Part="1" 
F 0 "M4" H 1800 15600 60  0000 C CNN
F 1 "MOUNTING" H 1800 15800 60  0000 C CNN
F 2 "complib:Fixing_M4" H 1800 15700 60  0001 C CNN
F 3 "" H 1800 15700 60  0000 C CNN
	1    1800 15700
	1    0    0    -1  
$EndComp
$Comp
L Mounting M5
U 1 1 571B67CE
P 2300 15700
AR Path="/571B67CE" Ref="M5"  Part="1" 
AR Path="/50523307/571B67CE" Ref="M5"  Part="1" 
F 0 "M5" H 2300 15600 60  0000 C CNN
F 1 "MOUNTING" H 2300 15800 60  0000 C CNN
F 2 "complib:Fixing_M4" H 2300 15700 60  0001 C CNN
F 3 "" H 2300 15700 60  0000 C CNN
	1    2300 15700
	1    0    0    -1  
$EndComp
$Comp
L Mounting M6
U 1 1 571B67D4
P 2750 15700
AR Path="/571B67D4" Ref="M6"  Part="1" 
AR Path="/50523307/571B67D4" Ref="M6"  Part="1" 
F 0 "M6" H 2750 15600 60  0000 C CNN
F 1 "MOUNTING" H 2750 15800 60  0000 C CNN
F 2 "complib:Fixing_M4" H 2750 15700 60  0001 C CNN
F 3 "" H 2750 15700 60  0000 C CNN
	1    2750 15700
	1    0    0    -1  
$EndComp
$Comp
L Mounting M7
U 1 1 571B67DA
P 3200 15700
AR Path="/571B67DA" Ref="M7"  Part="1" 
AR Path="/50523307/571B67DA" Ref="M7"  Part="1" 
F 0 "M7" H 3200 15600 60  0000 C CNN
F 1 "MOUNTING" H 3200 15800 60  0000 C CNN
F 2 "complib:Fixing_M4" H 3200 15700 60  0001 C CNN
F 3 "" H 3200 15700 60  0000 C CNN
	1    3200 15700
	1    0    0    -1  
$EndComp
Wire Wire Line
	8800 11650 8800 11600
Connection ~ 8800 11650
$Comp
L R_SMALL R51
U 1 1 577920BC
P 8800 11400
F 0 "R51" V 8875 11408 50  0000 C CNN
F 1 "10K" V 8732 11412 50  0000 C CNN
F 2 "complib:R_0603" H 8800 11400 60  0001 C CNN
F 3 "" H 8800 11400 60  0000 C CNN
	1    8800 11400
	1    0    0    -1  
$EndComp
Text GLabel 8800 11150 1    60   Input ~ 0
+3.3V
Wire Wire Line
	8800 11150 8800 11200
$Comp
L LOGO M8
U 1 1 577B4E04
P 3800 15700
F 0 "M8" H 3800 15600 60  0000 C CNN
F 1 "LOGO" H 3800 15800 60  0000 C CNN
F 2 "complib:LOGO" H 3800 15700 60  0001 C CNN
F 3 "" H 3800 15700 60  0000 C CNN
	1    3800 15700
	1    0    0    -1  
$EndComp
$EndSCHEMATC
