#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(){
  pid_t pid;
  pid = fork();

  printf("Hello World\n");

  if (pid == 0){
    printf("This is the child process\n");
    printf("Child Process ID: %d\n", getpid());
    printf("Parent Process ID: %d\n", getppid());
  } else if (pid > 0){
    printf("This is the parent process\n");
    printf("Parent Process ID: %d\n", getpid());
    printf("Child Process ID: %d\n", pid);
  } else {
    printf("Fork Failed");
  }
  
  printf("\n");

  return 0;
}
