#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Expected 2 parameters");
    return -1;
  }
  int n = atoi(argv[1]);
  for (int i = 0; i < n; i++) {
    int status;
    if (fork() == 0) {
      execvp(argv[2], argv + 2);
      exit(status);
    } else {
      wait(&status);
    }
  }
  return 0;
}
/*


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int n = atoi(argv[1]);
  int i;
  char *copia;
  for (i = 0; i < n; i++) {
    switch (fork()) {
    case 0:
      asprintf(&copia, "%d", i);
      setenv("NCOPIA", copia, 1);
      free(copia);
      execvp(argv[2], argv + 2);
      exit(1);
    case -1:
      exit(1);
    default:
      break;
    }
  }
  for (i = 0; i < n; i++) {
    int status;
    wait(&status);
  }
}
*/
