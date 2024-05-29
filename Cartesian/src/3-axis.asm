; 3 axis robot controller
; (well, 4 actually)
; Adrian Bowyer
; 22 April 2001

; Clock: 4.00 MHz resonator
; Don't forget to turn the watchdog reset OFF

	LIST P=PIC16F74		; tells the assembler which PIC

	include "p16f74.h"	; PIC register definitions file
 
; ******* Constants **********

DEL_0	equ 0	 ; Default time delay
DEL_1	equ 3
DEL_2	equ 0

ACC_0	equ 0	 ; Default steps of acceleration
ACC_1	equ 1
ACC_2	equ 070h

AINC_0	equ 0	; Default acceleration increment
AINC_1	equ 0
AINC_2	equ 1

BINC_0	equ 0	; Default acceleration steps
BINC_1	equ 0
BINC_2	equ 2

; Flag bits

NEG0	equ  0	; Negate axis 0
NEG1	equ  1	; Negate axis 1
NEG2	equ  2	; Negate axis 2
NEG3	equ  3	; Negate axis 3
SWP01	equ  4  ; Swap axes 0 and 1
SWP02	equ  5  ; Swap axes 0 and 2
SWP03	equ  6  ; Swap axes 0 and 3

; Endstop sensor bits

AX0L	equ  0	; Port C
AX0H	equ  1	; Port C
AX1L	equ  2	; Port C
AX1H	equ  3	; Port C
AX2L	equ  0	; Port D
AX2H	equ  1	; Port D

; Endstop bits in e_stop

SB0L	equ  0	; Axis 0
SB0H	equ  1
SB1L	equ  2	; Axis 0
SB1H	equ  3
SB2L	equ  4	; Axis 0
SB2H	equ  5
SBPZ	equ  6  ; Peripheral Z
SBPX	equ  7  ; Peripheral X
XC	equ  3  ; Port A bit for user's XY endstop (RA3)
ZC	equ  2  ; Port A bit for user's Z endstop (RA2)

; Accelleration bit

ACC	equ  0

; Default peripheral configuration

PCONF	equ  b'00000000'

; ADC control

ADC0	equ	b'01000001'	; Select ADC chan 0
ADC1	equ	b'01001001'	; Chan 1
ADC2	equ	b'01010001'	; Chan 2
ADC3	equ	b'01011001'	; Chan 3
ADC4	equ	b'01100001'	; Chan 4

; ********** data registers ***********

; Any subroutine or macro must switch to the bank it wants.
; There is no guaranteed state on entry or exit.

; ++++++++++++++ BANK 0 +++++++++++++++

	org	20h

; general temporary storage - fragile across any call

save	res 1	

; Character i/o data

last_i	res 1	; last received byte
last_o	res 1	; last transmitted byte
hex_l	res 1	; low nibble in hex
hex_h	res 1	; high nibble in hex
echo	res 1	; Echo on (01) or off (0)

; Time delays 

accel	res 1	; Acceleration flag; 0 == constant velocity

; Endstop flag

e_stop	res 1

; Axis stepper bit pattern

axpat	res 8
axstp_0	res 1	; Point in cycle, axis 0
axstp_1	res 1	; Point in cycle, axis 1
axstp_2	res 1	; Point in cycle, axis 2
axstp_3	res 1	; Point in cycle, axis 3

; Peripheral stop flag byte

p_stat	res 1	; 

; ++++++++++++++ BANK 1 +++++++++++++++

	org	0a0h

; General work location

work	res 3

; 24 bit arithmetic - pointers to arguments

arg0p	res 1	; 1st i/p
arg1p	res 1	; 2nd i/p
arg2p	res 1	; result

; Argument copies

arg0	res 3	; 1st i/p
arg1	res 3	; 2nd i/p
arg2	res 3	; result

; Positions to drive the axes to

dtarg_0  res 3   ; Target, axis 0
dtarg_1  res 3   ; Target, axis 1
dtarg_2  res 3   ; Target, axis 2
dtarg_3  res 3   ; Target, axis 3

; Current axis positions

pos_0	res 3   ; pos, axis 0
pos_1	res 3   ; pos, axis 1
pos_2	res 3   ; pos, axis 2
pos_3	res 3   ; pos, axis 3

; 4-dimensional Bressenham DDA

flags	res 1	; Negates and swaps
steps	res 1	; Axis step bits
d_0	res 3	; Axis 0 difference
d_1	res 3	; Axis 1 difference
d_2	res 3	; Axis 2 difference
d_3	res 3	; Axis 3 difference
i_0	res 3	; Copy of d_0
i_1	res 3	; Axis 1 increment
i_2	res 3	; Axis 2 increment
i_3	res 3	; Axis 3 increment

; Time delay values

count	res 3	; Temporary delay count
s_del	res 3	; Current delay time
d_init	res 3	; Initial delay time
dec_strt res 3	; Number of steps do do acceleration and deceleration
acc_stop res 3  ; Store for point to start decelerating
d_inc	res 3	; Number to change delay at each step
s_inc	res 3	; Number of steps before next to change of delay
s_temp	res 3	; Copy of s_inc


