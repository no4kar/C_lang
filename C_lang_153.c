#include<stdio.h>
#include<ctype.h> 
#include<string.h>
#include<stdlib.h>/*malloc() free()*/

#include"Pool_of_functions.h"
#define MAXWORD 100

struct TreeNode {
	char* word_;
	size_t count_;
	struct TreeNode* left_;
	struct TreeNode* right_;
};

struct TreeNode*
AddTree(
	struct TreeNode*,
	char*
);

void 
TreePrint(
	struct TreeNode*
);

struct TreeNode*
	TreeNodeAlloc(
		void
	);

char*
	StrDup(
		const char*
	);

/*extern int 
GetWord(
	char*,
	int
);*/
/* подсчет частоты встречаемости слов */ 

int
CLang153(
	int argc,
	char* argv[]
)
{ 
	struct TreeNode* root;
	char word[MAXWORD];
	root = NULL;

	while (GetWord(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			root = AddTree(root, word);
	
	TreePrint(root);
	
	return 0;
}

struct TreeNode*
AddTree(
	struct TreeNode* p_tn,
	char* word
)
{
	int cond;
	if (p_tn == NULL) {		/* слово встречается впервые */
		p_tn = TreeNodeAlloc(); /* создается новый узел */
		p_tn->word_ = StrDup(word);/*a standart func. in <string.h>*/
		p_tn->count_ = 1;
		p_tn->left_ = p_tn->right_ = NULL;
	}
	else if ((cond = strcmp(word, p_tn->word_)) == 0)
		p_tn->count_++; /* это слово уже встречалось */
	else if (cond < 0) /* меньше корня левого поддерева */
		p_tn->left_ = AddTree(p_tn->left_, word);
	else /* больше корня правого поддерева */
		p_tn->right_ = AddTree(p_tn->right_, word);
	
	return p_tn;
}

struct TreeNode*
TreeNodeAlloc(
	void
)
{
	return (struct TreeNode*) malloc(sizeof(struct TreeNode));
}

void
TreePrint(
	struct TreeNode* p_tn
) 
{
	if (p_tn != NULL) {
		TreePrint(p_tn->left_);
		printf("%4d %s\n", p_tn->count_, p_tn->word_);
		TreePrint(p_tn->right_);
	}
}

char*
StrDup(
	const char* ptr_source
)
{
	size_t lenght = strlen(ptr_source) + 1;/*'1' for '\0'*/
	char* ptr_dest = (char*)malloc(lenght);

	if (ptr_dest != NULL)
		strcpy_s(ptr_dest, lenght, ptr_source);

	return ptr_dest;
}