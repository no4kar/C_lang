/*#include<iostream>/**/
#include<signal.h>

#include"Pool_of_functions.h"

#define SETNAME(name,num) _##name##num

#define TEMPLATE(TEMP_NAME,TEMP_VARs) \
					typedef struct { TEMP_VARs } TEMP_NAME ;

#define m(var) m_##var
#define TEMPLATE_VARs_1 \
				int m(a);\
				double m(b);


struct BitField {
	/*bits fields must be 'integer' only and 'unsigned' for portability*/
	/*unnamed field('unsigned int : 3') does miss bits(shift) on a defined quantity*/
	unsigned int is_read : 1;
	unsigned int is_write : 1;
	unsigned int is_unbuf : 1;
	unsigned int is_eof : 1;
	unsigned int is_err : 1;
	unsigned int is_append : 1;

	/*a field defined as zero, used when need go to border of a word*/
	unsigned int : 0;
};


/*function that accepts an integer and a pointer to the function(that accepts an integer and return a void),
returning a pointer to the function that accepts an integer and return a void*/
void (*foo1(int, void(*foo)(int)))(int);

typedef void(*func_get_int_ret_void)(int);

func_get_int_ret_void
foo2(int
	, func_get_int_ret_void);

void asd(int);

int
ComplDef(
	int argc,
	char* argv[]
)
{
	foo1(1, asd);
	signal(SIGINT, asd);

	int SETNAME(var, 1) = 2;
	TEMPLATE(SomeClass, TEMPLATE_VARs_1);/*use template note from Cpp in C*/

	SomeClass a;
	a.m_a = 2;

	return 0;
}

/*in new Cstandard functions prohibit return a array or function, only pointers of them*/
char (*
	funcRetArrFuncRetChar()
	)(void)
{
	char funcRetChar(void);
	static char(*arrFuncRetChar[])(void) =/*array from three elements*/
	{ funcRetChar
		, funcRetChar
		, funcRetChar };

	static const struct {
		void(*p_asd)(int);
		void(*p_foo1)(int, void(*)(int));
		void(*p_foo2)(int, void(*)(int));
	} FuncTable = 
		{ asd
		,foo1
		,foo2 };

	FuncTable.p_foo1(1, FuncTable.p_asd);

	return arrFuncRetChar[2];/*a pointer on an auto variable cannot be returned, we use STATIC in a definition*/
}

char funcRetChar() { return 's'; }

void (*
	foo1(int a
		, void(*foo)(int))
	)(int)
{	return foo(a), foo; }

void (*
	foo2(int a
		, void(*foo)(int))
	)(int)
{	return foo(a), foo; }

void 
	asd(int a
	){}


void* Attempt1(void
) {
	static struct {
		void* head;
		void** to_tail;
	} arr[] = {
		{NULL, &arr[0].head }
		,{NULL, &arr[1].head}
	};
	return arr;
}