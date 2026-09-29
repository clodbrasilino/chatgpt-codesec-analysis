#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data;
    struct Node *next;
} Node;

Node* create_node(char data) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void append_to_list(Node **head, char data) {
    Node *new_node = create_node(data);
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

Node* string_to_list(const char *str) {
    Node *head = NULL;
    for (int i = 0; str[i] != '\0'; ++i) {
        append_to_list(&head, str[i]);
    }
    return head;
}

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%c -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    const char *str = "Hello, World!";
    Node *list = string_to_list(str);
    print_list(list);
    free_list(list);
    return 0;
}