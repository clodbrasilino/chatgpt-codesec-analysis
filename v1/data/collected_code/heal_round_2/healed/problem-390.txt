#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  char* data;
  struct Node* next;
} Node;

Node* createNode(char* data) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  if (newNode == NULL) {
    return NULL;
  }

  size_t data_length = strlen(data);
  newNode->data = malloc(data_length + 1);
  if (newNode->data != NULL) {
    strncpy(newNode->data, data, data_length + 1);
  }

  newNode->next = NULL;
  return newNode;
}

void insertAtBeginning(Node** head, char* data) {
  Node* newNode = createNode(data);
  if (newNode == NULL) {
    return;
  }

  newNode->next = *head;
  *head = newNode;
}

void displayList(Node* head) {
  Node* temp = head;
  while (temp != NULL) {
    printf("%s ", temp->data);
    temp = temp->next;
  }
  printf("\n");
}

int main() {
  Node* head = NULL;

  insertAtBeginning(&head, "World");
  insertAtBeginning(&head, "Hello");

  displayList(head);

  return 0;
}