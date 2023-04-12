#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <fcntl.h> 

int main(){
    int fd;
    char buff[100];
    // Reading from foo.txt
    fd = open("foo.txt", O_RDONLY);
    read(fd, buff, 13);
    printf("Contents of foo.txt is: %s\n", buff);

    // Writing contents of foo.txt to bar.txt
    fd = open("bar.txt", O_WRONLY | O_CREAT);
    write(fd, buff, 13);
    printf("Contents of foo.txt is copied to bar.txt\n");
    close(fd);

    return 0;
}
