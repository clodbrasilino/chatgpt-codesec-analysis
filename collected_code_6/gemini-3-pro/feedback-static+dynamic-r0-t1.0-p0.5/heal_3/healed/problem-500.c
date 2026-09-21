#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 4096

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

char* concatenate_list(Node *head) {
    if (head == NULL) {
        char *empty_str = malloc(1);
        if (empty_str != NULL) {
            empty_str[0] = '\0';
        }
        return empty_str;
    }

    size_t total_length = 0;
    Node *current = head;
    while (current != NULL) {
        if (current->data != NULL) {
            total_length += strnlen(current->data, MAX_STR_LEN);
        }
        current = current->next;
    }

    char *result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    char *ptr = result;
    current = head;
    while (current != NULL) {
        if (current->data != NULL) {
            size_t len = strnlen(current->data, MAX_STR_LEN);
            if (len > 0) {
                memcpy(ptr, current->data, len);
                ptr += len;
            }
        }
        current = current->next;
    }
    *ptr = '\0';

    return result;
}

Node* create_node(const char *data) {
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    
    if (data != NULL) {
        size_t len = strnlen(data, MAX_STR_LEN);
        new_node->data = malloc(len + 1);
        if (new_node->data == NULL) {
            free(new_node);
            return NULL;
        }
        if (len > 0) {
            memcpy(new_node->data, data, len);
        }
        new_node->data[len] = '\0';
    } else {
        new_node->data = NULL;
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

int main(void) {
    Node *head = create_node("Hello");
    if (head == NULL) return 1;

    head->next = create_node(", ");
    if (head->next == NULL) {
        free_list(head);
        return 1;
    }

    head->next->next = create_node("World");
    if (head->next->next == NULL) {
        free_list(head);
        return 1;
    }

    head->next->next->next = create_node("!");
    if (head->next->next->next == NULL) {
        free_list(head);
        return 1;
    }

    char *concatenated = concatenate_list(head);
    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
    }

    free_list(head);
    return 0;
}