; +++++++++++++++++++++++++++++++++++++++++++
; **** MACROS *******************************
; +++++++++++++++++++++++++++++++++++++++++++

; Bank switching (makes code more readable)

bank_0	macro
	bcf	STATUS,RP0
	endm

bank_1	macro
	bsf	STATUS,RP0
	endm

; Check the peripheral endstops

pstop_chk macro
	bank_0
	btfss	p_stat,ZC
	goto	nxt0#v(pc1)
	btfsc	PORTA,ZC
	goto	nxt0#v(pc1)	
	bsf	e_stop,SBPZ
	goto	endstop

nxt0#v(pc1)
pc1+=1
	bcf	e_stop,SBPZ
	btfss	p_stat,XC
	goto	nxt1#v(pc2)
	btfsc	PORTA,XC
	goto	nxt1#v(pc2)	
	bsf	e_stop,SBPX
	goto	endstop		
nxt1#v(pc2)
pc2+=1
	bcf	e_stop,SBPX
	endm

; Menu chain macro

menu_m	macro	char, code
	movfw	last_i
	sublw	char
	btfss	STATUS,Z
	goto	next#v(aa)	
	goto	code

next#v(aa)
aa+=1

	endm

; Get three bytes from input to a in bank 1

get_3	macro	a
	call	rx_hex
	bank_1
	movwf	a
	call	rx_hex
	bank_1
	movwf	a+1
	call	rx_hex
	bank_1
	movwf	a+2
	endm

; Send three bytes from a in bank 1 to output

put_3	macro	a
	bank_1
	movfw	a
	call	tx_hex
	bank_1
	movfw	a+1
	call	tx_hex
	bank_1
	movfw	a+2
	call	tx_hex
	endm

; **** 2's complement 24-bit arithmetic macros ******

; Zero a 24-bit location in bank 1

clr_24	macro	n
	bank_1
	clrf	n
	clrf	n+1
	clrf	n+2
	endm

; Put addresses of arguments into pointers in bank 1

a_store	macro	i0, i1, o
	bank_1
	movlw	i0		
	movwf	arg0p
	movlw	i1
	movwf	arg1p
	movlw	o
	movwf	arg2p
	endm

; Add 2 24 bit numbers 
; output can be either input with no problem

add_24	macro	i0, i1, o
	a_store	i0, i1, o
	call	add_24s
	endm

; Subtract 2 24 bit numbers
; output can be either input with no problem

sub_24	macro	i0, i1, o
	a_store	i0, i1, o
	call	sub_24s
	endm


; Increment a 24 bit number d in bank 1

inc_24	macro	d
	bank_1
	movlw	1	  ; inc inst. doesn't set C, so add 1 to...
	addwf	d+2,1	  ; ...low byte
	btfss	STATUS,0  ; Carry means need...
	goto	ic24#v(i24)	
	addwf	d+1,1	  ; ...to increment next byte too
	btfsc	STATUS,0  ; Carry means need...	
	incf	d,1	  ; ...to increment next byte too

ic24#v(i24)
i24+=1	
	endm


; Decrement a 24 bit number d in bank 1

dec_24	macro	d
	bank_1
	movlw	1	  ; dec inst. doesn't set C, so sub 1 from...
	subwf	d+2,1	  ; ...low byte
	btfsc	STATUS,0  ; No carry means need...
	goto	dc24#v(d24)
	subwf	d+1,1	  ; ...to decrement high byte too
	btfss	STATUS,0  ; No carry means need...	
	decf	d,1	  ; ...to decrement next byte too

dc24#v(d24)
d24+=1
	endm


; Check a 24 bit number d in bank 1 for zero

z_24	macro	d
	bank_1
	movf	d+2,1	  ; set Z flag, low byte
	btfss	STATUS,Z  ; look at next?
	goto	zc24#v(z24)
	movf	d+1,1	  ; yes
	btfsc	STATUS,Z  ; look at high?
	movf	d,1

zc24#v(z24)
z24+=1
	endm	


; Negate a 24 bit number d in bank 1

neg_24	macro	d
	bank_1
	comf	d,1
	comf	d+1,1
	comf	d+2,1
	inc_24	d
	endm

; copy a 24 bit number in bank 1

cp_24	macro	a, b
	bank_1
	movfw	a
	movwf	b
	movfw	a+1
	movwf	b+1
	movfw	a+2
	movwf	b+2
	endm


; swap 2 24 bit numbers in bank 1

swp_24	macro	a, b
	cp_24	a, work
	cp_24	b, a
	cp_24	work, b
	endm

; ************ DDA macros ************

; Set negate flag bits

setnf	macro	d,N
	bank_1
	btfsc	d,7	; d negative?
	goto	n_#v(cc)
	bcf	flags,N
	goto	p_#v(cc)
n_#v(cc)
	bsf	flags,N
	neg_24	d
p_#v(cc)
cc+=1
	endm

; set swp_24 flag bits

setsf	macro	a, b, F
	sub_24	a, b, work
	bank_1
	btfsc	work,7	; difference negative?
	goto	dp#v(dd)
	bcf	flags,F
	goto	ep#v(dd)
