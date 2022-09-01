#include<fcntl.h>

#define NULL 0
#define EOF (-1)
#define BUFSIZ 512
#define MAX_OPEN 20
#define RW_RW_RW 0666/*read and write perms for all*/

typedef struct _iobuf {
	int count;/*counter*/
	char* p_next;/*a pointer to the next char*/
	char* p_base;/*a pointer to the base of a buffer*/
	struct {
		/*bits fields must be 'integer' only and 'unsigned' for portability*/
		/*unnamed field('unsigned int : 3') does miss bits(shift) on a defined quantity*/
		unsigned int is_read : 1;
		unsigned int is_write : 1;
		unsigned int is_unbuf : 1;
		unsigned int is_eof : 1;
		unsigned int is_err : 1;
		unsigned int is_append : 1;


		/*a field defined as zero, used when need go to border of a word*/
		unsigned int : 0;
	} flag;
	int fd;/*a file's descriptor hold a value returned from system call*/
} FILE;

enum _flags {
	_READ = 01,/*file is open*/
	_WRITE = 02,/*file is writing*/
	_UNBUF = 04,/*file with out buffer*/
	_EOF = 010,/*file is open*/
	_ERR = 020,/*file with error*/
	_APPEND = 040/*file is opened with append to end*/
};

static FILE _iob[MAX_OPEN] = {
	{0, (char*)0, (char*)0, _READ, 0},/*stdin*/
	{0, (char*)0, (char*)0, _WRITE, 1},/*stdout*/
	{0, (char*)0, (char*)0, _WRITE | _UNBUF, 2}/*stderr*/
};

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

int _FillBuf(FILE*);
int _FlushBuff(int, FILE*);
FILE* FOpen(char*, char*);

#define feof(p) ((p)->flag.is_eof)
#define ferror(p) ((p)->flag.is_err)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->count >= 0 ? \
(unsigned char) *(p)->p_next++ : _FillBuf(p))
#define putc(x,p) (--(p)->count >= 0 ? \
(unsigned char) *(p)->p_next++ = (x) : _FlushBuff((x), p))

#define getchar() getc(stdin)
#define putchar(x) putc((x),stdin)

FILE*
	FOpen(
	char* name,
	char* mode
)
{
	FILE* fp = NULL;
	int fd;

	/*#undef _WIN32
*/
#ifndef _WIN32
#define _UNIX
#endif // !_WIN32

#ifdef _UNIX
	/*system calls*/
	extern int open(char*, int, int);
	extern int create(char*, int);
	extern long lseek(int, long, int);
	/*(fd, shift, from_where(0-begin,1-present pos.,2-end))*/

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;

	for (fp = _iob; fp < _iob + MAX_OPEN; fp++)
		if ((fp->flag.is_read | fp->flag.is_write) == 0)
			break;

	if (fp >= _iob + MAX_OPEN)
		return NULL;

	switch (*mode) {
	case 'r':
		if ((fd = open(name, O_RDONLY, 0)) == -1)
			fd = create(name, RW_RW_RW);
		fp->flag.is_read = 1;
		break;

	case 'w':
		fd = create(name, RW_RW_RW);
		fp->flag.is_write = 1;
		break;

	case 'a':
		if ((fd = open(name, O_RDONLY, 0)) == -1)
			fd = create(name, RW_RW_RW);
		lseek(fd, 0L, 2);
		fp->flag.is_append = 1;
		break;

	default:

		break;
	}

	if (fd == -1)
		return NULL;

	fp->fd = fd;
	fp->count = 0;
	fp->p_base = NULL;

#elif (_WIN32 || _WIN64)

#endif // _UNIX ^ (_WIN32 || _WIN64)

	return fp;
}

int
_FillBuf(
	FILE* fp
)
{
	int bufsize;

	/*#undef _WIN32
*/
#ifndef _WIN32
#define _UNIX
#endif // !_WIN32

#ifdef _UNIX
	extern void* malloc(int);

	/*system calls*/
	extern int read(int, char*, int);

	if (!fp->flag.is_read || fp->flag.is_eof || fp->flag.is_err)
		return EOF;

	bufsize = fp->flag.is_unbuf ? 1 : BUFSIZ;

	if (fp->p_base == NULL)
		if ((fp->p_base = (char*)malloc(bufsize)) == NULL)
			return EOF;

	fp->p_next = fp->p_base;
	fp->count = read(fp->fd, fp->p_base, bufsize);

	/*error check*/
	if (--fp->count < 0) {
		if (fp->count == -1)
			fp->flag.is_eof = 1;
		else
			fp->flag.is_err = 1;
		fp->count = 0;
		return EOF;
	}
#elif (_WIN32 || _WIN64)

#endif // _UNIX ^ (_WIN32 || _WIN64)

	return *fp->p_next++;
}