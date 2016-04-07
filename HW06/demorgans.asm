;;===============================
;;Name: Ramamurthy Siripuram
;;===============================

.orig x3000

AND R0, R0, 0; Clear reg 0
AND R1, R1, 0; Clear reg 1
AND R2, R2, 0; Clear reg 2
LD R0, A
LD R1, B
NOT R0, R0; ~A
NOT R1, R1; ~B
AND R2, R0, R1; ~A & ~B
NOT R2, R2; ~(~A & ~B)
ST R2, ANSWER;
HALT
	
A       .fill 6
B       .fill 13
ANSWER  .fill 0		; This answer should contain A | B when finished.
.end
