#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node* create_node(char *str) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) return NULL;
    new_node->data = strdup(str);
    if (!new_node->data) {
        free(new_node);
        return NULL;
    }
    new_node->next = NULL;
    return new_node;
}

Node* string_to_list(const char *str, const char *delimiter) {
    Node *head = NULL;
    Node **current = &head;
    char *copy = strdup(str);
    char *token = strtok(copy, delimiter);

    while (token) {
        *current = create_node(token);
        if (!*current) {
            free(copy);
            return NULL;
        }
        current = &(*current)->next;
        token = strtok(NULL, delimiter);
    }

    free(copy);
    return head;
}

void free_list(Node *head) {
    Node *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
}

int main() {
    const char *input = "apple,banana,orange,grape";
    const char *delimiter = ",";
    Node *list = string_to_list(input, delimiter);

    if (!list) {
        fprintf(stderr, "Failed to create list\n");
        return 1;
    }

    for (Node *node = list; node; node = node->next) {
        printf("%s\n", node->data);
    }

    free_list(list);
    return 0;
}