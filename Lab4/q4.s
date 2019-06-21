	AREA    RESET, DATA, READONLY
    EXPORT  __Vectors
__Vectors 
	DCD  0x40001000     ; stack pointer value when stack is empty
    DCD  Reset_Handler  ; reset vector
    ALIGN
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
	LDR R0,=hex
	MOV R5,#0
	MOV R7,#32
	LDR R1,[R0]
up2	BL divide
	CMP R1,#0
	BNE up2
	LDR R0,=bcd
	LSR R5,R5,R7
	STR R5,[R0]
STOP B STOP
divide 
	MOV R3,#0
up1 CMP R1,#0x0A
	BLO down
	SUB R1,#0x0A
	ADD R3,#1
	B up1
down
	ORR R5,R5,R1
	ROR R5,#4
	MOV R1,R3
	SUB R7,#4
	BX LR
hex DCD 0x62
	AREA mydata,DATA
bcd DCD 0