dp#v(dd)
	bsf	flags,F
	swp_24	a, b
	
ep#v(dd)
dd+=1
	endm

; swap bits in a byte macro (surely we can do better than this?)	

bswp	macro	byte, b0, b1
	bcf	STATUS,0
	btfsc	byte,b0
	bsf	STATUS,0
	bcf	byte,b0
	btfsc	byte,b1
	bsf	byte,b0
	bcf	byte,b1
	btfsc	STATUS,0
	bsf	byte,b1
	endm

; +++++++++++++++++++++++++++++++++++++++++++


; *********** reset point *****************

	org	00		; reset vector

reset
	goto	init

; Macro counters

	local	aa
	local	bb
	local	cc
	local	dd
	local	i24
	local	d24
	local	z24
	local	pc1
	local	pc2

; ****************************************************

; 2's complement 24-bit arithmetic subroutines

; Add/subtract 2 24 bit numbers (assumes hi byte immediately precedes 
; mid byte, which preceeds lo byte) a/s number pointed to by arg0 to that 
; pointed to arg1, answer in arg2

; copy input arguments

arg_in_copy

	bank_1
	movfw	arg0p	; Copy 3 bytes pointed to by arg0p...
	movwf	FSR
	movfw	INDF
	movwf	arg0	; ... to arg0
	incf	FSR,1
	movfw	INDF
	movwf	arg0+1
	incf	FSR,1
	movfw	INDF
	movwf	arg0+2
	
	movfw	arg1p	; Copy 3 bytes pointed to by arg1p...
	movwf	FSR
	movfw	INDF
	movwf	arg1	; ... to arg1
	incf	FSR,1
	movfw	INDF
	movwf	arg1+1
	incf	FSR,1
	movfw	INDF
	movwf	arg1+2

	return


; copy output arguments

arg_out_copy
	bank_1
	movfw	arg2p	; Copy 3 bytes in arg2...
	movwf	FSR
	movfw	arg2	; ... to location pointed to by arg2p
	movwf	INDF
	incf	FSR,1
	movfw	arg2+1
	movwf	INDF
	incf	FSR,1
	movfw	arg2+2
	movwf	INDF
	return


; Add two 24 bit numbers	

add_24s
	call	arg_in_copy

	bank_1
a24int	movfw	arg0	  	; Add high bytes
	addwf	arg1,0
	movwf	arg2

	movfw	arg0+1		; Add mid bytes, maybe needing...
	addwf	arg1+1,0
	movwf	arg2+1

	btfsc	STATUS,C	; ...carry to high byte?
	incf	arg2,1		; Yes - increment it

	movfw	arg0+2	  	; Add lo bytes, maybe needing...
	addwf	arg1+2,0
	movwf	arg2+2

	btfsc	STATUS,C	; ...carry to mid byte?
	incfsz	arg2+1,1	; Yes - increment it and if result is 0...
	goto	add_done
	incf	arg2,1		; ...increment high byte too

add_done
	call	arg_out_copy
	z_24	arg2		; Set zero flag
	return


; Subtract:   arg0 - arg1 -> arg2
; Just negate and add 

sub_24s
	call	arg_in_copy
	neg_24	arg1
	goto	a24int

; *********** Time Delay *************************

; Adjust the speed

step_adjust
	bank_0
	btfss	accel,ACC		; Constant speed?
	return				; Yes - nothing to do

	sub_24	acc_stop, i_0, work 	; i_0 > acc_stop?...
	btfss	work,7			; ... work < 0?
	goto	no_acc			; No

	dec_24	s_temp			; This the one to change on?
	z_24	s_temp
	btfss	STATUS,Z
	return				; no

	sub_24	s_del, d_inc, s_del	; Yes - decrease delay
	goto	set_s_dec

no_acc					; No acceleration.  Decelerating?
	sub_24	i_0, dec_strt, work	; dec_strt > i_0?
	btfss	work,7
	return				; No - do nothing

	dec_24	s_temp			; This the one to change on?
	z_24	s_temp
	btfss	STATUS,Z
	return				; no

	add_24	s_del, d_inc, s_del	; Yes - increase delay

set_s_dec
	cp_24	s_inc, s_temp	        ; Restore steps-between increments count
	return
	

; ********************************************	

; delay using a loop of s_del steps

delay
	call	step_adjust
	cp_24	s_del, count
d_loop
	dec_24	count
	z_24	count
	btfss	STATUS,Z
	goto	d_loop
	return

; ********* Turn a nibble into its hex equivalent ***

; Should already be in bank 0 for all these hex routines

nib2hex
	movwf	save
	sublw	.9
	btfsc	STATUS,0  ; if carry is 0, W was > 9
	goto	n2hdigit

; letter
	movfw	save
	addlw	'a'-.10
	return

n2hdigit
	movfw	save
	addlw	'0'
	return

; ********* Turn a hex letter into its equivalent nibble ************************

hex2nib
	movwf	save
	sublw	'9'
	btfsc	STATUS,0  ; if carry is 0, W was > '9'
	goto	h2ndigit

