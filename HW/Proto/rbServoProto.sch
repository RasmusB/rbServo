EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
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
LIBS:rbv_connectors
LIBS:rbv_device
LIBS:rbv_drivers
LIBS:rbv_mcu
LIBS:rbv_linear
LIBS:rbv_regul
LIBS:rbv_interface
LIBS:rbv_mosfet
LIBS:rbv_pcb_extras
EELAYER 24 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 2
Title ""
Date "28 nov 2012"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CONN_4 P1
U 1 1 4F2DC381
P 3800 3550
F 0 "P1" V 3750 3550 50  0000 C CNN
F 1 "EXTCON" V 3850 3550 50  0000 C CNN
F 2 "" H 3800 3550 60  0001 C CNN
F 3 "" H 3800 3550 60  0001 C CNN
	1    3800 3550
	-1   0    0    -1  
$EndComp
Text Label 7300 4400 2    60   ~ 0
MOTOR+
Text Label 7300 4600 2    60   ~ 0
MOTOR-
$Comp
L +5V #PWR01
U 1 1 4E74CD8D
P 4300 4200
F 0 "#PWR01" H 4300 4290 20  0001 C CNN
F 1 "+5V" H 4300 4290 30  0000 C CNN
F 2 "" H 4300 4200 60  0001 C CNN
F 3 "" H 4300 4200 60  0001 C CNN
	1    4300 4200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 4E74CD8C
P 4650 3950
F 0 "#PWR02" H 4650 3950 30  0001 C CNN
F 1 "GND" H 4650 3880 30  0001 C CNN
F 2 "" H 4650 3950 60  0001 C CNN
F 3 "" H 4650 3950 60  0001 C CNN
	1    4650 3950
	1    0    0    -1  
$EndComp
Text Label 4650 3500 2    60   ~ 0
CAN_LOW
Text Label 4650 3600 2    60   ~ 0
CAN_HIGH
Text Label 4800 2600 0    60   ~ 0
ISP_RES
Text Label 4800 2400 0    60   ~ 0
ISP_MISO
Text Label 4800 2500 0    60   ~ 0
ISP_SCK
Text Label 6900 2500 2    60   ~ 0
ISP_MOSI
$Comp
L GND #PWR03
U 1 1 4E6A7AD3
P 6600 2800
F 0 "#PWR03" H 6600 2800 30  0001 C CNN
F 1 "GND" H 6600 2730 30  0001 C CNN
F 2 "" H 6600 2800 60  0001 C CNN
F 3 "" H 6600 2800 60  0001 C CNN
	1    6600 2800
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR04
U 1 1 4E6A7AC8
P 6600 2250
F 0 "#PWR04" H 6600 2340 20  0001 C CNN
F 1 "+5V" H 6600 2340 30  0000 C CNN
F 2 "" H 6600 2250 60  0001 C CNN
F 3 "" H 6600 2250 60  0001 C CNN
	1    6600 2250
	1    0    0    -1  
$EndComp
Text Label 4650 3700 2    60   ~ 0
GND
Wire Wire Line
	4150 3400 5050 3400
Wire Wire Line
	4300 4200 4300 4650
Wire Wire Line
	6600 2800 6600 2600
Wire Wire Line
	6600 2600 6450 2600
Wire Wire Line
	6600 2250 6600 2400
Wire Wire Line
	6600 2400 6450 2400
Wire Wire Line
	6900 2500 6450 2500
Wire Wire Line
	5250 2500 4800 2500
Wire Wire Line
	5250 2400 4800 2400
Wire Wire Line
	5250 2600 4800 2600
Wire Wire Line
	4150 3600 5050 3600
Wire Wire Line
	6750 4400 7500 4400
Wire Wire Line
	6750 4600 7500 4600
Wire Wire Line
	4150 3700 4650 3700
Wire Wire Line
	4650 3700 4650 3950
Wire Wire Line
	4150 3500 5050 3500
Text Label 4650 4550 2    60   ~ 0
aPOT
Wire Wire Line
	5050 4550 4150 4550
$Sheet
S 5050 3050 1700 2050
U 50B642BA
F0 "Core" 50
F1 "../common/rbServoCore.sch" 50
F2 "MOTOR+" O R 6750 4400 60 
F3 "MOTOR-" O R 6750 4600 60 
F4 "aPot" I L 5050 4550 60 
F5 "ISP_MISO" O R 6750 3650 60 
F6 "ISP_MOSI" I R 6750 3550 60 
F7 "ISP_SCK" I R 6750 3450 60 
F8 "CAN_HIGH" B L 5050 3600 60 
F9 "CAN_LOW" B L 5050 3500 60 
F10 "ISP_RES" I R 6750 3350 60 
F11 "uIn" I L 5050 3400 60 
$EndSheet
Text Label 7250 3350 2    60   ~ 0
ISP_RES
Wire Wire Line
	7250 3350 6750 3350
Text Label 7250 3450 2    60   ~ 0
ISP_SCK
Wire Wire Line
	7250 3450 6750 3450
Text Label 7250 3550 2    60   ~ 0
ISP_MOSI
Wire Wire Line
	7250 3550 6750 3550
Text Label 7250 3650 2    60   ~ 0
ISP_MISO
Wire Wire Line
	7250 3650 6750 3650
$Comp
L ATMEL_ISP-6P ISP1
U 1 1 50B6476E
P 5850 2500
F 0 "ISP1" H 5650 2800 60  0000 C CNN
F 1 "ATMEL_ISP-6P" H 5850 2200 60  0000 C CNN
F 2 "" H 5850 2500 60  0001 C CNN
F 3 "" H 5850 2500 60  0001 C CNN
	1    5850 2500
	1    0    0    -1  
$EndComp
$Comp
L CONN_3 P2
U 1 1 50B64948
P 3800 4650
F 0 "P2" V 3750 4650 50  0000 C CNN
F 1 "POT" V 3850 4650 40  0000 C CNN
F 2 "" H 3800 4650 60  0001 C CNN
F 3 "" H 3800 4650 60  0001 C CNN
	1    3800 4650
	-1   0    0    -1  
$EndComp
$Comp
L CONN_2 P3
U 1 1 50B64B0C
P 7850 4500
F 0 "P3" V 7800 4500 40  0000 C CNN
F 1 "MOTOR" V 7900 4500 40  0000 C CNN
F 2 "" H 7850 4500 60  0001 C CNN
F 3 "" H 7850 4500 60  0001 C CNN
	1    7850 4500
	1    0    0    -1  
$EndComp
Text Label 4650 3400 2    60   ~ 0
uIn
$Comp
L GND #PWR05
U 1 1 50B6786D
P 4650 5000
F 0 "#PWR05" H 4650 5000 30  0001 C CNN
F 1 "GND" H 4650 4930 30  0001 C CNN
F 2 "" H 4650 5000 60  0001 C CNN
F 3 "" H 4650 5000 60  0001 C CNN
	1    4650 5000
	1    0    0    -1  
$EndComp
Text Label 4650 4750 2    60   ~ 0
GND
Wire Wire Line
	4150 4750 4650 4750
Wire Wire Line
	4650 4750 4650 5000
Wire Wire Line
	4300 4650 4150 4650
$EndSCHEMATC
