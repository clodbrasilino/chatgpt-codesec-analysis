#if defined(__linux__) || defined(__APPLE__)
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 4096

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node* create_node(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    
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

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

void prepend_string_to_list(Node *head, const char *prefix) {
    if (head == NULL || prefix == NULL) {
        return;
    }
    
    size_t prefix_len = strnlen(prefix, MAX_STRING_LEN);
    if (prefix_len == 0 || prefix_len == MAX_STRING_LEN) {
        return;
    }
    
    Node *current = head;
    while (current != NULL) {
        if (current->data != NULL) {
            size_t data_len = strnlen(current->data, MAX_STRING_LEN);
            size_t total_len = prefix_len + data_len + 1;
            char *new_data = (char *)malloc(total_len);
            if (new_data != NULL) {
                snprintf(new_data, total_len, "%s%s", prefix, current->data);
                free(current->data);
                current->data = new_data;
            }
        }
        current = current->next;
    }
}

int main(void) {
    Node *head = create_node("apple");
    if (head == NULL) {
        return 1;
    }
    
    head->next = create_node("banana");
    if (head->next == NULL) {
        free_list(head);
        return 1;
    }
    
    head->next->next = create_node("cherry");
    if (head->next->next == NULL) {
        free_list(head);
        return 1;
    }
    
    prepend_string_to_list(head, "fruit_");
    
    Node *current = head;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }
    
    free_list(head);
    return 0;
}