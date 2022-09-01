#pragma warning(disable : 4996)

#define MAX_NAME 20/*depend from system*/

#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<sys/stat.h>/*<sys/types.h> include in <sys/stat.h>*/
#include<io.h>/*old open,write and other*/
#include<stdlib.h>/*malloc,free*/

typedef struct {/*universal struct of a directory's element*/
	long index_node_;
	char name_[MAX_NAME];
} DirElement;

typedef struct {
	int fd_;
	DirElement d_;
} DIR;

DIR* openDir(const char* dir_name);
DirElement* readDir(DIR* p_dir);
void closeDir(DIR* p_dir);
void fSize(const char* file_name);
void dirWalk(const char* file_name, void(*p_func)(const char*));

int
C_lang_196(
	int argc,
	const char* argv[]
)
{
	if (argc == 1) {
		fSize(".");
	}
	else {
		while (--argc > 0) {
			fSize(*++argv);
		}
	}
	return 0;
}

void 
	fSize(
		const char* file_name
	) {
	/*static __inline int __CRTDECL 
	stat(
	char const* const _FileName,
	struct stat* const _Stat);*/

	struct stat stbuf;

	if (stat(file_name, &stbuf) == -1) {
		fprintf(stderr, 
			"void FSize(char* file_name): don't access to the file %s\n",
			file_name);
	}
	if ((stbuf.st_mode & S_IFMT) == S_IFDIR) {
		dirWalk(file_name,fSize);
		printf("%8ld%s\n",
			stbuf.st_size,
			file_name);
	}

	/*_open("CRT_OPEN.C", _O_RDONLY);*/
}

void 
	dirWalk(
	const char* dir_name,
	void(*func)(const char*)
	) {

	char name[MAX_NAME];
	DirElement* pde;
	DIR* pdir;

	if ((pdir = openDir(dir_name)) == NULL) {
		fprintf(stderr,
			"void dirWalk(const char*, void(*)(const char*)) : don't access to the directory %s\n",
			dir_name); 
		return;
	}

	while ((pde = readDir(pdir)) != NULL) {
		if ((strcmp(pde->name_, ".") == 0) || (strcmp(pde->name_, "...") == 0))
			continue;

		if ((strlen(dir_name) + strlen(pde->name_) + 2) > sizeof name) {
			fprintf(stderr,
				"void dirWalk(const char*, void(*)(const char*)) : too long names %s%s\n",
				dir_name,
				pde->name_);
		}
		else {
			sprintf_s(name, sizeof name, "%s\%s", dir_name, pde->name_);
			(*func)(name);
		}
	}
	closeDir(pdir);
}

DIR*
	openDir(const char* dir_name)
{ 
	int fd;
	struct stat stbuf;
	DIR* dp;
	if ((fd = _open(dir_name, O_RDONLY, 0)) == -1 ||
		fstat(fd, &stbuf) == -1 ||
		(stbuf.st_mode & S_IFMT) != S_IFDIR ||
		(dp = (DIR*)malloc(sizeof(DIR))) == NULL)
		return NULL;
	dp->fd_ = fd;
	return dp;
}

void
	closeDir(DIR* dp)
{ 
	if (dp) {
		_close(dp->fd_);
		free(dp);
	}
}

DirElement*
	readDir(DIR* dp)
{ 
#define DIRSIZ 14

	struct direct {/* структура каталога на данной системе */
		ino_t d_ino;
		char d_name[DIRSIZ];
	} dirbuf;
	 static DirElement d; /* возвращает унифицированную структуру */ 

	 while (_read(dp->fd_, (char*)&dirbuf, sizeof(dirbuf)) == sizeof(dirbuf)) {
		 if (dirbuf.d_ino == 0) /* пустой элемент, не используется */   
			 continue;
		 d.index_node_ = dirbuf.d_ino;
		 strncpy(d.name_, dirbuf.d_name, DIRSIZ);  
		 d.name_[DIRSIZ] = '\0'; /* завершающий символ '\0' */  
		 return &d; 
	 } 
	 return NULL;
}