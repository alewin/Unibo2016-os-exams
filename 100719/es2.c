/*Scrivere un programma che crei un processo figlio. Il
processo genitore e il processo figlio devono essere collegati
 da due pipe, una per la comunicazione genitorefiglio,
una per la comunicazione figlio-genitore.

Il processo figlio deve rispedire al genitore ogni messaggio
ricevuto dalla pipe di input nell'altra (echo).

Il processo genitore deve per 100000 volte spedire
un messaggio di 40 byte al processo figlio e aspettare
da questo che il messaggio venga rispedito.
Scopo dell'esercizio e' di verficare quanto tempo viene impiegato
per il “ping” di 100000 messaggi su pipe*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include <signal.h>
#include <sys/time.h>

int main(int argc, char *arv[]) {
  int c2p[2], p2c[2];
  pid_t cpid;
  cpid = fork();
  if (cpid == -1) {
    printf("fork error");
    return 1;
  }
  if (cpid == 0) {
    // figlio deve rispondere al parent ogni messaggio di input
  } else {
    // padre deve inviare msg al figlio
    write(pipefd[0], )
  }
  return 0;
}
