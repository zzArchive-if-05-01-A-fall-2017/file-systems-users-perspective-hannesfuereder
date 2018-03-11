#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

struct stat attributes;
void fileType();
void printAccess();
void printStuff();
void printDateStuff();

int main(int argc, char* argv[]) {
	if(argc != 2){
		printf("INPUT ERROR\n");
		
	}
	else{	
		lstat(argv[1],&attributes);
		printf("%-20s: %s\n","Filename: ",argv[1]);
		fileType();
		printAccess();
		printStuff();
		printDateStuff();
	}
	return 0;	
}
void fileType() {
	char data[255];
	mode_t mode = attributes.st_mode;
	if(S_ISBLK(mode) != 0)
		strcpy(data,"Block special File");
	else if(S_ISCHR(mode) != 0)
		strcpy(data,"character special file\n");
	else if(S_ISDIR(mode) != 0)
		strcpy(data,"directorie\n");
	else if(S_ISFIFO(mode) != 0)
		strcpy(data,"Pipe and FIFO special file\n");
	else if(S_ISLNK(mode) != 0)
		strcpy(data,"Symbolic link\n");
	else if(S_ISREG(mode) != 0)
		strcpy(data,"regular file" );
	else
		strcpy(data,"idk\n" );

	printf("%-20s: %s\n","File type : ",data);

}
void printAccess(){
	printf("%-20s: ", "Access privileges");
	printf((S_ISDIR(attributes.st_mode)) ? "d" : "-");
	printf((attributes.st_mode & S_IRUSR) ? "r" : "-");
	printf((attributes.st_mode & S_IWUSR) ? "w" : "-");
	printf((attributes.st_mode & S_IXUSR) ? "x" : "-");
	printf((attributes.st_mode & S_IRGRP) ? "r" : "-");
	printf((attributes.st_mode & S_IWGRP) ? "w" : "-");
	printf((attributes.st_mode & S_IXGRP) ? "x" : "-");
	printf((attributes.st_mode & S_IROTH) ? "r" : "-");
	printf((attributes.st_mode & S_IWOTH) ? "w" : "-");
	printf((attributes.st_mode & S_IXOTH) ? "x" : "-");
	printf("\n");
}
void printStuff(){
	printf("%-20s: %ld\n", "inode-Number ", attributes.st_ino);
	printf("%-20s: %ld\n", "Device numbers ",attributes.st_rdev);
	printf("%-20s: %ld\n", "Links count ", attributes.st_nlink);
	printf("%-20s: %u\n", "UID ", attributes.st_uid);
	printf("%-20s: %u\n", "GID ", attributes.st_gid);
	printf("%-20s: %ld\n", "File Size in bytes", attributes.st_size);
}
void printDateStuff(){
	printf("%-20s: %s", "Last access",ctime(&attributes.st_atime));
	printf("%-20s: %s", "Last modification",ctime(&attributes.st_mtime));
	printf("%-20s: %s", "Last inode change",ctime(&attributes.st_ctime));
}
