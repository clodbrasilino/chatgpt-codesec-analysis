#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node* create_node(char *str) {
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

void insert_node(Node **head, char *str) {
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
    char *str_copy = strdup(str);
    /* Possible weaknesses found:
     *  Invalid strtok() argument nr 2. A nul-terminated string is required. [invalidFunctionArgStr]
     */
    char *token = strtok(str_copy, &delimiter);
    while (token != NULL) {
        insert_node(&head, token);
        /* Possible weaknesses found:
         *  Invalid strtok() argument nr 2. A nul-terminated string is required. [invalidFunctionArgStr]
         */
        token = strtok(NULL, &delimiter);
    }
    free(str_copy);
    return head;
}

int main() {
    const char *input = "apple,banana,cherry";
    char delimiter = ',';
    Node *head = string_to_list(input, delimiter);

    Node *current = head;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }

    free_list(&head);
    return 0;
}