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
	LDR R2,[R0]
	LDR R3,[R1]
	LDR R4,[R0]
	LDR R5,[R1]
Loop
	CMP R2,R3
	BEQ Jump
	ADDLO R2,R2,R4
	ADDHI R3,R3,R5
	B Loop
Jump
	LDR R0,=RES
	STR R2,[R0]
Stop B Stop
NUM1 DCD 0X00000006
NUM2 DCD 0X00000005
	
	AREA Data_pg,DATA,READWRITE
RES DCD 0