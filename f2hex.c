#include"CmnInc.h"
#include<fcntl.h>
#include<assert.h>

#define BUFFERSIZE 8
static DWORD g_BytesTransferred = 0;

DEF_PROJ(f2hex)
{

	FILE* fp;

	static void impl1(FILE*);
	static void impl2(FILE*);

	if (argc != 2)
		fprintf(stderr, "\n\tUsage Error: Incorrect number of arguments\n\t"), assert(0);
	
	if((fp = fopen(argv[1], "r"/* read binary/**/)) == NULL)
		fprintf(stderr, "\n\tTerminal failure: unable to open file \"%s\" for read\n\t", argv[1]), assert(0);

	fprintf(stdout, "\n\t%s\'%s\'\n", "f2hex - ", argv[1]);

#if 0

	if (fstat(fp, &sb) == -1) {
		perror("stat");
		exit(EXIT_FAILURE);
	}

	printf("Inode number: %lu\n", sb.st_ino);
	printf("User ID of owner: %u\n", sb.st_uid);
	printf("Group ID of owner: %u\n", sb.st_gid);
	printf("Total file size: %lu bytes\n", sb.st_size);
	printf("Last status change:       %s", ctime(&sb.st_ctime));
	printf("Last file access:         %s", ctime(&sb.st_atime));
	printf("Last file modification:   %s", ctime(&sb.st_mtime));

#endif/*Get file size with fstat()*/

#if 0

#if defined(_WIN32)
	__int64 FileSize(const wchar_t* name)
	{
		WIN32_FILE_ATTRIBUTE_DATA fad;
		if (!GetFileAttributesEx(name, GetFileExInfoStandard, &fad))
			return -1; // error condition, could call GetLastError to find out more
		LARGE_INTEGER size;
		size.HighPart = fad.nFileSizeHigh;
		size.LowPart = fad.nFileSizeLow;
		return size.QuadPart;
	}
#endif/*win32 api is defined*/

#endif/*Get file size with win_api*/

	impl2(fp);

	if(	fclose(fp) == EOF) fprintf(stderr, "\n\tUsage Error: Stream is failurely closed\n\n"), assert(0);

	return 0;


	return -1;
}

static void
impl1(
	FILE* fp
) {

}

static void
impl2(
	FILE* fp
) {
	uint8_t onscr[] = "00 00 00 00 00 00 00 00";
	uint8_t buffhex[(size_t)(ARRAYSIZE(onscr) / 3/*"00 "*/) * 2/*"00"*/ + 1/*'\0'*/] = { 0 };
	int line = 0, count = 0;
	/*BOOL loop = TRUE;/**/

	static size_t
		strhex1(FILE * fp, str_t buffstr, size_t size);

	while (TRUE) {

		count += strhex1(fp, buffhex, ARRAYSIZE(buffhex) - 1/*'\0'*/);
		sprintf(onscr, "%c%c %c%c %c%c %c%c %c%c %c%c %c%c %c%c"
			, buffhex[0], buffhex[1]
			, buffhex[2], buffhex[3]
			, buffhex[4], buffhex[5]
			, buffhex[6], buffhex[7]
			, buffhex[8], buffhex[9]
			, buffhex[10], buffhex[11]
			, buffhex[12], buffhex[13]
			, buffhex[14], buffhex[15]);

		if (fprintf(stdout, "\n\t0x%08x %s", line, onscr) != 36)/*36 char if ok*/
			break;

		count += strhex1(fp, buffhex, ARRAYSIZE(buffhex) - 1/*'\0'*/);
		sprintf(onscr, "%c%c %c%c %c%c %c%c %c%c %c%c %c%c %c%c"
			, buffhex[0], buffhex[1]
			, buffhex[2], buffhex[3]
			, buffhex[4], buffhex[5]
			, buffhex[6], buffhex[7]
			, buffhex[8], buffhex[9]
			, buffhex[10], buffhex[11]
			, buffhex[12], buffhex[13]
			, buffhex[14], buffhex[15]);

		if (fprintf(stdout, "\t%s", onscr) != 24)/*24 char if ok*/
			break;

		line += 16;/*16 hexs in line*/
	}

	fprintf(stdout, "\n\n\t\t%d Bytes\n\n\t", count);
}

static size_t
strhex(
	FILE* fp
	, uint16_t* buffhex
	, size_t size
) {
	uint8_t c;
	size_t count = 0;

	for (size_t i = 0; i < size; i++) {
		if ((c = fgetc(fp)) != EOF) {
			sprintf(&buffhex[i], "%02x", c);
			buffhex[i] = (buffhex[i] >> 8) | (buffhex[i] << 8);/*swap LSB and MSB*/
			count++;
		}
		else {
			buffhex[i] = (uint16_t)(('.' << 8) | '.');/*"" the notation always contains a \0 at the end*/
		}
	}

	return count;
}

static size_t
strhex1(
	FILE* fp
	, str_t buffstr
	, size_t size
) {
	uint32_t c, hex;
	size_t i = 0;

	for (; i < size; i += 2)
	{
		c = fgetc(fp);
		if (c == EOF) break;

		sprintf(&hex, "%02x", c);
		sprintf(&buffstr[i], "%c%c", hex, hex >> 8);
	}

	return (size_t)(i / 2);
}