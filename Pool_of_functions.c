#include<stdio.h>
#include<string.h>
#include<ctype.h>/*is a space, or a number, or else*/
#include<stdarg.h>/*different an argument list*/

/*#include<sys/types.h>
#include<sys/stat.h>*/
#include<fcntl.h>/*macro definitions for file menegment*/
/*#include<errno.h>*/

/*#include<fstream>/**/
#include<Windows.h>/**/


#include"Pool_of_functions.h"

#define BUF_SIZE 512 
char buf[BUF_SIZE]; /* buffer for ungetch */ 
static int bufp = 0; /* next free position in the buffer */

/*#define _ARRAYSIZE(arr) (sizeof(arr))/(sizeof((arr)[0]))/**/
#define SETNAME(name,num) _##name##num/*SETNAME(var,1) == _var1*/
#define DPRINT(expr) printf(#expr " = %g\n", expr)/*DPRINT(x/y) == printf("x/y = %g\n", x/y). '%g'- use the shortest representation: %e or %f(392.65)*/

int
GetCh( /*get characters from input stream(or from buffer)*/
	void
) {
	/*#define WITH_BUFFER*/
#ifndef WITH_BUFFER
	return (bufp > 0) ? buf[--bufp]: getchar();	/*#define getchar() getc(stdin)*/
#else

#if defined(_Linux)
	/*system call*/
	extern int/*number of successful read characters*/
		read(
			unsigned,/**/
			void*,/**/
			unsigned/**/
		);

	static char buffer[BUF_SIZE];
	static char* p_buffer = buffer;
	static int index = 0;

	if (index == 0) {
		index = read(0, p_buffer, BUF_SIZE);
		p_buffer = buffer;/*it's need because the pointer will be modificait in next line*/
	}
	return (--index >= 0) ? (unsigned int)*p_buffer++ : EOF;
#endif /*_Linux*/

#if defined(_WINDOWS_)
	
#endif /*_WINDOWS_*/
	
#endif
}

int
UnGetCh( /*return characters to input stream(mean to buffer)*/
	int c
) {
	if (bufp >= BUF_SIZE) {
		printf("ungetch: too much symbols in a buffer\n");
		return -1;
	}
	else {
		buf[bufp++] = c;
		return 0;
	}
}

int
GetWord(/* getword: принимает следующее слово или символ из ввода */
	char* word,
	int lim
) {
	int char_in_int;/*, GetCh(void);
	void UnGetCh(int);*/
	char* p_word = word;

	/*first simbol*/
	while (isspace(char_in_int = GetCh()));

	if (char_in_int != EOF)
		*p_word++ = char_in_int;

	/*else part of the string*/
	if (!isalpha(char_in_int)) {
		*p_word = '\0';
		return char_in_int;
	}

	for (; --lim > 0; p_word++)
		if (!isalnum(*p_word = GetCh())) {
			UnGetCh(*p_word);
			break;
		}
	*p_word = '\0';
	return word[0];
}

void
MinPrintF(
	char* fmt
	, ...
) {
	va_list ap;/*argument pointer*/
	char* p;
	char* sval;
	int ival;
	double dval;

	va_start(ap, fmt);/*ap points to the first argument*/

	for (p = fmt;
		*p;
		p++) {

		if (*p != '%') {
			putchar(*p);
			continue;
		}

		switch (*++p) {
		case 'd':
			ival = va_arg(ap, int);
			printf("%d", ival);
			break;

		case 'i':
			ival = va_arg(ap, int);
			printf("%i", ival);
			break;
		
		case 'o':
			ival = va_arg(ap, int);
			printf("%o", ival);
			break;
		
		case 'x':
			ival = va_arg(ap, int);
			printf("%x", ival);
			break;
		
		case 'u':
			ival = va_arg(ap, unsigned);
			printf("%u", ival);
			break;
		
		case 'c':
			break;
		
		case 's':
			for (sval = va_arg(ap, char*);
				*sval;
				sval++)
				putchar(*sval);
			break;
		case 'f':
			dval = va_arg(ap, double);
			printf("%f", dval);
			break;


		default:
			putchar(*p);
			break;
		}
	}


	va_end(ap);
}

