#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

void signalHandler(int signum) {
  printf("%d\n", signum);
  if (signum == 10) {
    printf("Received SIGUSR1!\n");
  }
}

int main(int argc, char const *argv[]) {
  if (argc < 3) {
    printf("Expected 2 parameters");
    return -1;
  }
  int len = 0;
  int n_sign = atoi(argv[1]);
  char *command;
  for (int x = 2; x < argc; x++)
    len += strlen(argv[x]) + 1;
  command = malloc(len);
  for (int x = 2; x < argc; x++)
    strcat(strcat(command, " "), argv[x]);

  printf("%d %s", n_sign, command);
  signal(SIGUSR1, signalHandler);

  while (1) {
    printf("My process ID : %d\n", getpid());
    sleep(1);
  }
  /*  sig.sa_handler = &signalHandler;
    sig.sa_flags = SA_RESTART;
    sigaction(n_sign, *sig, NULL);
  */
  return 0;
}
