#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node* next;
} Node;

void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* nextNode = current->next;
        free(current);
        current = nextNode;
    }
}
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
            freeList(head);
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

void printList(const Node* head) {
    const Node* current = head;
    while (current != NULL) {
        putchar(current->data);
        current = current->next;
    }
    putchar('\n');
}

int main(void) {
    const char* sampleString = "Hello, World!";
    
    Node* listHead = stringToList(sampleString);
    
    if (listHead != NULL) {
        printList(listHead);
        freeList(listHead);
    }
    
    return EXIT_SUCCESS;
}