int
GetPut(
	void
) {
	char c;
	while ((c = getchar()) != EOF)
		putchar(c);/*#define putchar() putc(stdout)*/
	return 0;
}

int
NumCmp(
	void* a
	, void* b
) {
	if (*(int*)a == *(int*)b)
		return  0;
	else
		return *(int*)a > * (int*)b ? 1 : -1;
}

void
Swap(
	void* lineptr[]
	, int i
	, int j
) {
	void* temp = lineptr[i];
	lineptr[i] = lineptr[j];
	lineptr[j] = temp;
}

void
Echo_string(
	int argc,
	char** argv
) {
	while (argc--)
		printf(argc ? "%s " : "%s", *++argv);

	printf("\n");
}

void
WriteLines(
	char* lineptr[]
	, int nlines
) {
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}

#ifdef MAXLEN
int
ReadLines(
	char* lineptr[],
	int maxlines
) {
	int len, nlines;
	char* p, line[MAXLEN];
	nlines = 0; while ((len = getline(line, MAXLEN)) > 0)
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len - 1] = '\0'; /* убираем символ \n */
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}
#endif // MAXLEN

void
Qsort_of_Hoare(
	void* linePtr[]
	, int left
	, int right
	, int(*Func_for_comp)(void*, void*)
) {
	extern void Swap(void**, int, int);

//#define OWN_	
#ifdef OWN_

#else

	if (left >= right)
		return;

	Swap(linePtr, left, (left + right) / 2);/*checking pivot item */
	int last = left;

	for (int i = left + 1; i <= right; i++)
		if ((*Func_for_comp)(linePtr[i], linePtr[left]) < 0)
			Swap(linePtr, ++last, i);
	/*now "last" is the last item in the arr that exactly less than the pivot item*/
	Swap(linePtr, left, last);
	Qsort_of_Hoare(linePtr, left, last - 1, Func_for_comp);
	Qsort_of_Hoare(linePtr, last + 1, right, Func_for_comp);

#endif // !OWN_
}

int
SetBits_2_6(
	int destination
	, int source
	, int index
	, int quantity
) {
	int cut = ~(~0 << quantity);
	int shift = index + 1 - quantity;
	
	source &= cut;/*OCT "0...", HEX "0x..." or "...h"*/
	source <<= shift;/*in C++ "<<=" that in C "<<"*/
	cut <<= shift;

	return (destination & ~cut) | source;
}

const char*
ptr2str(
	void* ptr
) {
	static char buff[3 +/*for '0x' and '\0'*/
#if defined(WIN32)
		(1 << 5)/*2^5*/
#else
		(1 << 6)/*2^6*/
#endif
	] = { 0 };

	return	((sprintf(buff, "0x%p", ptr)) != 0)
		? (const char*)buff
		: (const char*)(NULL);
}

void
RoundRobinCounter(
	int begin
	, size_t range
) {
#if 0
	HANDLE hConsole = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE
		, 0
		, NULL
		, CONSOLE_TEXTMODE_BUFFER
		, NULL);

	SetConsoleActiveScreenBuffer(hConsole);
#endif



	int limit = begin + range;

	for (size_t i = 0; ; i++)
	{
		fprintf(stdout
			, "'begin': %d\t'i': %d\t'limit': %d\t\t'counter': %d\n"
			, begin
			, i %= range/*its alive*/
			, limit
			, begin + i);

		system("cls");
	}
}

int
ArithmProgres(
	int a1
	, int an
) {/*SUMn=((A1+An)/2)*n*/
	return (a1 > an) ? ArithmProgres(an, a1) : ((a1 + an) * (an - a1 + 1)) / 2;
}