#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#define BUFSIZE 1024
int totalbyte = 0;
void creatPIDfile() {
  char str[5];
  snprintf(str, 5, "%d", getpid());
  fopen(str, "w+");
}
void handler(int signum) {
  signal(SIGUSR1, handler);
  fprintf(stderr, "\n%ld Bytes copied until now\n", totalbyte);
}
int main(int argc, char const *argv[]) {
  creatPIDfile();
  signal(SIGUSR1, handler);
  int n, i;
  char buff[BUFSIZE];
  char loading[] = {'-', '\\', '|', '/'};
  while ((n = read(STDIN_FILENO, buff, BUFSIZE)) > 0) {
    totalbyte += write(STDOUT_FILENO, buff, n);
    fprintf(stderr, "\b", loading[i % 4]);
    (i == INT_MAX) ? (i = 0) : (i++);

    usleep(100000);
  }

  return 0;
}
