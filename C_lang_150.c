#include<stdio.h>
#include<string.h>
#include<ctype.h>

#include"Pool_of_functions.h"

struct Key {
	const char* word;
	int count;
} keytab[] = { 
	"auto", 0,
	"break", 0,
	"case", 0,
	"char", 0,
	"const", 0,
	"continue", 0,
	"default", 0,
	"unsigned", 0,
	"void", 0,
	"volatile", 0,
	"while", 0
};

struct Key* 
BinSearch(
	char*,
	struct Key*,
	int
);

#define NKEYS (sizeof keytab / sizeof keytab[0])
#define MAXWORD 1000

int 
CLang150(
	int argc,
	char* argv[]
)
{
	char word[MAXWORD];
	struct Key* p_Key;
	
	while (GetWord(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			if ((p_Key = BinSearch(word, keytab, NKEYS)) != NULL)/*increase count if is match*/
				p_Key->count++;

	for (p_Key = keytab; p_Key < keytab + NKEYS; p_Key++)/*print keyword, if a member count greater than zero*/
		if (p_Key->count > 0)
			printf("%4d %s\n", p_Key->count, p_Key->word);

	return 0;
}

/* binsearch: найти слово word в tab[0]...tab[n-1] */
struct Key* 
BinSearch(
	char* word,
	struct Key* tab,
	int n
)
{
	int cond;
	
	struct Key* low = &tab[0];
	struct Key* high = &tab[n];
	struct Key* mid;
	while (low < high)
	{
		mid = low + (high - low) / 2;
		if ((cond = strcmp(word, mid->word)) < 0)
			high = mid;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}
	return NULL;
}