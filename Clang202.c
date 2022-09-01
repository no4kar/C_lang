#include<stdlib.h>
#include<stdio.h>

#include"Pool_of_functions.h"

/*all machines have type who necessary align*/
/*this type can hold others types*/
typedef long Align;

typedef union header {
	struct {
		union header* p_next_;/*a pointer at the next free block*/
		unsigned size_;
	} block_;
	Align var_;/*forced block alignment*/
} Header;

static Header base;/*empty block(size zero) for begin with a pointer at a first free block*/
static Header* prev_succeed = NULL;/*block where a free space was found during the last search(previous succeed)*/

#define SIMULATION
#define ALL_MEMORY_SIZE 0x100
#define NALLOC 0x10

void* mAlloc(unsigned numBytes);
void freeMy(void* freeSpace);

int
clang202(
	int argc,
	char* argv[]
)
{
	void* test1;
	if ((test1 = mAlloc(10)) == NULL)
		fprintf(stderr, " test1 == NULL in \"int clang202( int argc, char* argv[])\"");
	
	freeMy(test1);

	return 0;
}

char* giveMemFromBuff(int numBytes) {
	static size_t iter = 0;
	static char memoryBuffer[ALL_MEMORY_SIZE] = { (char)0x0 };
	
	if ((iter + numBytes) >= ALL_MEMORY_SIZE)
		iter = 0;

	for (size_t i = 0; i < numBytes; i++)
		if (memoryBuffer[iter + i] == 'U')
			return 0;

	iter += numBytes;
	return &memoryBuffer[iter - numBytes];
}

void*
mAlloc(
	unsigned numBytes
)
{
	Header* p_inmd;/*a intermedia pointer*/
	Header* p_prev;/*at previous*/
	unsigned num_units;
	Header* moreCore(unsigned);

	num_units = (numBytes + sizeof(Header) - 1) / sizeof(Header) + 1;/*-1 +1 for arounding?*/
	
	if ((p_prev = prev_succeed) == NULL) {/*it's begin(a list of free space isn't exist)*/
		p_prev = base.block_.p_next_  = prev_succeed = &base;/*make loop*/
		base.block_.size_ = 0;
	}

	for (p_inmd = p_prev->block_.p_next_;;
		p_prev = p_inmd, p_inmd = p_inmd->block_.p_next_) {

		if (p_inmd->block_.size_ >= num_units) {
			if (p_inmd->block_.size_ == num_units) {
				p_prev->block_.p_next_ = p_inmd->block_.p_next_;
			}
			else {/*cut a tail*/
				p_inmd->block_.size_ -= num_units;
				/*make a new 'Header' who will be have a size of allocated space*/
				p_inmd += p_inmd->block_.size_;
				p_inmd->block_.size_ = num_units;
			}
			prev_succeed = p_prev;
			return (void*)(p_inmd + 1);
		}

		if (p_inmd == prev_succeed)
			if ((p_inmd = moreCore(num_units)) == NULL)
				return NULL;
	}

}


Header* moreCore(unsigned numUnits)
{
	char* p_ch;/*for pointer form "char* sbrk(int)"*/
	Header* p_head;

#ifdef _UNIX
	char* sbrk(int);/*system call in UNIX(return -1 if dont have free memory)*/
#endif

#ifdef SIMULATION
	char* giveMemFromBuff(int);
#endif

	void freeMy(void*);

	if (numUnits < NALLOC)
		numUnits = NALLOC;

	p_ch =
#if defined(_UNIX)
		sbrk(
#elif defined(SIMULATION)
		giveMemFromBuff(
#endif 		
			numUnits * sizeof(Header));

	if (p_ch == (char*)-1)
		return NULL;

	p_head = (Header*)p_ch;
	p_head->block_.size_ = numUnits;

	freeMy((void*)(p_head + 1));/*dont tach header*/
	return prev_succeed;
}

void freeMy(void* freeSpace) {
	Header* p_head_free = (Header*)freeSpace - 1;
	Header* ptr;
	/*first: conversion a "free_space" to "Header*" type*/
	/*second: subtract for find a header of the free space*/

	for (ptr = prev_succeed;
		!(ptr < p_head_free && p_head_free < ptr->block_.p_next_);
		ptr = ptr->block_.p_next_) {
		if (ptr >= ptr->block_.p_next_ && (p_head_free < ptr->block_.p_next_ || p_head_free > ptr))
			break;/*free block is outside the list*/

		if (ptr == p_head_free)
			fprintf(stderr,
				"\"void freeMy(void*)\": can't be ptr == p_head_free \n");
	}

	if ((p_head_free + p_head_free->block_.size_) == ptr->block_.p_next_) {/*merger with higher neighbor*/
		p_head_free->block_.size_ += ptr->block_.p_next_->block_.size_;
		p_head_free->block_.p_next_ = ptr->block_.p_next_->block_.p_next_;
		ptr->block_.p_next_ = p_head_free;
	}
	else {
		p_head_free->block_.p_next_ = ptr->block_.p_next_;
		ptr->block_.p_next_ = p_head_free;
	}

	if ((ptr + ptr->block_.size_) == p_head_free) {/*merger with lower neighbor*/
		ptr->block_.size_ += p_head_free->block_.size_;
	}
	else {
		p_head_free->block_.p_next_ = ptr->block_.p_next_;
		ptr->block_.p_next_ = p_head_free;
	}

	prev_succeed = ptr;
}