; letter
	movfw	save
	addlw	.10-'a'
	return

h2ndigit
	movfw	save
	addlw	-'0'
	return			

; ********* Turn byte in w to hex in hex_l and hex_h *********

w2hex
	movwf	hex_h	; use hex_h as temp storage

	andlw	0fh	; low nibble
	call	nib2hex
	movwf	hex_l

	swapf	hex_h,0 ; high nibble
	andlw	0fh
	call	nib2hex
	movwf	hex_h
	return	

; ****** Turn hex_l and hex_h into a byte in W **********

; NB: destroys hex_h and hex_l

hex2w
	movfw	hex_l
	call	hex2nib
	movwf	hex_l
	movfw	hex_h
	call	hex2nib
	movwf	hex_h
	swapf	hex_h,0
	iorwf	hex_l,0
	return	

;**** transmit the byte in w *******

tx_w	

; last one gone?

	bank_1
	btfss	TXSTA,1		; test for end of transmission
	goto	$-1
	bank_0

; send and save byte

	movwf	TXREG
	movwf	last_o	
	return

; **** send CR/LF *****

cr_lf
	movlw	0dh
	call tx_w
	movlw	0ah
	call tx_w
	return

;**** Send W as hex ***************************

tx_hex
	bank_0
	call	w2hex
	movfw	hex_h
	call	tx_w
	movfw	hex_l
	call	tx_w
	return

; ***** Check once for a byte and return it if it's there ****

rx_poll
	bank_0
	btfss	PIR1,RCIF	; test for incoming data
	goto	no_input
	
	movfw	RCREG		; Get rcvd character
	andlw	07fh		; Junk silly bit
	movwf   last_i		; Save it
	sublw	'.'		; Test for reset character
	btfsc	STATUS,Z
	goto	reset		; Yes - reset machine

	movfw	last_i		; Get rcvd character
	btfsc	echo,0		; Maybe...
	call	tx_w		; ...echo it
	bsf	STATUS,0	; set carry bit to say we've got one
	return

no_input
	bcf	STATUS,0	; clear carry bit to say we've not got one
	return

; ** Wait for a byte

rx_w
	call	rx_poll
	btfss	STATUS,0
	goto	rx_w
	return

; ***** Get a byte in hex ***********

rx_hex
	call rx_w
	movwf	hex_h
	call rx_w
	movwf	hex_l
	call	hex2w
	return

; ****** Load up the axis patterns for various stepper strategies

; Single step

ax_ld_1
	bank_0		
	movlw	b'00001000'
	movwf	axpat
	movwf	axpat+4
	movlw	b'00000100'
	movwf	axpat+1
	movwf	axpat+5
	movlw	b'00000010'
	movwf	axpat+2
	movwf	axpat+6
	movlw	b'00000001'
	movwf	axpat+3
	movwf	axpat+7
	return

; 1.4 x Torque

ax_ld_14
	bank_0			
	movlw	b'00001100'
	movwf	axpat
	movwf	axpat+4
	movlw	b'00000110'
	movwf	axpat+1
	movwf	axpat+5
	movlw	b'00000011'
	movwf	axpat+2
	movwf	axpat+6
	movlw	b'00001001'
	movwf	axpat+3
	movwf	axpat+7
	return

; Half step

ax_ld_h
	bank_0			
	movlw	b'00001001'
	movwf	axpat
	movlw	b'00001000'
	movwf	axpat+1
	movlw	b'00001100'
	movwf	axpat+2
	movlw	b'00000100'
	movwf	axpat+3
	movlw	b'00000110'
	movwf	axpat+4
	movlw	b'00000010'
	movwf	axpat+5
	movlw	b'00000011'
	movwf	axpat+6
	movlw	b'00000001'
	movwf	axpat+7
	return

; ****** Move the robot *****************

; Hit an endstop

endstop
	clr_24	i_0		; Fool the DDA into thinking we're at the end
	return			; Return to step

; step axis 0

pstep_0				; Positive step
	bank_0
	btfsc	PORTC,AX0H	; Check for endstop
	goto	ps0		; No - all clear
	bsf	e_stop,SB0H	; Yes - stop
	goto	endstop

ps0
	bcf	e_stop,SB0H	; Not at end stop
	movlw	0fh		; Clear upper nibble of...
	andwf	PORTB,1		; Port B
	incf	axstp_0,1	; next pattern
	movlw	07h		; Mask out... 
	andwf	axstp_0,1	; ...extra bits
	movlw	axpat		; Get... 
	addwf	axstp_0,0	; ...bit...
	movwf	FSR		; ...pattern from...
	movfw	INDF		; ...lookup table
	movwf	save		; store it
	swapf	save,0		; swap active nibble into upper nibble in W
	iorwf	PORTB,1		; Set motor bits
	inc_24	pos_0	        ; ...record new position
	pstop_chk		; Check peripheral stop bits
	return

nstep_0				; Negative step
	bank_0
	btfsc	PORTC,AX0L	; Check for endstop
	goto	ns0		; No - all clear
	bsf	e_stop,SB0L	; Yes - stop
	goto	endstop

