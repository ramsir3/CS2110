;;===============================
;;Name: Ramamurthy Siripuram
;;===============================

.orig x3000

	LD R6, STACK			; load the stack pointer

	AND R0, R0, 0
	ADD R6, R6, -1			; push argument idx=0 on stack
	STR R0, R6, 0 

	LD R0, ARRAY1			; R0 = ARRAY1, change later to ARRAY2 and ARRAY3 for testing
	ADD R6, R6, -1 			; allocate spot on stack
	STR R0, R6, 0			; push argument ARRAY on stack

	JSR ARRAYHOP

	LDR R0, R6, 0			; load return value off top of stack
	ADD R6, R6, 3 			; restore stack to previous value

	ST R0, ANSWER			; store answer
	HALT

ARRAY1 	.fill x5000
ARRAY2	.fill x5010
ARRAY3  .fill x5020
ANSWER 	.blkw 1
STACK 	.fill xF000


ARRAYHOP	ADD R6, R6, -3;		space for RV, RA, OFP
			STR R7, R6, 1;		store RA
			STR R5, R6, 0;		store OFP
			ADD R5, R6, -1;		new FP
			ADD R6, R6, -1;		space for locals

			LDR R0, R5, 5;		load idx into R0
			LDR R1, R5, 4;		load array pointer into R1
			ADD R1, R1, R0;		R1 = address of idx position in array
			LDR R0, R1, 0;		R0 = array[idx];
			STR R0, R5, 0;		push array[idx] onto stack

			LDR R0, R5, 0;
			BRnp ELSE;

			AND R0, R0, 0;		R0 = 0
			STR R0, R5, 3;		push 0 into RV
			ADD R6, R5, 3;		point R6 at RV
			LDR R7, R5, 2;		restore RA to RV
			LDR R5, R5, 1;		restore R5 to OFP
			RET

ELSE		ADD R6, R6, -2;
			STR R0, R6, 1;		push array[idx] onto stack
			STR R1, R6, 0;		push array pointer onto stack
			JSR ARRAYHOP;		ARRAYHOP(ARRAY, ARRAY[idx])
			LDR R0, R6, 0;		R0 = ARRAYHOP(ARRAY, ARRAY[idx])
			ADD R6, R6, 2;		move R6 back down, pop RV and R0 off stack
			ADD R0, R0, 1;		R0 = 1 + R0

			STR R0, R5, 3;		RV = R0;
			ADD R6, R5, 3;		point R6 at RV
			LDR R7, R5, 2;		restore RA to RV
			LDR R5, R5, 1;		restore R5 to OFP
			RET

.end

; 4 hops
.orig x5000
.fill 2
.fill 1
.fill 3
.fill 0
.fill -1
.fill -1
.end

; 5 hops
.orig x5010
.fill 1
.fill 1
.fill 1
.fill 3
.fill 0
.fill -12
.fill -2
.end

; 12 hops
.orig x5020
.fill 5
.fill 1
.fill 0
.fill -3
.fill 10
.fill -1
.fill 5
.fill 20
.fill 2
.fill 3
.fill 1
.fill -2
.fill 9
.fill 14
.fill 3
.fill 20
.fill -2
.fill -7
.fill 5
.fill 1
.fill -18
.fill -2
.end
