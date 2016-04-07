;;===============================
;;Name: Ramamurthy Siripuram
;;===============================

.orig x3000
	LD R6, STACK			; load the stack pointer

	LD R0, N				; R0 = N
	ADD R6, R6, -1			; push argument N on stack
	STR R0, R6, 0			

	JSR POWERSOF2

	LDR R0, R6, 0			; load return value off top of stack
	ADD R6, R6, 2 			; restore stack to previous value

	ST R0, ANSWER			; store answer
	HALT

N 		.fill 5
ANSWER 	.blkw 1
STACK 	.fill xF000


POWERSOF2	ADD R6, R6, -3;		space for RV, RA, OFP
			STR R7, R6, 1;		store RA
			STR R5, R6, 0;		store OFP
			ADD R5, R6, -1;		new FP
			ADD R6, R6, -2;		space for locals

			LDR R0, R5, 4;		load N into R0
			BRnp NEXT1;
			AND R0, R0, 0;		clear R0
			ADD R0, R0, 1;		R0 = 1
			STR R0, R5, 3;		push 0 into RV
			ADD R6, R5, 3;		point R6 at RV
			LDR R7, R5, 2;		restore RA to RV
			LDR R5, R5, 1;		restore R5 to OFP
			RET

NEXT1		ADD R0, R0, -1;		N-1 == 0 : N == 1
			BRnp NEXT2;
			AND R0, R0, 0;		clear R0
			ADD R0, R0, 2;		R0 = 2
			STR R0, R5, 3;		push 0 into RV
			ADD R6, R5, 3;		point R6 at RV
			LDR R7, R5, 2;		restore RA to RV
			LDR R5, R5, 1;		restore R5 to OFP
			RET

NEXT2		LDR R0, R5, 4;		R0 = N
			ADD R0, R0, -1;		R0 = N-1
			ADD R6, R6, -1;
			STR R0, R6, 0;		push N-1 onto stack
			JSR POWERSOF2;		POWERSOF2(N-1)
			LDR R0, R6, 0;		R0 = temp1 = POWERSOF2(N-1)
			ADD R6, R6, 2;		move R6 back down, pop RV and N-1 off stack
			STR R0, R5, 0;		push temp1 onto stack

			LDR R0, R5, 4;		R0 = N
			ADD R0, R0, -2;		R0 = N-2
			ADD R6, R6, -1;
			STR R0, R6, 0;		push N-2 onto stack
			JSR POWERSOF2;		POWERSOF2(N-2)
			LDR R0, R6, 0;		R0 = temp2 = POWERSOF2(N-2)
			ADD R6, R6, 2;		move R6 back down, pop RV and N-2 off stack
			STR R0, R5, -1;		push temp2 onto stack

			LDR R0, R5, 0;		load temp1 into R0
			ADD R2, R0, R0;
			ADD R0, R2, R0;		R0 = 3*R0
			LDR R1, R5, -1;		load temp2 into R1
			ADD R1, R1, R1;		R1 = 2*R1
			NOT R1, R1;
			ADD R1, R1, 1;		negate R1
			ADD R0, R0, R1;

			STR R0, R5, 3;		RV = R0;
			ADD R6, R5, 3;		point R6 at RV
			LDR R7, R5, 2;		restore RA to RV
			LDR R5, R5, 1;		restore R5 to OFP
			RET
.end