ns0
	bcf	e_stop,SB0L	; Not at end stop
	movlw	0fh		; Clear upper nibble of...
	andwf	PORTB,1		; Port B
	decf	axstp_0,1	; next pattern
	movlw	07h		; Mask out... 
	andwf	axstp_0,1	; ...extra bits
	movlw	axpat		; Get... 
	addwf	axstp_0,0	; ...bit...
	movwf	FSR		; ...pattern from...
	movfw	INDF		; ...lookup table
	movwf	save		; store it
	swapf	save,0		; swap active nibble into upper nibble in W
	iorwf	PORTB,1		; Set motor bits
	dec_24	pos_0	        ; ...record new position
	pstop_chk		; Check peripheral stop bits
	return

; Step axis 1

pstep_1				; Positive step
	bank_0
	btfsc	PORTC,AX1H	; Check for endstop
	goto	ps1		; No - all clear
	bsf	e_stop,SB1H	; Yes - stop
	goto	endstop

ps1
	bcf	e_stop,SB1H	; Not at end stop
	movlw	0f0h		; Clear lower nibble of...
	andwf	PORTB,1		; Port B
	incf	axstp_1,1	; next pattern
	movlw	07h		; Mask out... 
	andwf	axstp_1,1	; ...extra bits
	movlw	axpat		; Get... 
	addwf	axstp_1,0	; ...bit...
	movwf	FSR		; ...pattern from...
	movfw	INDF		; ...lookup table
	iorwf	PORTB,1		; Set motor bits
	inc_24	pos_1	        ; ...record new position
	pstop_chk		; Check peripheral stop bits
	return

nstep_1				; Negative step
	bank_0
	btfsc	PORTC,AX1L	; Check for endstop
	goto	ns1		; No - all clear
	bsf	e_stop,SB1L	; Yes - stop
	goto	endstop

ns1
	bcf	e_stop,SB1L	; Not at end stop
	movlw	0f0h		; Clear lower nibble of...
	andwf	PORTB,1		; Port B
	decf	axstp_1,1	; next pattern
	movlw	07h		; Mask out... 
	andwf	axstp_1,1	; ...extra bits
	movlw	axpat		; Get... 
	addwf	axstp_1,0	; ...bit...
	movwf	FSR		; ...pattern from...
	movfw	INDF		; ...lookup table
	iorwf	PORTB,1		; Set motor bits
	dec_24	pos_1	        ; ...record new position
	pstop_chk		; Check peripheral stop bits
	return

; Step axis 2

pstep_2				; Positive step
	bank_0
	btfsc	PORTD,AX2H	; Check for endstop
	goto	ps2		; No - all clear
	bsf	e_stop,SB2H	; Yes - stop
	goto	endstop

ps2
	bcf	e_stop,SB2H	; Not at end stop
	movlw	0fh		; Clear upper nibble of...
	andwf	PORTD,1		; Port D
	incf	axstp_2,1	; next pattern
	movlw	07h		; Mask out... 
	andwf	axstp_2,1	; ...extra bits
	movlw	axpat		; Get... 
	addwf	axstp_2,0	; ...bit...
	movwf	FSR		; ...pattern from...
	movfw	INDF		; ...lookup table
	movwf	save		; store it
	swapf	save,0		; swap active nibble into upper nibble in W
	iorwf	PORTD,1		; Set motor bits
	inc_24	pos_2	        ; ...record new position
	pstop_chk		; Check peripheral stop bits
	return

nstep_2				; Negative step
	bank_0
	btfsc	PORTD,AX2L	; Check for endstop
	goto	ns2		; No - all clear
	bsf	e_stop,SB2L	; Yes - stop
	goto	endstop

ns2
	bcf	e_stop,SB2L	; Not at end stop
	movlw	0fh		; Clear upper nibble of...
	andwf	PORTD,1		; Port D
	decf	axstp_2,1	; next pattern
	movlw	07h		; Mask out... 
	andwf	axstp_2,1	; ...extra bits
	movlw	axpat		; Get... 
	addwf	axstp_2,0	; ...bit...
	movwf	FSR		; ...pattern from...
	movfw	INDF		; ...lookup table
	movwf	save		; store it
	swapf	save,0		; swap active nibble into upper nibble in W
	iorwf	PORTD,1		; Set motor bits
	dec_24	pos_2	        ; ...record new position
	pstop_chk		; Check peripheral stop bits
	return


; Axis 3

pstep_3
	inc_24	pos_3	        ; ...record new position
	pstop_chk		; Check peripheral stop bits
	return

nstep_3
	dec_24	pos_3	        ; ...record new position
	pstop_chk		; Check peripheral stop bits
	return


; *************************************************

; Take the DDA one step forward

step
	bank_1
	clrf	steps		; Clear motors to move
	bsf	steps,0		; First axis always moves so...
	dec_24	i_0		; ...i_0 always steps

	add_24	i_1,d_1,i_1	; i_1 = i_1 + d_1
	btfsc	i_1,7		; I_1 < 0?
	goto	s1		; No
	sub_24	i_1, d_0, i_1	; Yes - i_1 = i_1 - d_1
	bsf	steps,1		; Step second axis
