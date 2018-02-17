#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
/*

  char strings[5][20] = {"apples", "zpples", "grapes", "strawberries",
                         "bananas"};

  // sort the strings
  qsort(strings, 4, 20, (int (*)(const void *, const void *))strcmp);

  // display the strings in ascending lexicographic order
  for (int i = 0; i < 4; ++i)
    printf("%s\n", strings[i]);

*/
int main(int argc, char const *argv[]) {
  DIR *d;
  struct dirent *ent;
  if ((d = opendir("/proc")) != NULL) {
    while ((ent = readdir(d)) != NULL) {
      if ((ent->d_type == DT_DIR) &&
          (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)) {
        char path_link[PATH_MAX];
        sprintf(path_link, "/proc/%s/exe", ent->d_name);
        char path_proc[PATH_MAX];
        if (readlink(path_link, path_proc, sizeof(path_proc) - 1) < 0) {
          continue;
        } else
          printf("%s %s\n", ent->d_name, path_proc);
      }
    }
    closedir(d);
  } else {
    printf("Errore durante l'apertura della directory\n");
    return -1;
  }
  return 0;
}
