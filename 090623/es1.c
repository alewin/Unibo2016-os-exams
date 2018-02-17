#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int c = 0;

void printc(int sign) { printf("%d\n", c); }
int main(int argc, char const *argv[]) {
  fprintf(stderr, "%s pid is: %d\n", argv[0], getpid());
  signal(SIGUSR1, printc);
  while (1) {
    sleep(1);
    c++;
  }
  return 0;
}
