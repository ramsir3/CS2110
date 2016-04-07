;===========================
; Name: YOUR NAME HERE
;===========================

.orig x3000
		AND R0, R0, 0;
		LD R1, ARRAY;
		LD R2, LENGTH;
		ADD R2, R2, R1;
		NOT R2, R2;
		ADD R2, R2, #1;
LOOP	LDR R3, R1, 0;
		ADD R0, R0, R3;
		ADD R1, R1, #1;
		ADD R4, R1, R2;
		BRn LOOP;
		ST R0, CHECKSUM;
		HALT;

LENGTH   .fill 3
ARRAY    .fill x5000
CHECKSUM .blkw 1
.end

.orig x5000
	.fill x1111
	.fill x2222
	.fill x3333
.end

