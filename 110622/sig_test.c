#define _POSIX_SOURCE


#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void measure_time(int sig) {
  printf("child [%d] received signal %d\n", getpid(), sig);
}

int main(int argc, char *argv[]) {
  int n_task = 4;

  pid_t pid;
  pid_t pid_array[n_task];

  for (int i = 0; i < n_task; i++) {
    pid = fork();

    if (pid < 0) {
      perror("fork");
      exit(1);
    }

    if (pid == 0) // child
    {
      printf("printed from child [%d]\n", getpid());
      signal(SIGUSR1, measure_time); // measure_time is a function
      sleep(5);

      exit(0);
    }

    // parent
    pid_array[i] = pid;
  }

  // This code is executed from parent only
  sleep(1);

  for (int i = 0; i < n_task; i++)
    kill(pid_array[i], SIGUSR1);

  for (int i = 0; i < n_task; i++)
    wait(NULL);

  return (0);
}
