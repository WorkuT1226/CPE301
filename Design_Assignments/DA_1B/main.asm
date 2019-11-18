.EQU STARTADDS = 0x0200 //set STARTADDS to 0x200
.EQU COUNTER = 250 //set counter to 250

.org 0

CLR R0 //clear R0
LDI XL, LOW(STARTADDS) //sets low bits of register X (R26)
LDI XH, HIGH(STARTADDS)//set high bits of register X (R27)

LDI YL, LOW(0x300)//set low bits of register Y(R28) to 0x300
LDI YH, HIGH(0x300)//set high bits of register Y(R29) to 0x300


LDI ZL, LOW(0x500)//set low bits of register Y(R30) to 0x500
LDI ZH, HIGH(0x500)//set high bits of register Y(R31) to 0x500

LDI R22, 6 //load immediate value 6 into R22
LDI R21, Counter //load counter value into R21

BEGIN:
		MOV R23, R22 //move value in R22 to R23.
		ST	X+,  R22 //store value X is pointing at to R22 then increment by 1.
		JMP L1 //jump to L1 target

L1:
		SUBI R23, 0x05 //subtract immediate value 0x05 from value in R23
		BREQ L3 //branch if equal jump to L3 target
		BREQ L2 //branch if equal jump to L2 target.
		JMP L1 //jump to L1 target

L2:		ST Y+, R22 //store value Y is pointing at to R22 then increment by 1.
		ADD R16, R22 //add value in R22 to R16
		ADC R17, R0 //add with carry value in R0 to R17
		JMP END // jump to END target

L3:
		ST Z+, R22 //store value Z is pointing at to R28 then increment by 1
		ADD R18, R22 // add value in R28 to R18.
		ADC R19, R0 //add with carry value in R0 to R19.
		JMP END //jump to END target

END:	INC R22 //increment R28 by 1.
		DEC R21 //decrement counter by 1
		BRNE BEGIN //branch if not equal back to BEGIN target.
		BREAK //break loop