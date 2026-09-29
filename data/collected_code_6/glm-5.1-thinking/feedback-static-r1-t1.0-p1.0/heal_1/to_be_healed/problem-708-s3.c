#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

char *string_duplicate(const char *src) {
    if (src == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(src) + 1;
    char *dst = malloc(len);
    if (dst == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dst, src, len);
    return dst;
}

Node *string_to_list(const char *str, const char *delim) {
    if (str == NULL || delim == NULL) {
        return NULL;
    }

    char *copy = string_duplicate(str);
    if (copy == NULL) {
        return NULL;
    }

    Node *head = NULL;
    Node *tail = NULL;
    char *token = strtok(copy, delim);

    while (token != NULL) {
        Node *new_node = malloc(sizeof(Node));
        if (new_node == NULL) {
            free(copy);
            free_list(head);
            return NULL;
        }

        new_node->data = string_duplicate(token);
        if (new_node->data == NULL) {
            free(new_node);
            free(copy);
            free_list(head);
            return NULL;
        }

        new_node->next = NULL;

        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }

        token = strtok(NULL, delim);
    }

    free(copy);
    return head;
}

int main(void) {
    const char *input = "Convert this string into a linked list";
    const char *delimiter = " ";

    Node *list = string_to_list(input, delimiter);
    if (list == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    Node *current = list;
    while (current != NULL) {
        printf("[%s]\n", current->data);
        current = current->next;
    }

    free_list(list);
    return EXIT_SUCCESS;
}