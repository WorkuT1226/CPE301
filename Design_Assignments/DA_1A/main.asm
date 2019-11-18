.include<m328pdef.inc>

.ORG 0
LDI R25, 0x10; //load register with value 00010000
LDI R24, 0x10; //load register with value 00010000
LDI R23, 0x01; //load register with value 00000001
LDI R22, 0x01; //load register with value 00000001
LDI R16,0; //load register with value 0
LDI R17,0; //load register with value 0
LDI R18,0; //load register with value 0
LDI R19,0; //load register with value 0
LDI R20,0; //load register with value 0
LDI R21,0; //load register with value 0
INC R22; //load register with value 0

TARGET1:
ADD R17,R24; //add value 00010000 to R17
ADD R18,R25; //add value 00010000 to R18
ADD R19,R16; 
ADD R20,R22; 
DEC R22; //Decrement R22 by 1
BRNE TARGET1; //goes to TARGET1 if branch not equal

COM R23;
INC R23; //increment R23 by 1

TARGET2:
ADD R17,R24;
ADD R18,R25;
ADD R19,R16;
ADD R20,R21;
DEC R23; //Decrement R23 by 1
BRNE TARGET2 //goes to TARGET2 if branch not equal

