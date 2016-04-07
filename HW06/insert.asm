;;===============================
;;Name: Ramamurthy Siripuram
;;===============================

.orig x3000
		LD R0, ARRAY; Load starting address of array
		LD R1, LENGTH; Load length of array
		ADD R1, R0, R1;
		NOT R1, R1;
		ADD R1, R1, #1; Negate R1
		ADD R0, R0, #1; Get address of second element in array
LP1		LDR R2, R0, 0; Get value in current index of array
		ADD R3, R0, 0; Put address in R0 into R3
LP2 	ADD R6, R3, #-1
		LDR R5, R6, 0;
		NOT R4, R5;
		ADD R4, R4, #1; Negate R5
		ADD R4, R2, R4;
		BRn NEXT;
ELSE	STR R2, R3, 0;
		ADD R0, R0, #1;
		ADD R4, R0, R1;
		BRn LP1;
		HALT;
NEXT	STR R5, R3, 0;
		ADD R3, R3, #-1;
		LD R4, ARRAY;
		NOT R4, R4;
		ADD R4, R4, #1; Negate R4
		ADD R4, R3, R4;
		BRp LP2;
		BR ELSE;


;; CODE GOES HERE! :D

ARRAY   .fill x6000
LENGTH  .fill 12
.end

.orig x6000
.fill 27
.fill 5
.fill -18
.fill 165
.fill -101
.fill 10
.fill 34
.fill 0
.fill -7
.fill 88
.fill 9
.fill 212
.end

