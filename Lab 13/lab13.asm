; ==========================
; CS2110 Lab 13 Spring 2016
; Name: Ramamurthy Siripuram
; ==========================

;@plugin filename=lc3_udiv vector=x80

; Main
; Do not edit this function!

.orig x3000

	; Initialize stack
	LD R6, STACK

	; Call digisum(n)
	LD R0, N
	ADD R6, R6, -1
	STR R0, R6, 0
	JSR DIGISUM

	; Pop return value and arg off stack
	LDR R0, R6, 0
	ADD R6, R6, 2

	; Save the answer
	ST R0, ANSWER

	HALT

STACK
	.fill xF000
N
	.fill 45
ANSWER
	.blkw 1

; To call UDIV, use TRAP x80
; Preconditions:
;    R0 = X
;    R1 = Y
; Postconditions:
;    R0 = X / Y
;    R1 = X % Y

DIGISUM	ADD R6, R6, -3;		space for RV, RA, OFP
		STR R7, R6, 1;		store RA
		STR R5, R6, 0;		store OFP
		ADD R5, R6, -1;		new FP
		ADD R6, R6, -2;		space for locals

		LDR R0, R5, 4;		load n into R0
		AND R1, R1, 0;		
		ADD R1, R1, 10;		10 in R1
		TRAP x80;
		STR R0, R5, 0;		div = n/10
		STR R1, R5, -1;		mod = n%10

		LDR R0, R5, 4;		load n into R0
		BRnp ELSE;
		AND R0, R0, 0;		R0 = 0
		STR R0, R5, 3;		RV = 0
		ADD R6, R5, 3;		point R6 at RV
		LDR R7, R5, 2;		restore RA to RV
		LDR R5, R5, 1;		restore R5 to OFP
		RET

ELSE	LDR R0, R5, 0;		R0 = div
		ADD R6, R6, -1;
		STR R0, R6, 0;		push div onto stack
		JSR DIGISUM;		digisum(div)
		LDR R0, R6, 0;		R0 = digisum(div)
		ADD R6, R6, 2;		move R6 back down, popping RV and the div param off the stack
		LDR R1, R5, -1;		R1 = mod
		ADD R0, R1, R0;		R0 - mod + digisum(div)

		STR R0, R5, 3;		RV = 0;
		ADD R6, R5, 3;		point R6 at RV
		LDR R7, R5, 2;		restore RA to RV
		LDR R5, R5, 1;		restore R5 to OFP
		RET

.end
