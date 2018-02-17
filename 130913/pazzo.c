#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
/*
files[i] = malloc(255 * sizeof(char *));
for (int i = 0; i < 10; ++i)
  sub_str[i] = malloc(20 * sizeof(char));
return sub_str;
*/

int getfiles(const char *pathname, char **files) {
  DIR *d;
  struct dirent *dir;
  int count = 0;

  if ((d = opendir(pathname)) != NULL) {
    while ((dir = readdir(d)) != NULL) {
      if (dir->d_type == DT_REG) {
        files[count] = malloc(255 * sizeof(char));
        strcpy(files[count], dir->d_name);
        printf("String = %s,  Address = %u\n", files[count], files[count]);
        count++;
        files = realloc(files, sizeof(files[count - 1]) * count);
      }
    }
    closedir(d);
  } else {
    perror("");
    return EXIT_FAILURE;
  }
  return count;
}

int main(int argc, char const *argv[]) {
  const char *pathname = argv[1];
  char **files = malloc(1);
  int count_files = getfiles(pathname, files);
  printf("number of files: %d \n", count_files);

  for (int i = 0; i < count_files; i++)
    printf("files[%d] = %s", i, files[i]);
  return 0;
}
