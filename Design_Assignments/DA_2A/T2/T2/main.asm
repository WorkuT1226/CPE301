; T2.asm
; Created: 10/5/2019 6:51:36 PM
; Author : Worku Tafara
;
.org 0
sbi DDRC, 3
sbi	PORTC, 3
sbi	DDRB, 3
sbi PORTB, 3

START:
	cbi	PORTC, 3
	cbi PORTB, 3
    ldi  R18, 109
    ldi  R19, 51
    ldi  R20, 106
L1: 
	dec  R20
    brne L1
    dec  R19
    brne L1
    dec  R18
    brne L1
	jmp START
