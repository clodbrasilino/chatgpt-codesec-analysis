#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node* create_node(char *str) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = strdup(str);
    if (new_node->data == NULL) {
        free(new_node);
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->next = NULL;
    return new_node;
}

void append_to_list(Node **head, char *str) {
    Node *new_node = create_node(str);
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

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
}

int main() {
    Node *list = NULL;
    char str[] = "example string";
    append_to_list(&list, str);

    Node *current = list;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }

    free_list(list);
    return 0;
}