s1
	add_24	i_2,d_2,i_2	; i_2 = i_2 + d_2
	btfsc	i_2,7		; i_2 < 0?
	goto	s2		; No
	sub_24	i_2, d_0, i_2	; Yes - i_2 = i_2 - d_2
	bsf	steps,2		; Step 3rd axis
s2
	add_24	i_3,d_3,i_3	; i_3 = i_3 + d_3
	btfsc	i_3,7		; i_3 < 0?
	goto	s3		; No
	sub_24	i_3, d_0, i_3	; Yes - i_3 = i_3 - d_3
	bsf	steps,3		; Step 4th axis
s3	
	btfss	flags,SWP03	; swap 0 and 3?
	goto	mo_1
	bswp	steps,0,3
mo_1
	btfss	flags,SWP02	; swap 0 and 2?
	goto	mo_2
	bswp	steps,0,2
mo_2
	btfss	flags,SWP01	; swap 0 and 1?
	goto	mo_3
	bswp	steps,0,1
mo_3
	btfss	steps,0		; Step axis 0?
	goto	ax_1		; No
	btfss	flags,NEG0	; Yes: + or - ?
	goto	ps_0
	call	nstep_0
	bank_1
	goto	ax_1
ps_0
	call	pstep_0
	bank_1
ax_1
	btfss	steps,1		; Step axis 1?
	goto	ax_2		; No
	btfss	flags,NEG1	; Yes: + or - ?
	goto	ps_1
	call	nstep_1
	bank_1
	goto	ax_2
ps_1
	call	pstep_1
	bank_1
ax_2
	btfss	steps,2		; Step axis 2?
	goto	ax_3		; No
	btfss	flags,NEG2	; Yes: + or - ?
	goto	ps_2
	call	nstep_2
	bank_1
	goto	ax_3
ps_2
	call	pstep_2
	bank_1
ax_3
	btfss	steps,3		; Step axis 3?
	return			; No
	btfss	flags,NEG3	; Yes: + or - ?
	goto	ps_3
	call	nstep_3
	return
ps_3
	call	pstep_3
	return

; ***********************************************

; Setup DDA to move from the current position to the target position

dda_set
	sub_24	dtarg_0, pos_0, d_0	; How far to go?
	sub_24	dtarg_1, pos_1, d_1
	sub_24	dtarg_2, pos_2, d_2
	sub_24	dtarg_3, pos_3, d_3

	setnf	d_0,NEG0		; Any of them backwards?
	setnf	d_1,NEG1
	setnf	d_2,NEG2
	setnf	d_3,NEG3
	setsf	d_0,d_1,SWP01		; Any bigger than axis 0 and so need 
	setsf	d_0,d_2,SWP02		; to be swapped with it?
	setsf	d_0,d_3,SWP03

	cp_24	d_0, i_0		; Set up DDA
	cp_24	d_0, i_1
	bcf	STATUS,0
	rrf	i_1,1			; i_1 <- i_1/2
	rrf	i_1+1,1
	rrf	i_1+2,1
	neg_24	i_1
	cp_24	i_1, i_2
	cp_24	i_1, i_3

	sub_24	i_0, dec_strt, acc_stop	; Set up accelerations
	cp_24	d_init, s_del
	cp_24	s_inc, s_temp

	return

m_loop
	z_24	i_0		; If i_0 == 0, we've finished
	btfsc	STATUS,Z
	goto	done
	call	delay		; Wait for the speed-deciding time delay
	call	step		; Step the DDA
	goto	m_loop

; Movement has finished 

done
	bank_0
	clrf	PORTB		; Turn...
	movlw	0fh		; ...motors...
	andwf	PORTD,1		; ...off
	movfw	e_stop		; Send a signal when finished and...
	goto	tx_hex		; Use return at the end of tx_hex

; ********* Zero the position and flags *****************

zero_all
	clr_24	pos_0
	clr_24	pos_1
	clr_24	pos_2
	clr_24	pos_3
	clrf	e_stop		; No endstops hit
	return

; ***** Get a->d voltage, transmit it, and go back to the main loop *********

volt_0
	movlw	ADC0
	goto	volt

volt_1
	movlw	ADC1
	goto	volt

volt_2
	movlw	ADC2
	goto	volt

volt_3
	movlw	ADC3
	goto	volt

volt_4
	movlw	ADC4

volt
	movwf	ADCON0

	movlw	.12	; 12us wait...
	movwf	save	; ...for sample and hold
vloop1
	decfsz	save,1
	goto	vloop1

	bsf	ADCON0,2	; start conversion
vloop2
	btfsc	ADCON0,2	; wait till it's done
	goto	vloop2
	movfw	ADRES		; load result into W
	clrf	ADCON0		; Shut A->D down
	call	tx_hex		; Transmit the byte (use return on tx_hex)
	goto	main

; ********* Menu actions ******************

; Record the destination as the current position

