#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void walker(char *basedir){
	DIR *dir;
	struct dirent *dEnt;

	dir = opendir(basedir);

	if(dir != NULL){
		printf("\nCurrent Directory: \"%s\"\n", basedir);

		while((dEnt = readdir(dir)) != NULL){
			char entpath[] = "";
			strcat(entpath, basedir);
			strcat(entpath, "\\");
			strcat(entpath, dEnt->d_name);

			if(isDir(entpath)){
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
	stat(file_path, &s);
	return S_ISDIR(s.st_mode);
}

int main(int argc, char *argv[])
{
	char basedir[strlen(argv[1])];
	strcpy(basedir,argv[1]);
	walker(basedir);

	return 0;
}
