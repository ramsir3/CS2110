; ==========================
; CS2110 Lab 15 Spring 2016
; Name: Ramamurthy Siripuram
; ==========================

.orig x40

	.fill x5000;

.end

.orig x3000

	; This is main. Do not modify it!

	LD R0, STRING
	TRAP x40
	PUTS

	HALT ; After halting, R0 - R6 should still contain their original values

STRING	.fill x4000
.end

.orig x4000
	.stringz "Hello, World! 123456789 !@#$%^&*"
.end

.orig x5000

		; TODO implement your trap here
		ST R0, ZERO;
		ST R1, ONE;
		ST R2, TWO;

		LD R1, ZERO;
		ADD R1, R1, -1;

LOOP	ADD R1, R1, 1;
		LDR R0, R1, 0;
		BRz DONE
		LD  R2, A;
		ADD R0, R0, R2
		BRn LOOP;
		LD  R2, Z;
		LDR R0, R1, 0;
		ADD R0, R0, R2
		BRp LOOP;
		LD  R2, L;
		LDR R0, R1, 0;
		ADD R0, R0, R2;
		STR R0, R1, 0;
		BR LOOP;

DONE	LD R0, ZERO
		LD R1, ONE
		LD R2, TWO
		RET


ZERO	.fill 0
ONE		.fill 0
TWO		.fill 0
A		.fill #-65
Z		.fill #-90
L		.fill #32
		; TODO you might need some labels here to hold temporary values

.end

