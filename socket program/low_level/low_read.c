#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define BUF_SIZE 100
void error_handling(char *message);

int main(){
    int fd;
    char buf[BUF_SIZE];

    fd = open("data.txt", O_RDONLY);
    if(fd == -1)
        error_handling("open() error");
    printf("file descriptor is %d\n", fd);

    if(read(fd, buf, sizeof(buf)) == -1)
        error_handling("read() error");
    close(fd);
    
    return 0;
}

void error_handling(char *message){
    fputs(message, stderr);
    fputs("\n", stderr);
    exit(1);
}