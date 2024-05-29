; Syringe controller
; Adrian Bowyer
; 15 April 2005

; Clock: 4.00 MHz resonator
; Don't forget to turn the watchdog reset OFF

	LIST P=PIC16F73		; tells the assembler which PIC

	include "p16c73.h"	; PIC register definitions file
 


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
moving	res	1	; Flag for if the motor's (supposed to be) turning
step_p	res 1	; Counter for stepper bit patterns
axis_d	res 1	; Axis move direction


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

; Position to drive the syringe to

dtarg_0  res 3   ; Target, axis 0

; Current syringe position

pos_0	res 3   ; pos, axis 0

; Position to drive the axis to

dtarg_1  res 3   ; Target, axis 1

; Current axis position

pos_1	res 3   ; pos, axis 1

; Difference between the two

diff	res 3

; Time delay values

count	res 3	; Temporary delay count
s_del	res 3	; Current delay time


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




; *********** reset point *****************

	org	00		; reset vector

reset
	goto	init

; Macro counters

	local	aa
	local	i24
	local	d24
	local	z24

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
a24int	
    movfw	arg0	  	; Add high bytes
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


; ********************************************	

; delay using a loop of s_del steps

delay
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
	movwf	save	  ; Save the original number
	sublw	.9		  ; Test if > 9
	btfsc	STATUS,0  ; if carry is 0, W was > 9
	goto	n2hdigit  ; Digit output

; letter output
	movfw	save      ; Get the number back
	addlw	'a'-.10   ; Add on ASCII code for a minus 10
	return

n2hdigit              ; Digit output
	movfw	save      ; Get the number back
	addlw	'0'		  ; Just add on the ascii for 0
	return

; ********* Turn a hex letter into its equivalent nibble ************************

hex2nib
	movwf	save      ; Save the letter
	sublw	'9'       ; Subtract ASCII for 9
	btfsc	STATUS,0  ; if carry is 0, W was > '9'
	goto	h2ndigit

; letter
	movfw	save      ; Get the letter back
	addlw	.10-'a'   ; Add on ASCII code for 10 minus ASCII a
	return

h2ndigit
	movfw	save      ; Get the letter back
	addlw	-'0'	  ; Just subtract the ascii for 0
	return			

; ********* Turn byte in w to hex in hex_l and hex_h *********

w2hex
	movwf	hex_h	; use hex_h as temp storage

	andlw	0fh	    ; low nibble - and with 00001111
	call	nib2hex
	movwf	hex_l

	swapf	hex_h,0 ; high nibble, swap to low
	andlw	0fh     ; And with 00001111
	call	nib2hex
	movwf	hex_h
	return	

; ****** Turn hex_l and hex_h into a byte in W **********

; NB: destroys hex_h and hex_l

hex2w
	movfw	hex_l      ; Get the letter for the low nibble
	call	hex2nib
	movwf	hex_l      ; Store the number for the low nibble in hex_l
	movfw	hex_h      ; Same for high nibble
	call	hex2nib
	movwf	hex_h
	swapf	hex_h,0    ; Put the high number in the senior 4 bits
	iorwf	hex_l,0    ; Or the two bit patterns together
	return	

;**** transmit the byte in w *******

tx_w	

; last one we sent gone yet?

	bank_1
	btfss	TXSTA,1		; test for end of transmission
	goto	$-1         ; No - back 1 and test again
	bank_0

; send and save byte

	movwf	TXREG
	movwf	last_o	
	return

; **** send CR/LF *****

cr_lf
	movlw	0dh   ; ASCII CR
	call tx_w
	movlw	0ah   ; ASCII LF
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
	goto	no_input    ; Haven't got any - go home
	
	movfw	RCREG		; Get rcvd character
	andlw	07fh		; Junk parity bit by anding with 01111111
	movwf   last_i		; Save it
	sublw	'.'		    ; Test for reset character - the full stop
	btfsc	STATUS,Z
	goto	reset		; Yes - reset the PIC

	movfw	last_i		; Get rcvd character
	btfsc	echo,0		; Maybe...
	call	tx_w		; ...echo it
	bsf	STATUS,0	    ; set carry bit to say we've got one
	return

no_input
	bcf	STATUS,0	    ; clear carry bit to say we've not got one
	return

; ** Wait for a byte

rx_w
	call	rx_poll     ; Got one?
	btfss	STATUS,0    ; if...
	goto	rx_w        ; ...not loop till we have
	return              ; Got one.

