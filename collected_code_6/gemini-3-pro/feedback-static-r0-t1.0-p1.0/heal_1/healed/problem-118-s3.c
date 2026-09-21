#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node* next;
} Node;

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
                Node* next = current->next;
                free(current);
                current = next;
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
        Node* next = current->next;
        free(current);
        current = next;
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
    const char* str = "Hello, World!";
    Node* list = stringToList(str);

    if (list != NULL) {
        printList(list);
        freeList(list);
    } else {
        printf("Failed to create list or empty string provided.\n");
    }

    return 0;
}