#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct Node {
    char *value;
    struct Node *next;
} Node;

Node *create_node(const char *token) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    size_t len = strnlen(token, SIZE_MAX);
    node->value = malloc(len + 1);
    if (node->value == NULL) {
        free(node);
        return NULL;
    }
    snprintf(node->value, len + 1, "%s", token);
    node->next = NULL;
    return node;
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

Node *string_to_list(const char *str, const char *delim) {
    if (str == NULL || delim == NULL) {
        return NULL;
    }
    size_t len = strnlen(str, SIZE_MAX);
    char *buffer = malloc(len + 1);
    if (buffer == NULL) {
        return NULL;
    }
    snprintf(buffer, len + 1, "%s", str);
    
    Node *head = NULL;
    Node *tail = NULL;
    
    char *token = strtok(buffer, delim);
    while (token != NULL) {
        Node *node = create_node(token);
        if (node == NULL) {
            free(buffer);
            free_list(head);
            return NULL;
        }
        if (head == NULL) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
        token = strtok(NULL, delim);
    }
    
    free(buffer);
    return head;
}

int main(void) {
    const char *text = "Convert this string to a list";
    Node *list = string_to_list(text, " ");
    if (list != NULL) {
        Node *current = list;
        while (current != NULL) {
            printf("%s\n", current->value);
            current = current->next;
        }
        free_list(list);
    }
    return 0;
}