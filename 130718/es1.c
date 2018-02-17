#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define bool int
#define true 1
#define false 0

struct list_el {
  char *comando;
  struct list_el *next;
};

void insert_el(struct list_el *head, char *command) {
  struct list_el *new_el = malloc(sizeof(struct list_el));
  new_el->comando = malloc(sizeof(char) * strlen(command));
  strcpy(new_el->comando, command);

  if (head == NULL) {
    head = new_el;
  } else {
    struct list_el *tmp = (head)->next;
    (head)->next = new_el;
    new_el->next = tmp;
  }
}
int main(int argc, char const *argv[]) {
  int count = 0;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  struct list_el *commands = (struct list_el *)malloc(sizeof(struct list_el));
  struct list_el *tmp = commands;

  commands->next = NULL;

  while ((read = getline(&line, &len, stdin)) != -1) {
    if (strcmp(line, "\n") == 0) {
      break;
    } else {
      insert_el(commands, line);
      count++;
    }
  }

  tmp = tmp->next;

  while (tmp != NULL) {
    printf("%s\n", tmp->comando);
    tmp = tmp->next;
  }
  printf("fine\n");

  free(line);
  exit(EXIT_SUCCESS);
}
