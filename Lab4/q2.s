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

	LDR R0,=NUM
	LDR R1,=RES
	MOV R2,#8
	LDR R3,[R0]
	MOV R5,#1
	MOV R7,#0
	MOV R8,#0X0A
	
Loop
	AND R4,R3,#0X0F
	LSR R3,#4
	MLA R7,R4,R5,R7
	MUL R5,R5,R8
	SUB R2,#1
	TEQ R2,#0
	BNE Loop
	STR R7,[R1]
Stop B Stop
NUM DCD 0X00000013
	AREA Data_pg,DATA,READWRITE
RES DCD 0