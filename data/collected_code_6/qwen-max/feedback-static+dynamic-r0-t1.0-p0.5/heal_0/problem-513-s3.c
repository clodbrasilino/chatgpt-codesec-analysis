#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *value;
    struct Node *next;
} Node;

Node* create_node(char *value) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->value = strdup(value);
    new_node->next = NULL;
    return new_node;
}

void append_node(Node **head, char *value) {
    Node *new_node = create_node(value);
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

Node* convert_tuple_to_list(const char *tuple, const char *separator, const char *append_str) {
    Node *head = NULL;
    char *token = strtok((char *)tuple, separator);
    while (token != NULL) {
        append_node(&head, token);
        append_node(&head, (char *)append_str);
        token = strtok(NULL, separator);
    }
    return head;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
}

int main() {
    const char *tuple = "(1,2,3)";
    const char *separator = ",()";
    const char *append_str = "str";

    Node *list = convert_tuple_to_list(tuple, separator, append_str);

    Node *current = list;
    while (current != NULL) {
        printf("%s ", current->value);
        current = current->next;
    }
    printf("\n");

    free_list(list);
    return 0;
}