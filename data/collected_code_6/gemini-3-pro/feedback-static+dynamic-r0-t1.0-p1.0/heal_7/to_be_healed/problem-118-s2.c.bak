#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* data;
    struct Node* next;
} Node;
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['write', 'a', 'program'], got <no output>
  *  test case 0 failed: expected ['python', 'programming'], got <no output>
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got <no output>
  */

Node* stringToList(char* str) {
    if (str == NULL) {
        return NULL;
    }

    Node* head = NULL;
    Node* tail = NULL;

    char* token = strtok(str, " \t\n\r");
    while (token != NULL) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        if (newNode == NULL) {
            Node* current = head;
            while (current != NULL) {
                Node* next = current->next;
                free(current->data);
                free(current);
                current = next;
            }
            return NULL;
        }
        
        newNode->data = (char*)malloc(strlen(token) + 1);
        if (newNode->data != NULL) {
            strcpy(newNode->data, token);
        }
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        token = strtok(NULL, " \t\n\r");
    }

    return head;
}

void printList(Node* head) {
    printf("[");
    Node* current = head;
    while (current != NULL) {
        printf("'%s'", current->data ? current->data : "");
        if (current->next != NULL) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]\n");
}

void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        if (current->data) {
            free(current->data);
        }
        free(current);
        current = next;
    }
}

int main(void) {
    char buffer[65536];
    
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        Node* list = stringToList(buffer);
        printList(list);
        freeList(list);
    }

    return 0;
}