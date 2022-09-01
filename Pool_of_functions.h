#ifndef POOL_OF_FUNC_H_
#define POOL_OF_FUNC_H_

int
SetBits_2_6(
	int destination,
	int source,
	int index,
	int quantity
);

int
ReadLines(
	char* lineptr[],
	int nlines
);

void
WriteLines(
	char* lineptr[],
	int nlines
);

void
Qsort_of_Hoare(
	void* lineptr[],
	int left,
	int right,
	int(*Func_for_comp)(void*, void*)
);

void 
Swap(
	void* lineptr[],
	int i,
	int j
);

int
NumCmp(
	void* a,
	void* b
);

void
Echo_string(
	int argc,
	char** argv
);

int
GetWord(
	char*,
	int
);

int
GetPut(
	void
);

void
MinPrintF(
	char*,
	...
);

const char*
ptr2str(
	void* ptr
);

int
ArithmProgres(
	int a1
	, int an
);


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

int
C_lang_157(
	int argc,
	char* argv[]
);

int
C_lang_177(
	int argc,
	char* argv[]
);

int
clang202(
	int argc,
	char* argv[]
);

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#endif/*POOL_OF_FUNC_H_*/
