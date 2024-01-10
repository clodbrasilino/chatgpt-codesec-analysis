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

  /* Possible weaknesses found:
   *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
   */
  newNode->data = malloc(strlen(data) + 1);
  if (newNode->data != NULL) {
    /* Possible weaknesses found:
     *   Does not check for buffer overflows when copying to destination [MS-banned]  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy  easily misused).
     */
    strcpy(newNode->data, data);
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