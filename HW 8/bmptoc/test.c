#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

int main(int argc, char const *argv[])
{
	char arr[4] = {0xAA, 0xBB, 0x31, 0xCD};
	short out[1];
	out[0] = (((short)(arr[0] >> 3) << 10) & 0x7C00) | (((short)(arr[1] >> 3) << 5) & 0x3E0) | ((short)(arr[2] >> 3) & 0x1F);
	printf("%0x\n", out[0]);
	return 0;
}