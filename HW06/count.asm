;;===============================
;;Name: Ramamurthy Siripuram
;;===============================

		.orig x3000
		AND R0, R0, 0; Clear reg 0, will be counter
		LD R1, ARRAY; Load starting address into reg 1
		LD R3, LENGTH;
		ADD R3, R1, R3;
		ADD R3, R3, #-1; Get address of the last entry of array
		NOT R3, R3;
		ADD R3, R3, #1; Negate value in reg 3
LOOP	LDR R2, R1, 0; Get value in array
		BRn INCR;
NEXT	ADD R1, R1, #1;
		ADD R4, R3, R1;
		BRnz LOOP;
		ST R0, ANSWER;
		HALT;
INCR	ADD R0, R0, #1; Increment counter
		BR NEXT;
			
		ARRAY   .fill x6000
		LENGTH  .fill 10
		ANSWER	.fill 0		; The answer should have the number of negative values when finished.
		.end

		.orig x6000
		.fill -20
		.fill 14
		.fill 7
		.fill 0
		.fill -3
		.fill 11
		.fill 9
		.fill -9
		.fill 2
		.fill -5
		.end
