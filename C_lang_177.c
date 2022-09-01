#include<stdio.h>
#include<stdlib.h>

#include"Pool_of_functions.h"

int
C_lang_177(
	int argc,
	const char* argv[]
)
{
	FILE* fp;
	void
		FileCopy(
			FILE * ifp,
			FILE * ofp
		);

	if (argc == 1) {/*if dont have input files*/
		FileCopy(stdin, stdout);/*#define stdin  (__acrt_iob_func(0))*/
	}
	else {
		while (--argc > 0) {
			if (fopen_s(&fp, argv[argc], "r") != NULL) {
				fprintf(stderr, "\n%s can't open file %s\n", argv[0], argv[argc]);
				exit(1);
			}
			else {
				FileCopy(fp, stdout);
				fclose(fp);
			}
		}
		if (ferror(stdout)) {
			fprintf(stderr, "\n%s error of record in a stdout\n", argv[0]);
			exit(2);
		}

	}

	exit(0);
}

void
FileCopy(
	FILE* ifp,
	FILE* ofp
)
{
	int character;

	while ((character = getc(ifp)) != EOF)
		putc(character, ofp);
}