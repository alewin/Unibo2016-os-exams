#include <dirent.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

struct list {
  char *name;
  int num;
  struct list *next;
};

struct list *newNode(char *nome, int n) {
  struct list *tmp = (struct list *)malloc(sizeof(struct list));
  tmp->num = n;
  tmp->name = (char *)(malloc(sizeof(char) * strlen(nome)));
  strcpy(tmp->name, nome);

  tmp->next = NULL;
  return tmp;
}
void sortedInsert(struct list **head_ref, struct list *new_node) {
  struct list *current;
  /* Special case for the head end */
  if (*head_ref == NULL || (*head_ref)->num >= new_node->num) {
    new_node->next = *head_ref;
    *head_ref = new_node;
  } else {
    /* Locate the node before the point of insertion */
    current = *head_ref;
    while (current->next != NULL && current->next->num < new_node->num) {
      current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
  }
}

void printList(struct list *head) {
  struct list *temp = head;
  while (temp != NULL) {
    printf("%s - %d  ", temp->name, temp->num);
    temp = temp->next;
  }
}
int main(int argc, char const *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Expected 1 parameter");
    return (-1);
  }

  DIR *dir;
  struct dirent *entry;
  struct stat sb;
  dir = opendir(argv[1]);
  struct list *head = NULL;

  if (dir != NULL) {
    while ((entry = readdir(dir)) != NULL) {
      stat(entry->d_name, &sb);

      struct list *new_node = newNode(entry->d_name, entry->d_ino);
      sortedInsert(&head, new_node);
    }
    printList(head);
  } else {
    fprintf(stderr, "Error on opendir()");
    return -1;
  }
}
