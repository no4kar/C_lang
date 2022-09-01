#include"CmnInc.h"

typedef struct { uint32_t _[2]; } u64_t;
typedef struct { uint32_t _[4]; } u128_t;

DEF_PROJ(u64_type) {
	/*define function addu()*/
	u64_t
		addu(
			u64_t* a
			, u64_t* b
		);

	u64_t a = { 0xFFFFFFFF,0xAAAAAAAA }
	, b = { 0xAAAAAAAA,0xFFFFFFFF };

	u64_t c = addu(&a, &b);


	char* ptr = (char*)(&a)->_[1];/* '*(target) = *(*(char**)&(source)->Buffer)++;' */

}

u64_t
addu(
	u64_t* a
	, u64_t* b
) {
	u64_t result;
	register uint16_t buf = 0;

	for (size_t i = 0; i < sizeof(u64_t); i++)
	{
		buf >>= BYTE_SHIFT;
		buf += (uint16_t)(BYTE_PTR(a)[i]);
		buf += (uint16_t)(BYTE_PTR(b)[i]);
		BYTE_PTR(&result)[i] = (uint8_t)(buf);
	}

	return result;
}