#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *value;
    struct Node *next;
} Node;

Node* create_node(char *val) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) return NULL;
    new_node->value = val;
    new_node->next = NULL;
    return new_node;
}

void append_node(Node **head, char *val) {
    Node *new_node = create_node(val);
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
        free(temp->value);
        free(temp);
    }
}

Node* tuple_to_list(Node *tuple, const char *separator) {
    Node *list = NULL;
    for (Node *item = tuple; item != NULL; item = item->next) {
        append_node(&list, item->value);
        append_node(&list, (char *)separator);  // Cast to char* for simplicity
    }
    return list;
}

int main() {
    Node *tuple = NULL;
    append_node(&tuple, strdup("apple"));
    append_node(&tuple, strdup("banana"));
    append_node(&tuple, strdup("cherry"));

    const char *separator = " - ";
    Node *list = tuple_to_list(tuple, separator);

    for (Node *item = list; item != NULL; item = item->next) {
        printf("%s\n", item->value);
    }

    free_list(tuple);
    free_list(list);
    return 0;
}