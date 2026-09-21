#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct Node {
    char *value;
    struct Node *next;
} Node;

void free_list(Node *head) {
    while (head) {
        Node *next = head->next;
        free(head->value);
        free(head);
        head = next;
    }
}

Node *string_to_list(const char *str, const char *delim) {
    if (!str || !delim) return NULL;

    Node head = {NULL, NULL};
    Node *current = &head;
    int error = 0;

    const char *ptr = str;

    while (*ptr) {
        size_t span = strspn(ptr, delim);
        ptr += span;
        if (!*ptr) break;

        size_t token_len = strcspn(ptr, delim);

        if (token_len == SIZE_MAX) {
            error = 1;
            break;
        }

        size_t alloc_size = token_len + 1;

        Node *new_node = malloc(sizeof(Node));
        if (!new_node) {
            error = 1;
            break;
        }

        new_node->value = malloc(alloc_size);
        if (!new_node->value) {
            free(new_node);
            error = 1;
            break;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(new_node->value, ptr, token_len);
        new_node->value[token_len] = '\0';
        new_node->next = NULL;

        current->next = new_node;
        current = new_node;

        ptr += token_len;
    }

    if (error) {
        Node *n = head.next;
        while (n) {
            Node *tmp = n->next;
            free(n->value);
            free(n);
            n = tmp;
        }
        return NULL;
    }

    return head.next;
}

int main(void) {
    const char *text = "apple,banana,cherry,date";
    const char *delim = ",";
    Node *list = string_to_list(text, delim);

    if (list) {
        Node *curr = list;
        while (curr) {
            printf("%s\n", curr->value);
            curr = curr->next;
        }
        free_list(list);
    }

    return 0;
}