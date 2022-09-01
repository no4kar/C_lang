#include"ParseFormat.h"

DEF_PROJ(ParseFormat) {
	const char* str = "-1248768.12638";
	static char str_new[32] = { 0 };

	static const char*
		Double2Fmt(char* _ans
			, const char* _fmt
			, const char* _source);

	fprintf(stdout, "%s\n"
		, Double2Fmt(str_new, "%.3f", str));

	return 0;
}

static const char*
Double2Fmt(char* _ans
	, const char* _fmt
	, const char* _source
) {
	double temp_flt;
	/*assert(expression) is a macro with double negation"!!" and logic-OR"||". If first expression return TRUE next "||" expressions will not be executed.*/
	assert(sscanf(_source, "%lf", &temp_flt) != EOF);
	assert(sprintf(_ans, _fmt, temp_flt) != EOF);

	/*try 'double atof(char const* _String)'*/

	return (const char*)_ans;
}