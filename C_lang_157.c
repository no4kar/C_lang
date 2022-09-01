#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#include"Pool_of_functions.h"

#define HASHSIZE 100

static struct ListNode {
	struct ListNode* next = NULL;
	char* name;
	char* definition;
} * hashTable[HASHSIZE];

struct ListNode*
	Define(/*install*/
		char* name,
		char* definition
	);

int
UnDef(
	char* name
);

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

int
C_lang_157(
	int argc,
	char* argv[]
)
{
#define MAX_WORD_SIZE 100
	char word[MAX_WORD_SIZE];
	char nextWord[MAX_WORD_SIZE];

	while (GetWord(word, MAX_WORD_SIZE) != EOF) {
		if (!strcmp("define", word)) {
			if (GetWord(word, MAX_WORD_SIZE) == EOF ||
				GetWord(nextWord, MAX_WORD_SIZE) == EOF ||
				*word == '\0')
				printf("ERROR in determining 'DeFine'\n");

			Define(word, nextWord);
		}
		else if (!strcmp("undef", word)) {
			if (GetWord(word, MAX_WORD_SIZE) == EOF ||
				*word == '\0')
				printf("ERROR in determining 'UnDef'\n");
			
			UnDef(word);
		}
	}

	return 0;
}

/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

unsigned	
	HashCodeGet(
		char* str
	)
{
	unsigned hashVal;
	
	for (hashVal = 0; *str != '\0'; str++)
		hashVal += *str;
	return hashVal % HASHSIZE;
}

struct ListNode*
	LookUp(
		char* str
	)
{
	struct ListNode* p_ln;

	for (p_ln = hashTable[HashCodeGet(str)];
		p_ln != NULL;
		p_ln = p_ln->next)
		if (!strcmp(p_ln->name, str))
			return p_ln;
	
	return NULL;
}

struct ListNode*
	Define(/*install*/
		char* name,
		char* definition
	)
{
	struct ListNode* p_ln;
	unsigned hashVal;

	if ((p_ln = LookUp(name)) == NULL) {/*don't exist*/
		p_ln = (struct ListNode*)malloc(sizeof(*p_ln));
		if (p_ln == NULL ||
			(p_ln->definition = _strdup(definition)) == NULL ||
			(p_ln->name = _strdup(name)) == NULL)
			return NULL;
		hashVal = HashCodeGet(name);
		p_ln->next = hashTable[hashVal];/*assign a pointer on a first node to new node*/
		hashTable[hashVal] = p_ln;/*assign a pointer on a new node to hash table*/
	}
	else {/*exist*/
		free((void*)p_ln->definition);
		if((p_ln->definition = _strdup(definition)) == NULL)
			return NULL;
	}
	
	return p_ln;
}

int	
	UnDef(
		char* name
	)
{
	struct ListNode* p_ln;
	struct ListNode* p_ln_previous;
	
	if ((p_ln = LookUp(name)) != NULL) {/*exist*/
			/*find a pointer to previous node*/

		for (
			p_ln_previous = hashTable[HashCodeGet(name)];
			p_ln_previous != p_ln && p_ln_previous->next != p_ln;
			p_ln_previous++);

		p_ln_previous = p_ln->next;
		free((void*)p_ln);

		return 1;
	}

	return NULL;
}