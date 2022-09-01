#include"CmnInc.h"
/*#include"Pool_of_functions.h"/**/
/*clang202(argc, argv);/**/

void Foo1(int a) {}
void Foo2(char a) {}
static int Foo3(int i) { return i > 0 ? 3 : 0; }
int Foo4(int i) { return i > 0 ? 4 : 0; }
int Foo5(int i) { return i > 0 ? 5 : 0; }



typedef void(*viod_pfunc_viod)(void);
typedef int(*int_pfunc_int)(int);

static struct Switcher {
	const char* flag_;
	int(*handler_)(int);
} arrSw[] = {
	TOFLAG(Foo3), (void*)Foo1,/*WARNING!!! Reinterpret type*/
	TOFLAG(Foo4), Foo4,
	TOFLAG(Foo5), Foo5
};

int(*
	Switcher(
		unsigned int index)
	)(int) {

	static int(*arrOfFunc[])(int) = {
		Foo3,
		Foo4,
		Foo5 };

	if (index >= ARRAYSIZE(arrOfFunc)) {
		abort();
	}

	return arrOfFunc[index];
}

int_pfunc_int
Switcher2(
	struct Switcher arrSw[]
	, size_t arrSize
	, str_t flag
) {
	for (size_t i = 0; i < arrSize; i++)
	{
		if (!strcmp(flag, arrSw[i].flag_)) {
			return arrSw[i].handler_;
		}
	}

	return (int_pfunc_int)((void*)0);
}


/*
					ATTENTION!!! Remember about compiler mode
	"Solution Explorer -> ProjectName -> Properties -> Configuration properties ->
	C/C++ -> Disable Language Extension -> /NO or /Yes /Za(C source code with the ANSI compatibility option)"

	NOW is /NO
*/

int
AttemptFuncSwitch(
	int argc,
	char* argv[]
)
{
	Switcher(0)(3);
	arrSw[1].handler_('a');/**/

	system("pause");
	system("cls");
	return 0;
}