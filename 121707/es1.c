#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUF_SIZE 20

int main(int argc, char **argv) {
  chdir(".");
  int ncopie, i, ris;
  char command[BUF_SIZE];
  if (argc < 3) {
    printf("inserisci due o più argomenti (ncopie, command)\n");
    exit(1);
  }
  ncopie = atoi(argv[1]);
  strcpy(command, argv[2]);
  for (i = 0; i < ncopie; i++) {
    if (fork()) { // processo padre
    } else {
      char *env_el;
      env_el = malloc(BUF_SIZE);
      sprintf(env_el, "NCOPIA=%d", i);
      // asprintf
      // devo aggiungerci in fondo lo zero terminatore
      char *newenviron[] = {env_el, (char *)0};
      // argv+2 sono gli argomenti, ovvero tutti gli argomenti passati dopo il
      // secondo
      ris = execve(argv[2], argv + 2, newenviron);
      if (ris == -1) {
        perror("execve");
        exit(1);
      }
    }
  }
  for (i = 0; i < ncopie; i++)
    wait(NULL);
  return 1;
}
