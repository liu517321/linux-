#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{

int fd;
size_t size;
fd=open("hello.txt",O_CREAT|O_RDWR,0777);
if(fd<0)
{
printf("open file hello.txt failure,fd=%d\n",fd);
return -1;
}

set_flag(fd,O_APPEND);
close(fd);
fd=open("hello.txt",O_RDWR|O_APPEND);
if(fd<0)
{
perror("open error");
exit(1);
}


while(1)
{
char ang[128]={0};
fgets(ang,128,stdin);
size=strlen(ang)*sizeof(char);
if(write(fd,ang,size)!=size)
{
perror("write error");
close(fd);
exit(1);
}

printf("\n");
int size1=0;
size1=lseek(fd,0L,SEEK_END);
lseek(fd,0L,SEEK_SET);
char buf[128]={0};
int tar=read(fd,(char*)buf,size1);
if(tar!=size1)
{
perror("read error");
close(fd);
exit(1);
}

printf("%s\n",buf);
}

close(fd);
return 0;
}

void set_flag(int fd,int flag)
{
int val;
val=fcntl(fd,F_GETFL);
if(val<0)
{
perror("fcntl error");
}

val|=flag;
if(fcntl(fd,F_SETFL,val)<0)
{
perror("fcntl error");
}

}
