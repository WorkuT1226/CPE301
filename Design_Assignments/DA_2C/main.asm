.org 0
sbi DDRB, 3
sbi PORTB, 3

START:
	cbi PORTB, 3
    ldi  R18, 36
    ldi  R19, 79
    ldi  R20, 221
L1:
	dec  R20
    brne L1
    dec  R19
    brne L1
    dec  R18
    brne L1
    nop
	sbi PORTB, 3
    ldi  R18, 51
    ldi  R19, 187
    ldi  R20, 224
L2:
 dec  R20
    brne L2
    dec  R19
    brne L2
    dec  R18
    brne L2
    rjmp PC+1
	jmp START