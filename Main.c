#include"CmnInc.h"
#include"Pool_of_functions.h"/**/
/*clang202(argc, argv);/**/

/*
					ATTENTION!!! Remember about compiler mode
	"Solution Explorer -> ProjectName -> Properties -> Configuration properties ->
	C/C++ -> Disable Language Extension -> /NO or /Yes /Za(C source code with the ANSI compatibility option)"

	NOW is /NO
*/

/*					ATTENTION!!! Preprocessor Definitions
Configuration Properties -> C/C++ -> Preporocessor -> Preprocessor Definitions -> _CRT_NONSTDC_NO_WARNINGS
*/

/*
text seg. and data seg. are sharing one address space.
	doesn't work:
	char* c = (char*)main;
	c = 'Q';
*/

int
main(const int argc
	, const char* argv[]
	, const char* env[]
) {

#if 0
	int a;
	int* const p2a_1 = &a;
	const int* p2a_2 = &a;
	p2a_1 = (int*)0x00; *p2a_1 = 1;/*(int* const) - cann't change the value of the pointer */
	p2a_2 = (int*)0x00; *p2a_2 = 1;/*(const int*) - cann't change the value on this pointer */

	printf("%s", ptr2str(p2a_1));
#endif

	
#if 1

	/*EXTERN_PROG(AttemptFuncSwitch)/**/
	/*EXTERN_PROG(C_WIN32_multithread)/**/
	/*EXTERN_PROJ(ParseFormat);/**/
	/*EXTERN_PROJ(BitArr);/**/
	/*EXTERN_PROJ(u64_type);/**/
	/**/EXTERN_PROJ(FIFO_LL);/**/
	/*EXTERN_PROJ(f2hex);/**/

#endif/**/
	/*RoundRobinCounter(-70, 100);/**/
	
	system("pause");
	system("cls");
	return 0;
}