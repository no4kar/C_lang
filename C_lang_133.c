#include<stdio.h>

#include"Pool_of_functions.h"

#define MAXLINES 5000 /* максимальное число строк */ 
//#define MAXLEN 500
char* lineptr[MAXLINES]; /* указатели на строки */

int
CLang133(
	int argc,
	char* argv[]
)
{

	typedef int UsingType_;
	UsingType_ intArr[] = { -3,5,78,153,-7,20,32,-15,5 };

	const UsingType_ size = (sizeof intArr / sizeof intArr[0]);

	UsingType_* ptrArr[(sizeof intArr / sizeof intArr[0])];

	for (size_t i = 0; i < size; i++)
		ptrArr[i] = intArr + i;

	for (size_t i = 1; i < size; i++)
		NumCmp(ptrArr[i - 1], ptrArr[i]);

	Qsort_of_Hoare((void**)ptrArr, 0, size - 1, NumCmp);

	return 0;
}

void Qsort_of_Hoare_int(int*, int, int);

int
CLang133_2(
	int argc,
	char* argv[]
)
{
	int arr[] = { 3,25,1,16,-7,-7 };/**/
	
#define SIZE_ARR (sizeof arr / sizeof arr[0])

	Qsort_of_Hoare_int(arr, 0, SIZE_ARR - 1);

	int* p_low = &arr[0];
	int* p_high = &arr[SIZE_ARR];

	auto variable = p_high - p_low;

	int* p_middle = p_low + (p_high - p_low) / 2;

	*p_middle = 100;

	return 0;
}

void
Qsort_of_Hoare_int(
	int linePtr[],
	int left,
	int right
)
{
	void Swap_int(int*, int*);

	//#define OWN_	
#ifdef OWN_

#else

	if (left >= right)
		return;

#define ON_SCREEN
#ifdef ON_SCREEN
	void
		OnScreen(
			int linePtr[],
			int left,
			int right
		);

	OnScreen(linePtr, left, right);
	printf("\n");
#endif // ON_SCREEN


	Swap_int(&linePtr[left], &linePtr[(left + right) / 2]);
	int last = left;

	for (int i = left + 1; i <= right; i++)
		if (linePtr[i] < linePtr[left])
			Swap_int(&linePtr[++last], &linePtr[i]);

	Swap_int(&linePtr[left], &linePtr[last]);

#ifdef ON_SCREEN
	OnScreen(linePtr, left, right);
	printf("\n\n");
#endif // ON_SCREEN

	Qsort_of_Hoare_int(linePtr, left, last - 1);
	Qsort_of_Hoare_int(linePtr, last + 1, right);

#endif // !OWN_
}

void
Swap_int(
	int* i,
	int* j
)
{
	if (i == j)
		return;

	*i += *j;
	*j = *i - *j;
	*i -= *j;
}

void
OnScreen(
	int linePtr[],
	int left,
	int right
)
{
	for (size_t i = 0; i <= right; i++)
		if (i < left)
			printf("...\t");
		else
			printf("%d\t", linePtr[i]);
}
