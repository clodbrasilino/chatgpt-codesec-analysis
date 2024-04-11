#include <stdio.h>
#include <stdlib.h>

struct Node {
  int value;
  struct Node* next;
};

struct Dictionary {
  struct Node* head;
};

int checkValues(struct Dictionary* dict) {
  if (dict == NULL || dict->head == NULL) {
      return 1;
  }

  int value = dict->head->value;
  struct Node* current = dict->head->next;

  while (current != NULL) {
      if (current->value != value) {
          return 0;
      }
      current = current->next;
  }

  return 1;
}

int main() {
  struct Dictionary* dict = malloc(sizeof(struct Dictionary));
  if (dict == NULL) {
    return -1;
  }
  dict->head = NULL;

  struct Node* node1 = malloc(sizeof(struct Node));
  if (node1 == NULL) {
    free(dict);
    return -1;
  }
  node1->value = 5;
  node1->next = NULL;
  dict->head = node1;

  struct Node* node2 = malloc(sizeof(struct Node));
  if (node2 == NULL) {
    free(node1);
    free(dict);
    return -1;
  }
  node2->value = 5;
  node2->next = NULL;
  node1->next = node2;

  struct Node* node3 = malloc(sizeof(struct Node));
  if (node3 == NULL) {
    free(node2);
    free(node1);
    free(dict);
    return -1;
  }
  node3->value = 5;
  node3->next = NULL;
  node2->next = node3;

  printf("%d\n", checkValues(dict));

  free(node3);
  free(node2);
  free(node1);
  free(dict);

  return 0;
}