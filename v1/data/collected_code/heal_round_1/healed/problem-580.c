#include <stdio.h>

typedef struct Node {
  int number;
  struct Node *next;
} Node;

void extractEvenElements(Node *head) {
  if (head == NULL)
    return;
    
  while (head != NULL) {
    if (head->number % 2 == 0)
      printf("%d\n", head->number);
    head = head->next;
  }
}

int main() {
  Node num5 = {5, NULL};
  Node num4 = {4, &num5};
  Node num3 = {3, &num4};
  Node num1 = {1, &num3};

  extractEvenElements(&num1);

  return 0;
}