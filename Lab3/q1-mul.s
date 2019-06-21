	AREA RESET, DATA, READONLY
	EXPORT __Vectors
__Vectors
	DCD 0x10001000
	DCD Reset_Handler
	ALIGN
	
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
	LDR R0,=num1
	LDR R1,=num2
	MOV R2, #0
	MOV R3, #0
	LDR R5,[R1]
Loop
	LDR R4,[R0]
	ADDS R2,R4
	ADC R3,#0
	SUB R5,#1
	TEQ R5,#0
	BNE Loop
	LDR R0, =result
	STR R2,[R0],#4
	STR R3,[R0]
Stop B Stop
num1 DCD 5
num2 DCD 2
	AREA Data_pg,DATA,READWRITE
result DCD 0, 0