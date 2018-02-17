#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  DIR *d;
  struct dirent *dir;
  struct stat sb;
  int pid;

  d = opendir(".");
  if (d != NULL) {
    while ((dir = readdir(d)) != NULL) {
      stat(dir->d_name, &sb);
      if (((sb.st_mode & S_IFMT) == S_IFREG) && (sb.st_mode & S_IXUSR)) {
        printf("%d\n", dir->d_name);
        /*if ((pid = fork()) == -1) {
          printf("fork fail\n");
          return -1;
        }
        if (pid == 0) { // child
          execv(dir->d_name, argv + 1);
          perror(dir->d_name);
          return -1;
        }
        */
      }
    }
  }
  closedir(d);
  return 0;
}
