#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <dirent.h> 
#include <stdio.h> 
#include <errno.h>
struct stat attributes;
void fileType();
void printAccess();
void printStuff();
void printDateStuff();

int main(int argc, char* argv[]) {
DIR *d;
struct dirent *dir;

if(argc == 2){
	d = opendir(argv[1]);
}

if(ENOENT == errno|| argc == 1)
{
	printf("File Not exists, use default \n");
	d = opendir(".");	
}	

while ((dir = readdir(d)) != NULL) {
	
		lstat(dir->d_name,&attributes);
		
		fileType();
		printAccess();
		printStuff();
		printf("%-10s",dir->d_name);
		printDateStuff();
		
	}
	closedir(d);
	printf("\n");
	return 0;	
}
void fileType() {
	
	mode_t mode = attributes.st_mode;
	if(S_ISBLK(mode) != 0)
		printf("b");
	else if(S_ISCHR(mode) != 0)
		printf("c");
	else if(S_ISDIR(mode) != 0)
		printf("d");
	else if(S_ISFIFO(mode) != 0)
		printf("f");
	else if(S_ISLNK(mode) != 0)
		printf("l");
	else if(S_ISREG(mode) != 0)
		printf("-" );
}
void printAccess(){
	printf( (S_ISDIR(attributes.st_mode)) ? "d" : "-");
	printf( (attributes.st_mode & S_IRUSR) ? "r" : "-");
	printf( (attributes.st_mode & S_IWUSR) ? "w" : "-");
	printf( (attributes.st_mode & S_IXUSR) ? "x" : "-");
	printf( (attributes.st_mode & S_IRGRP) ? "r" : "-");
	printf( (attributes.st_mode & S_IWGRP) ? "w" : "-");
	printf( (attributes.st_mode & S_IXGRP) ? "x" : "-");
	printf( (attributes.st_mode & S_IROTH) ? "r" :"-");
	printf( (attributes.st_mode & S_IWOTH) ? "w" : "-");
	printf( (attributes.st_mode & S_IXOTH) ? "x" : "-");
	printf(" ");
}
void printStuff(){
	printf("%-5u", attributes.st_uid);
	printf("%-5u", attributes.st_gid);
	printf("%-10ld", attributes.st_size);
	
}
void printDateStuff(){
	printf("%-20s",ctime(&attributes.st_mtime));
}
