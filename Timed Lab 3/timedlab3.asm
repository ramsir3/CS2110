;;===============================
;; NAME:
;;===============================

.orig x3000
		LD R0, ARRAY		; store current index here

		LD R1, ARRAY		;
		NOT R1, R1			;
		ADD R1, R1, 1		; negate R1

		LD R6, ASKED_VAL	;
		NOT R6, R6			;
		ADD R6, R6, 1		; negate R6

		AND R5, R5, 0		; store ODD_CNT in R5
		ST R5, ODD_CNT		; store ODD_CNT
		
LOOP	ADD R4, R1, R0		; subtract offset from current address to get index
		ADD R4, R4, 1		; add 1 to get the length
		ST R4, LENGTH		; store length

		LDR R2, R0, 0		; load array element into R2
		ADD R2, R2, R6		;
		BRz FIND			; current value - ASKED_VAL == 0

ELS1	LDR R2, R0, 0		; load array element into R2
		AND R2, R2, 1		; if odd R2 = 1
		ADD R2, R2, -1		;
		BRz FODD			; R2 - 1 == 0

ELS2	ADD R0, R0, 1		; increment R0
		LDR R2, R0, 0		; load current value
		ADD R2, R2, 1		;
		BRnp LOOP			; R2 + 1 == 0
	    HALT

FIND	ADD R4, R1, R0		; subtract offset from current address to get index
		ST R4, ASKED_IND	; store index
		BR ELS1				; return to method

FODD	ADD R5, R5, 1		; increment R5
		ST R5, ODD_CNT		; store ODD_CNT
		BR ELS2				; return to method


ASKED_VAL .fill 9     ; You must find the index of this value in the array
ASKED_IND .blkw 1     ; Store the index of the asked value in the array
ODD_CNT   .blkw 1     ; Store the total number of odd entries in the array here
LENGTH    .blkw 1     ; Store the length of the array at this label
ARRAY     .fill x7000 ; This is where the array is located in memory

.end

.orig x7000
        .fill 1       ; The first element of the array
        .fill 3
        .fill 7
        .fill 4
        .fill 2
        .fill 9
        .fill 3
        .fill 4       ; The last element of the array
        .fill -1      ; -1 will follow the last element of the array  
.end
