#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *value;
    struct Node *next;
} Node;

void free_list(Node *head) {
    while (head != NULL) {
        Node *next = head->next;
        free(head->value);
        free(head);
        head = next;
    }
}

Node *tuple_to_list(const char **tuple, size_t length, const char *separator) {
    Node *head = NULL;
    Node *tail = NULL;

    if (tuple == NULL || separator == NULL || length == 0) {
        return NULL;
    }

    for (size_t i = 0; i < length; ++i) {
        if (tuple[i] == NULL) {
            free_list(head);
            return NULL;
        }

        size_t element_length = strlen(tuple[i]);
        char *element_copy = malloc(element_length + 1);
        if (element_copy == NULL) {
            free_list(head);
            return NULL;
        }
        memcpy(element_copy, tuple[i], element_length + 1);

        Node *element_node = malloc(sizeof(Node));
        if (element_node == NULL) {
            free(element_copy);
            free_list(head);
            return NULL;
        }
        element_node->value = element_copy;
        element_node->next = NULL;

        if (head == NULL) {
            head = element_node;
            tail = element_node;
        } else {
            tail->next = element_node;
            tail = element_node;
        }

        size_t separator_length = strlen(separator);
        char *separator_copy = malloc(separator_length + 1);
        if (separator_copy == NULL) {
            free_list(head);
            return NULL;
        }
        memcpy(separator_copy, separator, separator_length + 1);

        Node *separator_node = malloc(sizeof(Node));
        if (separator_node == NULL) {
            free(separator_copy);
            free_list(head);
            return NULL;
        }
        separator_node->value = separator_copy;
        separator_node->next = NULL;

        tail->next = separator_node;
        tail = separator_node;
    }

    return head;
}

int main(void) {
    const char *tuple[] = {"one", "two", "three"};
    size_t length = sizeof(tuple) / sizeof(tuple[0]);

    Node *list = tuple_to_list(tuple, length, ", ");
    if (list == NULL) {
        return EXIT_FAILURE;
    }

    for (Node *current = list; current != NULL; current = current->next) {
        printf("%s\n", current->value);
    }

    free_list(list);
    return EXIT_SUCCESS;
}