targ2pos
	cp_24	dtarg_0, pos_0
	cp_24	dtarg_1, pos_1
	cp_24	dtarg_2, pos_2
	cp_24	dtarg_3, pos_3
	goto	main

; Single stepping

xnstep
	call	nstep_0
	goto	main

ynstep
	call	nstep_1
	goto	main

znstep
	call	nstep_2
	goto	main

wnstep
	call	nstep_3
	goto	main

xpstep
	call	pstep_0
	goto	main

ypstep
	call	pstep_1
	goto	main

zpstep
	call	pstep_2
	goto	main

wpstep
	call	pstep_3
	goto	main

; Set accelerating

acc_dec
	bsf	accel,ACC
	goto	move

const_spd
	bcf	accel,ACC

; Execute movement

move
	call	dda_set		; Setup the DDA
	call	m_loop		; Loop, stepping it
	goto	main

; Set target positions

to_0
	get_3	dtarg_0
	goto	main

to_1
	get_3	dtarg_1
	goto	main

to_2
	get_3	dtarg_2
	goto	main

to_3
	get_3	dtarg_3
	goto	main

; Load different motor behaviour

small_tq	; Low torque low current
	call	ax_ld_1
	goto	main

big_tq		; High torque big current
	call	ax_ld_14
	goto	main

half_stp	; Half-step the motors
	call	ax_ld_h
	goto	main

; Return current positions

where_0
	put_3	pos_0
	goto	main

where_1
	put_3	pos_1
	goto	main

where_2
	put_3	pos_2
	goto	main

where_3
	put_3	pos_3
	goto	main

; Set step time delay

s_time
	get_3	d_init
	goto	main

; Set the number of steps of acceleration

s_a_step
	get_3	dec_strt
	goto	main

; Set the acceleration delay speedup rate

s_a_inc
	get_3	d_inc
	goto	main

s_b_inc
	get_3	s_inc
	goto	main

; Get step time delay

time
	put_3	d_init
	goto	main

; Get the number of steps of acceleration

a_step
	put_3	dec_strt
	goto	main

; Get the acceleration delay speedup rate

a_inc
	put_3	d_inc
	goto	main

b_inc
	put_3	s_inc
	goto	main	

; echo on/off

e_on
	bank_0
	bsf	echo,0
	goto	main
e_off
	bank_0
	bcf	echo,0
	goto	main

; Zero endstop flags and position

zero_e_p
	call	zero_all
	goto	main

; Deal with PORT A - User's i/o

; Write to TRISA

w_trisa
	bank_0
	call	rx_hex
	movwf	TRISA
	goto	main

; Read TRISA

r_trisa
	bank_0
	movfw	TRISA
	call	tx_hex
	goto	main


; Read port A

r_porta
	bank_0
	movfw	PORTA
	call	tx_hex
	goto	main

; Write a bit to port A:

;     76543210
;         ^
;         Bit
;          ^^^
;          Which A bit to put it in

w_porta
	bank_0
	call	rx_hex
	andlw	b'00001111'
	movwf	save
	bcf	STATUS, C
	rlf	save, 0		

; Check page position for the next instruction

	addwf	PCL,1

	bcf	PORTA,0
	goto	main
	bcf	PORTA,1
	goto	main	
	bcf	PORTA,2
	goto	main	
	bcf	PORTA,3
	goto	main	
	bcf	PORTA,4
	goto	main	
	bcf	PORTA,5
	goto	main	
	bcf	PORTA,6
	goto	main	
	bcf	PORTA,7
	goto	main	

	bsf	PORTA,0
	goto	main	
	bsf	PORTA,1
	goto	main	
	bsf	PORTA,2
	goto	main	
	bsf	PORTA,3
	goto	main	
	bsf	PORTA,4
	goto	main	
	bsf	PORTA,5
	goto	main	
	bsf	PORTA,6
	goto	main	
	bsf	PORTA,7
	goto	main	

; Read an A to D converter

a_to_d
	bank_0
	call	rx_hex
	andlw	b'00000111'	; Which A->D

; Check page position for the next instruction

	addwf	PCL,1	
	goto	volt_0
	goto	volt_1	
	goto	volt_2	
	goto	volt_3	
	goto	volt_4
	goto	dud_v		; Dud A->D number
	goto	dud_v
dud_v
	movlw	0
	call	tx_hex
	goto	main	
	
; Set and get the peripheral control byte

set_pctl
	bank_0
	call	rx_hex
	movwf	p_stat
	goto	main

get_pctl
	bank_0
	movfw	p_stat
	call	tx_hex
	goto	main

; ********* initalize ******************

