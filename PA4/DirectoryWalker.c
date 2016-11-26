#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

#include "isdir.h"

#if !defined(S_ISDIR) && defined(S_IFDIR)
#define	S_ISDIR(m) (((m) & S_IFMT) == S_IFDIR)
#endif

void walker(char *basedir){
	DIR *dir;
	struct dirent *dEnt;

	dir = opendir(basedir);

	if(dir != NULL){
		while((dEnt = readdir(dir)) != NULL){
            if(strcmp(dEnt->d_name, ".") == 0 || strcmp(dEnt->d_name, "..") == 0)
			{
				continue;
			}

			char entpath[500] = "";
			strcat(entpath, basedir);
			strcat(entpath, "/");
			strcat(entpath, dEnt->d_name);

			if(isDir(entpath)==1){
				printf("\nDIR: %s\n", dEnt->d_name);
				walker(entpath);
			}
			else{
				printf("\nFILE: %s\n", dEnt->d_name);
			}
		}
		closedir(dir);
	}
}

int isDir(const char *file_path)
{
	struct stat s;
	if (NULL == file_path) { return 1; }
	stat(file_path, &s);
	return S_ISREG(s.st_mode)? 0 : 1;
}

int main(int argc, char *argv[])
{
	char basedir[strlen(argv[1])];
	strcpy(basedir,argv[1]);
	walker(basedir);

	return 0;
}
