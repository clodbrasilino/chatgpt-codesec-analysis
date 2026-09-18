#include <stdio.h>

struct Node {
  int data;
  struct Node* next;
};

int isPresent(struct Node* head, int key) {
  struct Node* temp = head;
  while (temp != NULL) {
    if (temp->data == key) return 1;
    temp = temp->next;
  }
  return 0;
}

struct Node* newNode(int data) {
  /* Possible weaknesses found:
   *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
   *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
   */
  struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
  if (new_node == NULL) {
    fprintf(stderr, "Error in allocating memory\n");
    return NULL;
  }
  
  new_node->data = data;
  new_node->next = NULL;
  return new_node;
}

void printList(struct Node* node) {
  while (node != NULL) {
    printf("%d ", node->data);
    node = node->next;
  }
  printf("\n");
}

int main() {
  struct Node* head = newNode(10);
  struct Node* second = newNode(20);
  struct Node* third = newNode(30);
  
  if (!head || !second || !third) return 1;

  head->next = second;
  second->next = third;
  
  printList(head);
  
  int key = 20;
  if(isPresent(head, key)) {
    printf("%d is present in the list\n", key);
  } else {
    printf("%d is not present in the list\n", key);
  }

  key = 50;
  if(isPresent(head, key)) {
    printf("%d is present in the list\n", key);
  } else {
    printf("%d is not present in the list\n", key);
  }

  /* Possible weaknesses found:
   *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
   *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
   */
  free(third);
  free(second);
  free(head);

  return 0;
}