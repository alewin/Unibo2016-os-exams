#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

off_t fsize(const char *filename) {
  struct stat st;
  if (stat(filename, &st) == 0)
    return st.st_size;
  return -1;
}

char *readFileBytes(const char *name) {
  FILE *fl = fopen(name, "r");
  fseek(fl, 0, SEEK_END);
  long len = ftell(fl);
  char *ret = malloc(len);
  fseek(fl, 0, SEEK_SET);
  fread(ret, 1, len, fl);
  fclose(fl);
  return ret;
}

int is_regular_file(char *file) {
  struct stat p_stat;
  stat(file, &p_stat);
  return S_ISREG(p_stat.st_mode);
}
int main(int argc, char const *argv[]) {
  DIR *d;

  struct dirent *dir;
  if ((d = opendir(".")) != NULL) {
    while ((dir = readdir(d)) != NULL) {
      if (is_regular_file(dir->d_name)) {
        printf("%d %s %s\n", fsize(dir->d_name), dir->d_name,
               readFileBytes(dir->d_name));
      }
    }

    // write to file
    closedir(d);
  } else {
    printf("%s\n", "Opendir error");
  }

  return 0;
}
