#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

struct lista {
  struct lista *next;
  char *stringa;
};

void leggiArgomenti(char *comando) // prendo il comando dalla stringa, la divido
                                   // in programma e argomenti, poi la eseguo
{
  char *temp;
  char delim = ' ';
  char *args[64];     // alla fine uso questo
  char **next = args; // ma questo e' quello che riempio
  temp = strtok(comando, &delim);

  while (temp != NULL) {
    *next++ = temp;
    temp = strtok(NULL, &delim);
  }
  *next = NULL;
  execvp(args[0], args);
}

void ins(struct lista *l, char *comando) {
  struct lista *tmp = malloc(sizeof(struct lista));
  tmp->stringa = malloc(sizeof(char) * strlen(comando) + 1);
  tmp->next = l->next;
  strcpy(tmp->stringa, comando);
  l->next = tmp;
}

int main(int argc, char *argv[]) {

  size_t n;
  int status = 0;
  char *riga = (char *)malloc(sizeof(char));
  struct lista *lista_arrivi = (struct lista *)malloc(sizeof(struct lista));
  struct lista *tmp = lista_arrivi;
  lista_arrivi->next = NULL;

  while ((getline(&riga, &n, stdin) != 0)) {
    if (strcmp(riga, "\n") == 0)
      break;
    ins(lista_arrivi, riga);
    counter++;
  }

  while (lista_arrivi != NULL) {
    pid_t pid = fork();
    switch (pid) {
    case -1:
      exit(2);
      break;
    case 0: // processo figlio che prende in input i comandi

      leggiArgomenti(lista_arrivi->stringa);
      break;
    default: // processo padre che stampera' la lista
      lista_arrivi = lista_arrivi->next;
      break;
    }
  }

  tmp = tmp->next;

  while (tmp != NULL) {
    wait(&status);
    printf("Terminato: %s\n", tmp->stringa);
    tmp = tmp->next;
  }

  return 0;
}
