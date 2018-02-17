#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  pid_t cpid;
  int pipefd[2];

  struct timeval stop, start, tval_result;

  if (pipe(pipefd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }
  cpid = fork();
  if (cpid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  if (cpid == 0) {
    /*rispondere al parent per ogni msg ricevuto*/
    char buf;
    close(pipefd[1]); /* Close unused write end */
    while (read(pipefd[0], &buf, 1) > 0)
      write(STDOUT_FILENO, &buf, 1);
    write(STDOUT_FILENO, "\n", 1);
    close(pipefd[0]);

    gettimeofday(&stop, NULL);
    timersub(&start, &stop, &tval_result);

    printf("Ping: %ld sec and %06ld usec\n", (long int)tval_result.tv_sec,
           (long int)tval_result.tv_usec);

    printf("hello from the child ");
    _exit(EXIT_SUCCESS);
  } else {
    /*soedire 100000 volte un msg di 40byte
    al figlio e aspetare che msg venga spedito*/
    close(pipefd[0]);           /* Close unused read end */
    gettimeofday(&start, NULL); // begin message passing time

    // do stuff
    sleep(5);

    write(pipefd[1], argv[1], strlen(argv[1]));
    // for i 100000
    close(pipefd[1]); /* Reader will see EOF */
    wait(NULL);       /* Wait for child */
    printf("hello from the parent\n");
    exit(EXIT_SUCCESS);
  }

  return 0;
}
