#pragma once
#include"CmnInc.h"

/*FIFO LinkedList*/
/*in #include<Windows.h> ARRAYSIZE(arr_name)*/
#define NEW(type_name)			(##type_name##*)malloc(sizeof(##type_name))
#define DELETE(ptr)				free((void*)(ptr))
#define TEMPLATE(TEMP_NAME,TEMP_VARs) \
					typedef struct { TEMP_VARs } TEMP_NAME ;
#define m(var) m_##var

#define STATIC static
/*NodeName - typename of the node struct, ImplTypeName - typename for impl's pointer*/
#define	FIFO_LL_StructDef(NodeName, ImplTypeName) \
	struct NodeName { \
		struct NodeName* m(next); \
		 struct ImplTypeName* m(impl); }; 