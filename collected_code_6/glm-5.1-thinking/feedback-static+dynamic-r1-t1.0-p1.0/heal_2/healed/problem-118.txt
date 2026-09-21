#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *value;
    struct Node *next;
} Node;

Node *create_node(const char *token) {
    if (token == NULL) {
        return NULL;
    }
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    size_t len = strlen(token);
    node->value = malloc(len + 1);
    if (node->value == NULL) {
        free(node);
        return NULL;
    }
    memcpy(node->value, token, len + 1);
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
    size_t len = strlen(str);
    char *buffer = malloc(len + 1);
    if (buffer == NULL) {
        return NULL;
    }
    memcpy(buffer, str, len + 1);
    
    Node *head = NULL;
    Node *tail = NULL;
    
    char *saveptr;
    char *token = strtok_r(buffer, delim, &saveptr);
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
        token = strtok_r(NULL, delim, &saveptr);
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