#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    pid = fork();

    if (pid > 0) {
        printf("This is the parent process. Sleeping for 5 seconds.\n");
        sleep(5);
        printf("Parent process exiting.\n");
    }
    else if (pid == 0){
        printf("This is the child process.\n");
        printf("Child process exiting.\n");
    } else {
        printf("Fork failed.\n");
    }

    return 0;
}