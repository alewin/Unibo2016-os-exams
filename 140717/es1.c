#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

const char *get_filename_ext(const char *filename) {
  const char *dot = strrchr(filename, '.');
  if (!dot || dot == filename)
    return "";
  return dot + 1;
}
const char *remove_ext(const char *mystr) {
  char *retstr;
  char *lastdot;
  if (mystr == NULL)
    return NULL;
  if ((retstr = (char *)malloc(strlen(mystr) + 1)) == NULL)
    return NULL;
  strcpy(retstr, mystr);
  lastdot = strrchr(retstr, '.');
  if (lastdot != NULL)
    *lastdot = '\0';
  return retstr;
}
int get_files(char *pathname, char *ext, char ***files) {
  int i = 0;
  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir(pathname)) != NULL) {
    while ((ent = readdir(dir)) != NULL) {
      if (ent->d_type == DT_REG) {
        if (strcmp(get_filename_ext(ent->d_name), ext) == 0) {
          *files = (char **)realloc(*files, (i + 1) * sizeof(char *));
          (*files)[i] = (char *)malloc((strlen(ent->d_name)) + 1);
          strcpy((*files)[i], ent->d_name);
          i++;
        }
      }
    }
    closedir(dir);
  }
  return i;
}

void execute(char **argv) {
  pid_t pid;
  int status;

  if ((pid = fork()) < 0) { /* fork a child process           */
    printf("*** ERROR: forking child process failed\n");
    exit(1);
  } else if (pid == 0) {             /* for the child process:         */
    if (execvp(argv[0], argv) < 0) { /* execute the command  */
      printf("*** ERROR: exec failed\n");
      exit(1);
    }
  } else {                       /* for the parent:      */
    while (wait(&status) != pid) /* wait for completion  */
      ;
  }
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Expected 1 parameter");
    return -1;
  }
  char *pathname = argv[1];
  char **cfiles = NULL, **ofiles = NULL;
  int ic, io;
  char *command = "gcc";
  char *args[] = {"gcc", "-c", "es1.c", NULL};
  ic = get_files(pathname, "c", &cfiles);
  io = get_files(pathname, "o", &ofiles);
  printf("%d e %d\n", ic, io);

  for (int i = 0; i < ic; i++) {
    printf("%d\n", i);
    if (io != 0) {
      for (int j = 0; j < io; j++) {
        if (strncmp(cfiles[i], ofiles[j], strlen(cfiles[i]) - 2) == 0) {
          printf("esiste %s per il sorgente %s \n", ofiles[j], cfiles[i]);
          // execlp("gcc", command[0], command[1], cfiles[i], (char *)NULL);
        } else {
          printf("non esiste il file oggetto per il sorgente %s \n", cfiles[i]);
          // execlp("gcc", command[0], command[1], cfiles[i], (char *)NULL);
        }
      }
    } else {
      printf("non esiste nessun file oggetto genero %s \n", cfiles[i]);
      args[2] = cfiles[i];
      // execvp("gcc", args);
      execute(args);
    }
  }
  return 0;
}
