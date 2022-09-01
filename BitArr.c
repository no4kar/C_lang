#include"CmnInc.h"

/*#define BITARR_SIZE(bit_arr) (_ARRAYSIZE(bit_arr) * 8)/**/
#define BITARR_SIZE(bit_arr) (sizeof(bit_arr) * 8)
#define BITARR_TYPE uint8_t
#define BITARR_OFFSET (sizeof(BITARR_TYPE) << 3) /* x<<3 same x*(2^3) */

DEF_PROJ(BitArr) {
	static BITARR_TYPE bitArr[] = {
	0x1f,0xf5,0x7a,0xcd};
	uint8_t GetBitFromArr(char bitArr[], size_t ind);

	for (size_t i = 0; i < BITARR_SIZE(bitArr); i++)
	{
		printf("\tIndex %d value %d\n", i, GetBitFromArr(bitArr, i));
	}

	return 0;
}

uint8_t
GetBitFromArr(
	char bitArr[]
	, size_t ind
) {
	return ((bitArr[(ind / BITARR_OFFSET)]) >> (ind % BITARR_OFFSET)) & (BITARR_TYPE)1;
}