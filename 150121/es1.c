#include <s2argv.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Expected 1 parameter");
    return (EXIT_FAILURE);
  }

  // variable for read file
  FILE *stream;
  char *line = NULL;
  char **lines = NULL;
  size_t len = 0;
  ssize_t read;
  int i = 1;
  const char *pathname = argv[1];

  // variable for pipe
  int pipefd[2]; // pipefd[0] is set up for reading, pipefd[1] is set up for
                 // writing
  pid_t cpid;

  // open file
  stream = fopen(pathname, "r");
  if (stream == NULL)
    exit(EXIT_FAILURE);
  // read line of file
  while (((read = getline(&line, &len, stream)) != -1) & (i <= 2)) {
    printf("Retrieved line %d of length %zu :\n", i, read);
    printf("%s", line);
    lines = (char **)realloc(lines, i * sizeof(char *));
    lines[i - 1] = (char *)malloc(sizeof(line));
    strcpy(lines[i - 1], line);
    i++;
  }

  // start pipe
  if (pipe(pipefd) == -1) {
    perror("Pipe");
    return (EXIT_FAILURE);
  }
  cpid = fork();
  if (cpid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  if (cpid == 0) {
    close(pipefd[0]);
    dup2(pipefd[1], STDOUT_FILENO); // redirect STDOUT to write to fd[1]->fd[0]
    execsp(lines[0]);
    return (EXIT_FAILURE);

  } else {
    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);
    wait(NULL);
    execsp(lines[1]);
    return (EXIT_FAILURE);
  }
  free(line);
  fclose(stream);
  exit(EXIT_SUCCESS);
}