init
	bank_0
	clrf	PORTB		; Motors off
	clrf	PORTD
	clrf	PORTA

	bank_1			; goto page 1

	movlw	b'00000100'	; set rtcc internal div 32
	movwf	OPTION_REG

	movlw	b'10001111'	; RS232 i/p on + bottom 4 bits for endstops...
	movwf	TRISC		; ...in port C
	movlw	b'00000011'	; Top 4 bits motor o/p, bottom 2 bits for endstops...
	movwf	TRISD		; ...in port D	

	movlw	.12		; 4800 baud
	movwf	SPBRG
	movlw	b'00100000'	; Transmit async tx 8 bit
	movwf	TXSTA

	clrf	TRISB		; Port B is all outputs (motor steppers)

	clr_24	dtarg_0		; Not going anywhere
	clr_24	dtarg_1
	clr_24	dtarg_2
	clr_24	dtarg_3

	movlw	DEL_0		; Default time delay
	movwf	d_init
	movlw	DEL_1
	movwf	d_init+1
	movlw	DEL_2
	movwf	d_init+2

	movlw	ACC_0		; Default number of acceleration steps
	movwf	dec_strt
	movlw	ACC_1
	movwf	dec_strt+1
	movlw	ACC_2
	movwf	dec_strt+2

	movlw	AINC_0		; Default speedup increment
	movwf	d_inc
	movlw	AINC_1
	movwf	d_inc+1
	movlw	AINC_2
	movwf	d_inc+2
	movlw	BINC_0		; Default speedup gap
	movwf	s_inc
	movlw	BINC_1
	movwf	s_inc+1
	movlw	BINC_2
	movwf	s_inc+2

	bank_0
	clrf	p_stat		; Default is no user endstops
	clrf	accel		; Default is constant speed

       	movlw	b'10010000'	; Receive async rx 8 bit
	movwf	RCSTA

	bsf	echo,0		; Echo on

	call	ax_ld_1		; Set the energising patterns
	bank_0
	clrf	axstp_0		; Clear the counters for each axis
	clrf	axstp_1
	clrf	axstp_2
	clrf	axstp_3

	movlw	b'00111111'	; Port A all...
	movwf	TRISA		; ...inputs initially

	call	zero_all	; Set the current position as zero

; Start of the main loop

main
	bank_0
	btfss	echo,0		; If echoing, go to newline and write a prompt
	goto	get_c
	call	cr_lf		; New line
	movlw	':'		; Prompt
	call	tx_w
	movlw	' '
	call	tx_w

get_c
	call	rx_w		; Check if we've got a byte from RS232

; User has sent a byte - act on what he she or it typed

	menu_m	'A', to_0	; Set destinations <3 hex bytes>
	menu_m	'B', to_1	; <3 hex bytes>
	menu_m	'C', to_2	; <3 hex bytes>
	menu_m	'D', to_3	; <3 hex bytes>

	menu_m	'a', where_0	; Find where we are [3 hex bytes]
	menu_m	'b', where_1	; [3 hex bytes]
	menu_m	'c', where_2	; [3 hex bytes]
	menu_m	'd', where_3	; [3 hex bytes]

	menu_m	'F', acc_dec	; Accelerate and decelerate <>
	menu_m	'f', const_spd	; Go at constant speed <>

	menu_m	'T', s_time	; Set the initial time delay <3 hex bytes>
	menu_m	'S', s_a_step	; set the acceleration number of steps <3 hex bytes>
	menu_m	'I', s_a_inc	; How much to change each step <3 hex bytes>
	menu_m	'J', s_b_inc	; How many steps between changes <3 hex bytes>
	
	menu_m	't', time	; Get the initial time delay [3 hex bytes]
	menu_m	's', a_step	; Get the acceleration number of steps [3 hex bytes]
	menu_m	'i', a_inc	; Get how much to change each step [3 hex bytes]
	menu_m	'j', b_inc	; Get how many steps between changes [3 hex bytes]

	menu_m	'e', e_off	; Echo control <>
	menu_m	'E', e_on	; <>

	menu_m	'q', small_tq	; Set the motor behaviour <>
	menu_m	'Q', big_tq	; <>
	menu_m	'h', half_stp	; <>

	menu_m	'k', r_porta	; Read PORT A [1 hex byte]
	menu_m	'K', w_porta	; Write a bit to PORT A <1 hex byte 0000baaa>

	menu_m	'l', r_trisa	; Read TRISA [1 hex byte]
	menu_m	'L', w_trisa	; Write TRISA <1 hex byte>

	menu_m	'm', a_to_d	; Read an A->D converter [1 hex byte, 0..5],<1 hex byte>

	; Peripheral control byte:
	; 0000xz00 - 1 means check A3 (x) and/or A2 (z)

	menu_m	'n', get_pctl	; Read peripheral control byte [1 hex byte]
	menu_m  'N', set_pctl	; Write peripheral control byte <1 hex byte>

	menu_m	'x', xnstep	; Single stepping: -ve <>
	menu_m	'y', ynstep	; <>
	menu_m	'z', znstep	; <>
	menu_m	'w', wnstep	; <>
	menu_m	'X', xpstep	; Single stepping: +ve
	menu_m	'Y', ypstep	; <>
	menu_m	'Z', zpstep	; <>
	menu_m	'W', wpstep	; <>

	menu_m	'r', zero_e_p	; Zero the counts <>
	menu_m	'p', targ2pos	; Set the destination as the position <>

; Also a '.' sent at any time will reset the machine

	movlw	'?'		; None of the above - uh?		
	call	tx_w
	goto	main		; go again

	end
