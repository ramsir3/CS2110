;;===============================
;;Name: Ramamurthy Siripuram
;;===============================

.orig x3000
        LEA R0, START_MSG_1;
        PUTS;
        LD R0, N;
        ADD R0, R0, #-1;        Subtract 1 to get proper index
        LEA R1, GRAMMAR_ARR;    Get address for the numbers array
        ADD R0, R0, R1;         Offset by starting index
        LDR R0, R0, 0;
        PUTS;
        LEA R0, START_MSG_2;
        PUTS;
        AND R1, R1, 0;          Clear reg 1 it will be the counter
        LD R2, N;               Load number to check if loop is done
        NOT R2, R2;
        ADD R2, R2, #1;         Negate reg 2
LOOP    LEA R3, MESSAGE_ARR;    Get address for the message array
        ADD R0, R1, R3;         Offset by starting index
        LDR R0, R0, 0;
        PUTS;
        ADD R1, R1, #1;         Increment counter
        ADD R5, R1, R2;         Subtract counter by number
        BRn LOOP;               If counter < number continue
        HALT;

N .fill 1

START_MSG_1
    .stringz "The "

START_MSG_2
    .stringz " reasons I love CS 2110 so far:\n"

GRAMMAR_ARR
    .fill GRAM01
    .fill GRAM02
    .fill GRAM03
    .fill GRAM04
    .fill GRAM05
    .fill GRAM06
    .fill GRAM07
    .fill GRAM08
    .fill GRAM09
    .fill GRAM10

MESSAGE_ARR
    .fill MESS01
    .fill MESS02
    .fill MESS03
    .fill MESS04
    .fill MESS05
    .fill MESS06
    .fill MESS07
    .fill MESS08
    .fill MESS09
    .fill MESS10
.end

.orig x5000
GRAM01
    .stringz "one"
GRAM02
    .stringz "two"
GRAM03
    .stringz "three"
GRAM04
    .stringz "four"
GRAM05
    .stringz "five"
GRAM06
    .stringz "six"
GRAM07
    .stringz "seven"
GRAM08
    .stringz "eight"
GRAM09
    .stringz "nine"
GRAM10
    .stringz "ten"
MESS01
    .stringz "One, I made this cool program in assembly!\n"
MESS02
    .stringz "Two, the TAs are super helpful!\n"
MESS03
    .stringz "Three, Professor Leahy is an entertaining lecturer!\n"
MESS04
    .stringz "Four, I now know how to prevent electrical fires!\n"
MESS05
    .stringz "Five, bitwise operations are really useful!\n"
MESS06
    .stringz "Six, I can make state machines now!\n"
MESS07
    .stringz "Seven, memory is no longer a mystery!\n"
MESS08
    .stringz "Eight, I understand how a basic computer works now!\n"
MESS09
    .stringz "Nine, I feel more confident with binary and hex!\n"
MESS10
    .stringz "Ten, I'm looking forward to learning C!\n"
.end
