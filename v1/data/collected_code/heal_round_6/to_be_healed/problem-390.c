#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  char* data;
  struct Node* next;
} Node;

Node* createNode(const char* data) {
  if (data == NULL)
    return NULL;

  Node* newNode = (Node*)malloc(sizeof(Node));

  /* Possible weaknesses found:
   *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
   */
  size_t data_length = strlen(data);
  /* Possible weaknesses found:
   *  dereference of possibly-NULL 'newNode' [CWE-690] [-Wanalyzer-possible-null-dereference]
   */
  newNode->data = (char*)malloc(data_length + 1);

  if (newNode == NULL || newNode->data == NULL) {
    free(newNode);
    return NULL;
  }

  /* Possible weaknesses found:
   *   Does not check for buffer overflows when copying to destination (CWE-120).  Make sure destination can always hold the source data.
   */
  memcpy(newNode->data, data, data_length);
  newNode->data[data_length] = '\0';
  newNode->next = NULL;
  
  return newNode;
}

void insertAtBeginning(Node** head, const char* data) {
  if (data == NULL) return;
  
  Node* newNode = createNode(data);

  if(newNode != NULL) {
    newNode->next = *head;
    *head = newNode;
  }
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