	AREA RESET,DATA,READONLY
	EXPORT __Vectors
__Vectors
	DCD 0x40001000
	DCD Reset_Handler
	ALIGN
	AREA mycode,CODE,READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
	LDR R0,=Src;LOAD ADDRESS OF SRC IN REGISTER R0
	LDR R1,=DST;LOAD ADDRESS OF DST IN REGISTER R1
	LDR R2,[R0];LOAD ADDRESS OF REGISTER R0 IN REGISTER R2
	STR R2,[R1];STORE VALUE OF R2 TO R1
STOP B STOP
	AREA data1,DATA,READWRITE
Src DCD 0
DST DCD 0