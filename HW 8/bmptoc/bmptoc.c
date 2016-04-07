// bmptoc.c
// Name: Ramamurthy Siripuram

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

// This is the array into which you will load the raw data from the file
// You don't have to use this array if you don't want to, but you will be responsible
// for any errors caused by erroneously using the stack or malloc if you do it a
// different way, incorrectly!
char data_arr[0x36 + 240 * 160 * 4];

int main(int argc, char *argv[]) {

	// 1. Make sure the user passed in the correct number of arguments
	if (argc > 2) {
		printf("More than 1 argument\n");
		return 0;
	}
	if (argc < 2) {
		printf("Less than 1 argument\n");
		return 0;
	}



	// 2. Open the file. If it doesn't exist, tell the user and then exit

	FILE *f = fopen(argv[1], "r");
	if(f == NULL) {
		printf("file does not exist\n");
		return 0;
	}


	// 3. Read the file into the buffer then close it when you are done
	char header[54];
	fread(header, 1, 54, f);

	// 4. Get the width and height of the image
	int *wp = (int*)(header + 0x12);
	int *hp = (int*)(header + 0x16);
	int w = *wp;
	int h = *hp;
	char pixels[w*h*4];
	fread(pixels, 1, w*h*4, f);
	fclose(f);
	// 5. Create header file, and write header contents. Close it

	int len = strlen(argv[1]);
	char hname[len];
	char *ptr = strcpy(hname, argv[1]);
	ptr += len-3;
	*ptr = 'h';
	ptr += 1;
	*ptr = '\0';

	char hvarname[len];
	char *ptr1 = strcpy(hvarname, argv[1]);

	ptr1 += len-4;
	*ptr1 = '\0';
	char hvarup[len-4];
	strcpy(hvarup, hvarname);
	for (int i = 0; i < len-4; i++) {
		hvarup[i] = toupper(hvarup[i]);
	}

	char hbody[100];
	int n = sprintf(hbody, "#define %s_WIDTH %d\n#define %s_HEIGHT %d\nconst unsigned short %s_data[%d];", hvarup, w, hvarup, h, hvarname, w*h);

	FILE *hf = fopen(hname, "w");
	fwrite(hbody, 1, n, hf);
	fclose(f);

	// 6. Create C file, and write pixel data. Close it
	char pname[len];
	char *pt = strcpy(pname, argv[1]);
	pt += len-3;
	*pt = 'c';
	pt += 1;
	*pt = '\0';

	FILE *pfc = fopen(pname, "w");
	fclose(pfc);
	FILE *pf = fopen(pname, "a");

	short out[w*h];
	int o = 0;

	for (int i = h-1; i >= 0; i--) {
		for (int j = 0; j < w; j++) {
			int c = i*w+j;
			out[o++] = (((short)(pixels[4*c] >> 3) << 10) & 0x7C00) | (((short)(pixels[4*c+1] >> 3) << 5) & 0x3E0) | ((short)(pixels[4*c+2] >> 3) & 0x1F);
		}
	}

	char dbuffer[100];
	int dn = sprintf(dbuffer, "const unsigned short %s_data[%d] = {", hvarname, w*h);
	fwrite(dbuffer, 1, dn, pf);
	for (int i = 0; i < w*h; i++)	{
		int x = 0;
		char e[8];
		if (i == w*h-1)	{
			x = sprintf(e, "0x%04X", out[i]);
		} else {
			x = sprintf(e, "0x%04X, ", out[i]);
		}
		if (i % 8 == 0)
		{
			fwrite("\n", 1, 1, pf);
		}
		fwrite(e, 1, x, pf);
	}
	char *fin = "};";
	fwrite(fin, 1, 2, pf);
	fclose(pf);

	return 0;
}

