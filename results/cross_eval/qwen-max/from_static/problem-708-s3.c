#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char value;
    struct Node* next;
} Node;

Node* createNode(char value) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) return NULL;
    node->value = value;
    node->next = NULL;
    return node;
}

Node* stringToList(const char* str) {
    Node* head = NULL;
    Node** current = &head;
    while (*str) {
        Node* newNode = createNode(*str);
        if (newNode == NULL) {
            return NULL;
        }
        *current = newNode;
        current = &((*current)->next);
        str++;
    }
    return head;
}

void freeList(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    const char* input = "hello";
    Node* list = stringToList(input);
    if (list == NULL) {
        printf("Failed to convert string to list.\n");
        return 1;
    }

    for (Node* p = list; p != NULL; p = p->next) {
        printf("%c -> ", p->value);
    }
    printf("NULL\n");

    freeList(list);
    return 0;
}