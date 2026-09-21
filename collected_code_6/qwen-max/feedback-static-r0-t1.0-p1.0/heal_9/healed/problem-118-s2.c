#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node* create_node(const char *str) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = strdup(str);
    if (new_node->data == NULL) {
        free(new_node);
        return NULL;
    }
    new_node->next = NULL;
    return new_node;
}

void insert_node(Node **head, const char *str) {
    Node *new_node = create_node(str);
    if (new_node == NULL) {
        return;
    }
    new_node->next = *head;
    *head = new_node;
}

void free_list(Node **head) {
    Node *current = *head;
    while (current != NULL) {
        Node *temp = current->next;
        free(current->data);
        free(current);
        current = temp;
    }
    *head = NULL;
}

Node* string_to_list(const char *str, char delimiter) {
    Node *head = NULL;
    size_t len = strnlen(str, 2147483647); // Use strnlen to avoid over-read
    char *str_copy = (char *)malloc(len + 1);
    if (str_copy == NULL) {
        return NULL;
    }
    strncpy(str_copy, str, len + 1); // Use strncpy for safer copy
    str_copy[len] = '\0'; // Ensure null termination

    char delimiters[2] = {delimiter, '\0'};
    char *token = strtok(str_copy, delimiters);
    while (token != NULL) {
        insert_node(&head, token);
        token = strtok(NULL, delimiters);
    }
    free(str_copy);
    return head;
}

int main() {
    const char *input = "apple,banana,cherry";
    char delimiter = ',';
    Node *head = string_to_list(input, delimiter);

    for (Node *current = head; current != NULL; current = current->next) {
        printf("%s\n", current->data);
    }

    free_list(&head);
    return 0;
}