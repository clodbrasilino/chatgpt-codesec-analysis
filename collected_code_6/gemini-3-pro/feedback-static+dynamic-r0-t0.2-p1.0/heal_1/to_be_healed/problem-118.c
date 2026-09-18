#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data;
    struct Node* next;
} Node;
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['python', 'programming'], got <no output>
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got <no output>
  *  test case 2 failed: expected ['write', 'a', 'program'], got <no output>
  */

Node* stringToList(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    Node* head = NULL;
    Node* tail = NULL;

    for (size_t i = 0; str[i] != '\0'; i++) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        if (newNode == NULL) {
            Node* current = head;
            while (current != NULL) {
                Node* temp = current;
                current = current->next;
                free(temp);
            }
            return NULL;
        }

        newNode->data = str[i];
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    return head;
}

void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%c -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main(void) {
    /* Possible weaknesses found:
     *  Assignment 'myString="Hello, World!"', assigned value is "Hello, World!"
     */
    const char* myString = "Hello, World!";
    
    Node* list = stringToList(myString);
    /* Possible weaknesses found:
     *  Condition 'myString!=NULL' is always true
     *  Condition 'myString[0]!='\0'' is always true [knownConditionTrueFalse]
     *  Condition 'myString[0]!='\0'' is always true
     *  Condition 'myString!=NULL' is always true [knownConditionTrueFalse]
     */
    if (list == NULL && myString != NULL && myString[0] != '\0') {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printList(list);
    freeList(list);

    return EXIT_SUCCESS;
}