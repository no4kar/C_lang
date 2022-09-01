#include"FIFO_as_LL.h"

#define NODE_IMPL NodeImpl
#define NODE Node
FIFO_LL_StructDef(NODE, NODE_IMPL)

struct NODE_IMPL {
	int a;
};

int
FIFO_LL(int argc
	, char* argv[]
) {
#define OPTION 2

#if OPTION == 1 /*struct LL_node;/**/
#define LL_MEMBERS(ll_name, ll_other_members) \
				struct ll_name* m(next);\
				ll_other_members
#define LL_OTHER_MEMBERs
#define LL_TYPE_NAME		LL_node
#define NEW_LLNODE		NEW(LL_TYPE_NAME)

	TEMPLATE(LL_TYPE_NAME, LL_MEMBERS(LL_TYPE_NAME, LL_OTHER_MEMBERs))
		LL_TYPE_NAME** tohead_ptr = NULL, * totail_ptr = NULL;

	LL_TYPE_NAME* ptr = NEW_LLNODE;

	DELETE(NEW(LL_TYPE_NAME));
#elif OPTION == 2

	struct NODE**
		AddNode(struct NODE** totail_ptr, struct NODE_IMPL* impl);
	struct NODE*
		EraseNode(struct NODE* head_ptr);
	struct NODE*
		EraseList(struct NODE* head_ptr);

#if 1
	/*in C we can't make defult initialized field of structs but can init arrays*/
	static struct {
		struct NODE* head_ptr;
		struct NODE** totail_ptr;
	} link_lst[] = {
		{ NULL, &link_lst[0].head_ptr }
	};

#define TOTAIL_PTR (link_lst[0].totail_ptr)/* "link_lst->head_ptr" you can use this notation*/
#define HEAD_PTR (link_lst[0].head_ptr)

#else
	static struct NODE* head_ptr = NULL;
	static struct NODE** totail_ptr = &head_ptr;/*when list is empty*/

#define TOTAIL_PTR totail_ptr
#define HEAD_PTR head_ptr

#endif

	size_t switch_on = 0x0A;/* '\n' simbol in ASCII table*/

	do
	{
		switch (switch_on)
		{
		case '+': {
			TOTAIL_PTR = AddNode(TOTAIL_PTR, NEW(struct NODE_IMPL));
			break; }

		case '-': {
		#define MINUS_CASE 1
		#if MINUS_CASE == 1
					/*head_ptr = EraseNode(head_ptr);*/
					if ((HEAD_PTR = EraseNode(HEAD_PTR)) == NULL)/*'(=)==' , without brackets '==' has highest priority*/
						TOTAIL_PTR = &HEAD_PTR;
		#elif MINUS_CASE == 2
					NULL == (head_ptr = EraseNode(head_ptr)) ? 0 : 1;
		#endif
			break; }
				/* in the input stream file (stdin) allways will be stay '\n' in the end after input*/
		case'\n': {
			fprintf(
				stdout
				, "\t%s\n\t%s\n\t%s\n"
				, "'+' - AddNode"
				, "'-' - EraseNode"
				, "'other' - EraseList and finish");
			break; }

		default: {
			if (EraseList(HEAD_PTR))
				fprintf(
					stderr
					, "%s\n %s in line: %d\n"
					, "List is not empty"
					, __FILE__
					, __LINE__)
				, abort();

			return 0; }
		}
	} while (switch_on = getchar());


#endif


	return -1;
}

/*struct NODE_IMPL must be dynamic alloc */
STATIC struct NODE**
	AddNode(
		struct NODE** totail_ptr
		, struct NODE_IMPL* impl
) {
	
	if (impl == NULL)assert(0), abort();
	
	/*static variables are init one time only, in compile time*/
	struct NODE* newNode = NEW(struct Node);
	if (newNode == NULL)
		fprintf(
			stderr
			, "%s\n%s in line: %d\n"
			, "'malloc' return NULL"
			, __FILE__
			, __LINE__)/*does almost same as "assert"*/
		, abort();

	newNode->m_next = *totail_ptr;
	*totail_ptr = newNode;
	totail_ptr = &newNode->m_next;
	newNode->m_impl = impl;

	return totail_ptr;
}

STATIC struct NODE*
	EraseNode(
		struct NODE* head_ptr
) {

	if (!head_ptr) {
		fprintf(stdout, "%s\n", "List is empty"); 
		return head_ptr;
	}
		
	struct NODE* next = head_ptr->m_next;/*accept pointer to the next node after a head node*/
	
	free((void*)head_ptr->m_impl);/*to erase implementation of the current node*/
	free((void*)head_ptr);

	return next;
}

struct NODE*
	EraseList(
		struct NODE* head_ptr
	) {

	while (head_ptr)
		head_ptr = EraseNode(head_ptr);
	return head_ptr;
}
