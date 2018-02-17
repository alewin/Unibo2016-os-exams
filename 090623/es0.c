#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    printf("NO");
    return (-1);
  }
  const char *pathname = argv[1];
  FILE *fd;
  size_t size;
  char *buf;
  int ris = 0;
  if ((fd = fopen(pathname, "r")) != NULL) {
    while ((ris = getline(&buf, &size, fd) > 0)) {
      int i = 0;
      if (buf[0] != '#') {
        while (buf[i] != EOF) {
          printf("%c\n", buf[i]);
          if (buf[i] == ' ') {
            printf("%c trovato", buf[i]);
          }

          i++;
        }
        char *args[] = {"ls", "-l", (char *)0};
        execvp("ls", args);
      }
    }
  }

  return 0;
}
