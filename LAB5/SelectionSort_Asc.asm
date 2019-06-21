	AREA RESET,DATA,READONLY
	EXPORT __Vectors
__Vectors
	DCD 0X10001000
	DCD Reset_Handler
	ALIGN
	
	AREA mycode,CODE,READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
	LDR R1,=0X29
	LDR R2,=0X56
	LDR R3,=0X98
	LDR R4,=0X12
	LDR R5,=0X99
	LDR R6,=0X15
	LDR R7,=0X21
	LDR R8,=0X30
	LDR R9,=0X22
	LDR R10,=0X28
	
	LDR R0,=0X10000000		;stack ptr
	STM R0!,{R1-R10}
	MOV R9,R0
	SUB R0,#40
	MOV R8,#9		;parse
label1
	MOV R7,R8		;comparision
	MOV R1,R0
label2
	LDR R2,[R0]
	LDR R3,[R1,#4]!
	CMP R2,R3
	BLS skip1
	STR R2,[R1]
	STR R3,[R0]
	
skip1 
	SUB R7,#1
	TEQ R7,#0
	BNE label2
	ADD R0,#4
	SUB R8,#1
	TEQ R8,#0
	BNE label1
	
	MOV R0,R9
	LDMDB R0,{R1-R10}
stop B stop
	
	

	
	
	