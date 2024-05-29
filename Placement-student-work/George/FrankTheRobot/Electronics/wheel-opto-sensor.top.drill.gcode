;(.../Electronics/Eagle/pcb-gcode/pcb-gcode.ulp)
;(Copyright 2005 - 2012 by John Johnson)
;(See readme.txt for licensing terms.)
;(This file generated from the board:)
;(.../Electronics/wheel-opto-sensor.brd)
;(Current profile is .../pcb-gcode/profiles/generic.pp  )
;(This file generated 09/01/2018 16:01)
;(Settings from pcb-machine.h)
;(spindle on time = 1000.0000)
;(spindle speed = 20000.0000)
;(tool change at 0.0000 0.0000 5.0000 )
;(feed rate xy = F0.00  )
;(feed rate z  = F200.00 )
;(Z Axis Settings)
;(  High     Up        Down     Drill)
;(5.0000 	2.0000 	-0.2000 	-2.0000 )
;(Settings from pcb-defaults.h)
;(isolate min = 0.0250)
;(isolate max = 0.5000)
;(isolate step = 0.0800)
;(Generated top outlines, top drill, )
;(Unit of measure: mm)
;( Tool|       Size       |  Min Sub |  Max Sub |   Count )
;( T01  0.600mm 0.0236in 0.0000in 0.0000in )
;( T02  1.016mm 0.0400in 0.0000in 0.0000in )
;(Metric Mode)
G21
;(Absolute Coordinates)
G90
;S20000
G00 Z5.0000  F3000
G00 X0.0000 Y0.0000  F3000
;M03 S1
G04 P1000.000000
;M03 S0
;M06 T01  ; 0.6000 
G01 Z0.0000 F200.00 
;M06 
G00 Z2.0000  F3000
;M03 S1
G04 P1000.000000
G00 X2.5400 Y2.5400  F3000
G01 Z-2.0000 F200.00 
G00 Z2.0000  F3000
G00 X9.2075 Y6.9850  F3000
G01 Z-2.0000 F200.00 
G00 Z2.0000  F3000
G00 X13.3568 Y9.4264  F3000
G01 Z-2.0000 F200.00 
G00 Z2.0000  F3000
G00 X17.7800 Y5.0800  F3000
G01 Z-2.0000 F200.00 
G00 Z2.0000  F3000
G00 X12.7000 Y2.8575  F3000
G01 Z-2.0000 F200.00 
G00 Z2.0000  F3000
G00 X20.3200 Y13.3350  F3000
G01 Z-2.0000 F200.00 
G00 Z2.0000  F3000
;M03 S0
G00 Z5.0000  F3000
G00 X0.0000 Y0.0000  F3000
;M06 T02  ; 1.0160 
G01 Z0.0000 F200.00 
;M06 
G00 Z2.0000  F3000
;M03 S1
G04 P1000.000000
G00 X20.3200 Y2.5400  F3000
G01 Z-2.0000 F200.00 
G00 Z2.0000  F3000
G00 X20.3200 Y5.0800  F3000
G01 Z-2.0000 F200.00 
G00 Z2.0000  F3000
G00 X20.3200 Y7.6200  F3000
G01 Z-2.0000 F200.00 
G00 Z2.0000  F3000
G00 X20.3200 Y10.1600  F3000
G01 Z-2.0000 F200.00 
G00 Z2.0000  F3000
;T01 
G00 Z5.0000  F3000
;M03 S0
M0
