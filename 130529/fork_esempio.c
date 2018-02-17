#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
  printf("--beginning of program\n");

  int counter = 0;
  pid_t pid = fork();

  if (pid == 0) {
    // child process
    for (int i = 0; i < 5; ++i)
      printf("child process: counter=%d\n", ++counter);
  } else if (pid > 0) {
    // parent process
    for (int j = 0; j < 5; ++j)
      printf("parent process: counter=%d\n", ++counter);
  }
  printf("--end of program--\n");

  return 0;
}
