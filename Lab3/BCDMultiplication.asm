	AREA RESET,DATA,READONLY
	EXPORT __Vectors
__Vectors
	DCD 0X10001000
	DCD Reset_Handler
	ALIGN
	AREA Code_pg,CODE,READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler

	LDR R0,=NUM1		
	LDR R1,=NUM2
	LDR R2,[R0]			;store 1
	LDR R3,[R1]			;store 2
Loop
	BL BCDadd
	SUB R3,#1
	TEQ R3,#0
	BNE Loop
	LDR R0,=RES
	STR R2,[R0]
Stop B Stop

BCDadd
	MOV R8,#9		;count
	MOV R6,#0		;carry
LoopFN
	AND R4,R2,#0X0F		;extract last digit
	AND R10,R9,#0X0F
	ADD R5,R10,R4		
	ADD R5,R6			;add carry
	CMP R5,#0X0A		
	BLO Carry
	MOV R6,#1
	SUB R5,#0X0A
	B Next
Carry
	MOV R6,#0
Next
	LSR R2,#4		;shift original
	LSR R9,#4
	ORR R7,R5		;accumulator
	ROR R7,#4		;rotate
	SUB R8,#1		
	TEQ R8,#0
	BNE LoopFN
	STR R7,R9
	BX LR 