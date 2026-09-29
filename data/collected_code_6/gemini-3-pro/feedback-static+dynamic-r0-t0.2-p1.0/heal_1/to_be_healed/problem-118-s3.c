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

    while (*str != '\0') {
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

        newNode->data = *str;
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        str++;
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
    const char* myString = "Hello, World!";
    
    Node* list = stringToList(myString);
    if (list != NULL) {
        printList(list);
        freeList(list);
    } else {
        fprintf(stderr, "Memory allocation failed or input string was NULL.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}