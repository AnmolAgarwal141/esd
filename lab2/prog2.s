    AREA RESET, DATA, READONLY
	EXPORT __Vectors
__Vectors
	DCD 0x40001000
	DCD Reset_Handler
	ALIGN
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
	LDR R0, = src+(len-1)*4
	LDR R1, = src+(2*len-1-lap)*4
	MOV R3,#10
up
	LDR R2,[R0],#-4
	STR R2,[R1],#-4
	SUB R3,#1
	TEQ R3,#0
	BNE up
STOP B STOP
len EQU 10
lap EQU 5
	AREA data1, DATA, READWRITE
src DCD 0,0,0,0,0,0,0,0,0,0
DST DCD 0,0,0,0,0,0,0,0,0,0