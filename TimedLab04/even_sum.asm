;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Your Name Here:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

        .orig x3000

        LD R6, STACK
        LD R0, N
        ADD R6, R6, -1
        STR R0, R6, 0
        JSR EVEN_SUM
        LDR R1, R6, 0
        ADD R6, R6, 2
        ST R1, ANSWER
        HALT

STACK   .fill xF000
N       .fill 4
ANSWER  .fill 999


EVEN_SUM	ADD R6, R6, -3;		space for RV, RA, OFP
			STR R7, R6, 1;		store RA
			STR R5, R6, 0;		store OFP
			ADD R5, R6, -1;		new FP
			ADD R6, R6, -1;		space for locals

			LDR R0, R5, 4;		load N into R0
			ADD R0, R0, -1;		N-1
			STR R0, R5, 0;		push N-1 onto stack

			LDR R0, R5, 4;		load N into R0
			BRp NEXT
			AND R0, R0, 0;		R0 = 0
			STR R0, R5, 3;		push 0 into RV
			ADD R6, R5, 3;		point R6 at RV
			LDR R7, R5, 2;		restore RA to RV
			LDR R5, R5, 1;		restore R5 to OFP
			RET

NEXT		LDR R0, R5, 0;		R0 = N-1
			ADD R6, R6, -1;
			STR R0, R6, 0;		push N-1 onto stack
			JSR EVEN_SUM;		EVEN_SUM(N-1)
			LDR R0, R6, 0;		R0 = EVEN_SUM(N-1)
			ADD R6, R6, 2;		move R6 back down, pop RV and N-1 off stack
			LDR R1, R5, 4;		R1 = N
			AND R4, R1, 1;		R4 = N & 1
			ADD R4, R4, -1;
			BRz RETURN;
			ADD R0, R1, R0;		R0 = N + R0

RETURN		STR R0, R5, 3;		RV = N + EVENSUM(N-1);
			ADD R6, R5, 3;		point R6 at RV
			LDR R7, R5, 2;		restore RA to RV
			LDR R5, R5, 1;		restore R5 to OFP
			RET
        .end
