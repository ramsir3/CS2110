;===========================
; Name: YOUR NAME HERE
;===========================

.orig x3000
		LEA R0, HELLO;
		PUTS;
		LD R0, X;
		LD R1, Y;
		ADD R0, R0, R1;
		ADD R0, R0, #15;
		ADD R0, R0, #15;
		ADD R0, R0, #15;
		ADD R0, R0, #3;
		OUT;
		HALT;
HELLO	.stringz "The sum is: "
X		.fill 2
Y		.fill 3
.end