; ***** Get a byte in hex ***********

rx_hex
	call rx_w
	movwf	hex_h
	call rx_w
	movwf	hex_l
	call	hex2w
	return

; ***********************************************

; Syringe motor control
; Bits control the motor directly 
; PORTC, bits 1 and 2 are the BA6286 control bits


s_forward
	bank_0
	bcf		PORTC,1
	bsf		PORTC,2
	clrf	moving
	bsf		moving, 0
	return

s_backward
	bank_0
	bsf		PORTC,1
	bcf		PORTC,2
	clrf	moving
	bsf		moving, 1
	return

s_stop
	bank_0
	bcf		PORTC,2
	bcf		PORTC,1
	clrf	moving
	return

; ***********************************************

; Axis motor control
; axis_d bit 0 is a flag for which direction to go
; Port B, bits 5,6,7, and 8 control the two BA6286s

a_forward
	bank_0
	bsf	axis_d,0
	return

a_backward
	bank_0
	bcf	axis_d,0
	return

; Take one step

a_step
	bank_0
	btfsc	axis_d,0   ; Forward?
	goto	a_back     ; No - backward
	incf	step_p,f   ; Forward - increment pattern counter
	goto	a_m        ; Actually move

a_back
	decf	step_p,f   ; Backward - decrement pattern counter

a_m
	movlw	b'00000011' ; Mask out all but the two...
	andwf	step_p,f    ; ...most junior bits of step_p so
	movfw	step_p      ; ...it's always mod 4
	call	lookup      ; Get the bit pattern for...
	movwf	PORTB       ; Port B
	return

lookup                  ; Lookup the 4 bit patterns
	addwf	PCL,f       ; Add W (which is 0 .. 3) to the program counter
	retlw	b'01010000' ; Jump here for W==0,...
	retlw	b'01100000' ; ...W==1,...
	retlw	b'10100000' ; ...W==2,...
	retlw	b'10010000' ; or ...W==3

a_stop                  ; Needed for backwards compatibility
	return

; ************************************************

; Optical sensor monitoring for syringe toothed wheel

hl_wait				; Wait for a high-low transition on PORTB bit 0
	bank_0
	btfss	PORTB,0
	goto	hl_wait
hl
	btfsc	PORTB,0
	goto	hl
	return

lh_wait				; Wait for a low-high transition
    bank_0
	btfsc	PORTB,0
	goto	lh_wait
lh
	btfss	PORTB,0
	goto	lh
	return


; *************** Syringe drive loop **************

move_s
	sub_24	dtarg_0, pos_0, diff  ; Get the number of steps
	z_24	diff                  ; Is it...
	btfsc	STATUS,Z              ; ...zero?
	return		  		          ; Yes - nothing to do, so go home
	btfsc	diff,7                ; Is it...
    goto	s_neg_d				  ; ...negative?
    call	s_forward			  ; No - go forward
    goto	s_pulse_count

s_neg_d							  ; Yes - go backward
	neg_24	diff				  ; Negate the count
	call	s_backward

s_pulse_count					  ; Wait for...
	call	hl_wait               ; ...optoswitch pulses
	dec_24	diff				  ; Got one - decrement count
	z_24	diff				  ; Count = ...
	btfss	STATUS,Z              ; ...0?
	goto	s_pulse_count         ; No - go do another

                                  ; Yes.  All done; update...
	cp_24	dtarg_0, pos_0		  ; ...the current position
	call	s_stop
	return

; *************** Axis drive loop **************

move_a
	sub_24	dtarg_1, pos_1, diff  ; Get the number of steps
	z_24	diff                  ; Is it...
	btfsc	STATUS,Z              ; ...zero?
	return		  		  		  ; Yes - nothing to do so go home
	btfsc	diff,7                ; Is it...
    goto	a_neg_d				  ; ...negative?
    call	a_forward			  ; No - go forward
    goto	a_pulse_count

a_neg_d							  ; Yes - go backward
	neg_24	diff				  ; Negate the count
	call	a_backward

a_pulse_count
	call	a_step                ; Take one step
	call	delay				  ; Time delay between steps
	dec_24	diff				  ; Decrement count
	z_24	diff				  ; Count = ...
	btfss	STATUS,Z              ; ...0?
	goto	a_pulse_count         ; No - go do another

                                  ; All done; update...
	cp_24	dtarg_1, pos_1		  ; ...the current position
	call	a_stop
	return

