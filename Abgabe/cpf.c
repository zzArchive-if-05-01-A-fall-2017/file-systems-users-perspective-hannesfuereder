#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>


void writeInFile(int f1,int f2);
int main(int argc, char* argv[]){	
	int file1 = open(argv[1], O_RDWR);
	int file2 =open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR |S_IWUSR);
	writeInFile(file1,file2);	
	return 0;
}
void writeInFile(int f1,int f2){
	char d[5000];
	int run = 1;
	while(run != 0){
		run = read(f1,d,5000);
		if(run==0)
		{
			close(f1);
			close(f2);
		}
		else
		{
			write(f2, d,run);		
		}
	}
}
