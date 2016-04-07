;;===============================
;;Name: Ramamurthy Siripuram
;;===============================

.orig x3000

	LD R6, STACK			; load the stack pointer

	LD R0, N				; R0 = N
	ADD R6, R6, -1			; push argument N on stack
	STR R0, R6, 0			

	JSR TWOTORIAL

	LDR R0, R6, 0			; load return value off top of stack
	ADD R6, R6, 2 			; restore stack to previous value

	ST R0, ANSWER			; store answer
	HALT

N 		.fill 10
ANSWER 	.blkw 1
STACK 	.fill xF000
  
TWOTORIAL	ADD R6, R6, -3;		space for RV, RA, OFP
			STR R7, R6, 1;		store RA
			STR R5, R6, 0;		store OFP
			ADD R5, R6, -1;		new FP
			ADD R6, R6, -1;		space for locals

			LDR R0, R5, 4;		load N into R0
			ADD R0, R0, -2;		N-2
			STR R0, R5, 0;		push N-2 onto stack

			LDR R0, R5, 4;		load N into R0
			BRp NEXT
			AND R0, R0, 0;		R0 = 0
			STR R0, R5, 3;		push 0 into RV
			ADD R6, R5, 3;		point R6 at RV
			LDR R7, R5, 2;		restore RA to RV
			LDR R5, R5, 1;		restore R5 to OFP
			RET

NEXT		LDR R0, R5, 0;		R0 = N-2
			ADD R6, R6, -1;
			STR R0, R6, 0;		push N-2 onto stack
			JSR TWOTORIAL;		TWOTORIAL(N-2)
			LDR R0, R6, 0;		R0 = TWOTORIAL(N-2)
			ADD R6, R6, 2;		move R6 back down, pop RV and N-2 off stack
			LDR R1, R5, 4;		R1 = N
			ADD R0, R1, R0;		R0 = N + R0

			STR R0, R5, 3;		RV = N + N -2;
			ADD R6, R5, 3;		point R6 at RV
			LDR R7, R5, 2;		restore RA to RV
			LDR R5, R5, 1;		restore R5 to OFP
			RET
.end