; *************** Axis + syringe drive loop **************

; Turn on the syrings (NB - No speed control or counting) and
; Then run the movement axis till it stops, then turn off the syringe.

move_as
	call	s_forward
	call	move_a
	call	s_stop
	goto	main

; ********* Menu actions ******************

; Execute movements

move_sm             ; Move syringe
	call	move_s
	goto	main

move_am             ; Move axis
	call	move_a
	goto	main

move_asm            ; Move both syringe and axis together
	call	move_as
	goto	main

step_pos            ; Axis one step forward
	call	a_forward
	call	a_step
	goto	main

step_neg            ; Axis one step backward
	call	a_backward
	call	a_step
	goto	main

; Record the destination as the current position
; This allows any value to be set as the curreent position

targ2pos
	cp_24	dtarg_0, pos_0
	goto	main

; Set syringe goto position

to_0
	get_3	dtarg_0
	goto	main

; Return current syringe position

where_0
	put_3	pos_0
	goto	main

; Set axis goto position

to_1
	get_3	dtarg_1
	goto	main

; Return current axis positions

where_1
	put_3	pos_1
	goto	main

; Set time delay for axis stepper

to_d
	get_3	s_del
	goto	main

; Return current time delay

where_d
	put_3	s_del
	goto	main

; Turn character echo on/off

e_on
	bank_0
	bsf	echo,0
	goto	main
e_off
	bank_0
	bcf	echo,0
	goto	main

; Set current positions and destinations to 0

zero_e_p
	bank_1
	clr_24	pos_0
	clr_24	dtarg_0
	clr_24	pos_1
	clr_24	dtarg_1
	bank_0
	return	

; ********* initalize ******************

; When the PIC is reset/turned-on this is where it jumps to

init

	bank_1				; goto page 1

	movlw	b'00000100'	; set rtcc internal div 32
	movwf	OPTION_REG

	movlw	b'10000000'	; RS232 i/p on 
	movwf	TRISC		; ...in port C, rest outputs

	movlw	.12	    	; 4800 baud
	movwf	SPBRG
	movlw	b'00100000'	; Transmit async tx 8 bit
	movwf	TXSTA

	movlw	b'00001111'
	clrf	TRISB		; Senior Port B is output, junior input

	call	zero_e_p	; Not going anywhere

	clr_24	s_del
	movlw	0x02		; Set default delay to hex 000200
	movwf	s_del+1

	bank_0

    movlw	b'10010000'	; Receive async rx 8 bit
	movwf	RCSTA
	clrf	PORTB		; Motors off
	bsf		echo,0		; Echo on
	clrf	step_p      ; Actually axis stepper could be at any of 4 positions,
                        ; but we have no way of knowing which.

; Start of the main loop

main
	bank_0
	btfss	echo,0		; If echoing, go to newline and write a prompt
	goto	get_c       ; If not, just wait for an input character
	call	cr_lf		; New line
	movlw	':'			; Prompt
	call	tx_w
	movlw	' '
	call	tx_w

get_c
	call	rx_w		 ; Check if we've got a byte from RS232 input

; User has sent a byte - act on what he she or it typed
; <Q> means input Q needed; [R] means output R returned

	menu_m	'A', to_0	 ; Set syringe destinations <3 hex bytes>

	menu_m	'a', where_0 ; Find where syringe is [3 hex bytes]

	menu_m	'B', to_1	 ; Set axis destination <3 hex bytes>

	menu_m	'b', where_1 ; Find where axis_is [3 hex bytes]

	menu_m	'D', to_d	 ; Set delay <3 hex bytes>

	menu_m	'd', where_d ; Find delay [3 hex bytes]

	menu_m	's', move_sm ; Move syringe <>

    menu_m	'x', move_am  ; Move axis <>

    menu_m  'X', move_asm ; Turn on syringe, move axis, turn off syringe <>

	menu_m	'>', step_pos	  ; Single axis step + <>
	menu_m	'<', step_neg	  ; Single axis step - <>

	menu_m	'e', e_off	 ; Echo control <>
	menu_m	'E', e_on	 ; <>

	menu_m	'r', zero_e_p	; Zero the counts <>
	menu_m	'p', targ2pos	; Set the destination as the position <>

; Also a '.' sent at any time will reset the machine

	movlw	'?'		    ; None of the above - uh?		
	call	tx_w
	goto	main		; go again

	end
