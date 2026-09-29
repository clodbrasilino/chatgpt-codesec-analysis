#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node *create_node(const char *str, size_t str_len) {
    if (str == NULL) {
        return NULL;
    }

    if (str_len >= SIZE_MAX) {
        return NULL;
    }

    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }

    if (str_len > SIZE_MAX - 1) {
        free(new_node);
        return NULL;
    }

    new_node->data = (char *)malloc(str_len + 1);
    if (new_node->data == NULL) {
        free(new_node);
        return NULL;
    }

    if (str_len > 0) {
        memcpy(new_node->data, str, str_len);
    }
    new_node->data[str_len] = '\0';
    new_node->next = NULL;
    return new_node;
}

Node *string_to_list(const char *str, const char *delimiter) {
    if (str == NULL || delimiter == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, SIZE_MAX - 1);
    if (len >= SIZE_MAX - 1) {
        return NULL;
    }

    if (len > SIZE_MAX - 1) {
        return NULL;
    }

    char *str_copy = (char *)malloc(len + 1);
    if (str_copy == NULL) {
        return NULL;
    }

    if (len > 0) {
        memcpy(str_copy, str, len);
    }
    str_copy[len] = '\0';

    Node *head = NULL;
    Node *tail = NULL;
    char *saveptr;
    char *token = strtok_r(str_copy, delimiter, &saveptr);

    while (token != NULL) {
        size_t token_len = strnlen(token, SIZE_MAX - 1);
        if (token_len >= SIZE_MAX - 1) {
            free(str_copy);
            Node *current = head;
            while (current != NULL) {
                Node *next = current->next;
                free(current->data);
                free(current);
                current = next;
            }
            return NULL;
        }

        Node *new_node = create_node(token, token_len);
        if (new_node == NULL) {
            free(str_copy);
            Node *current = head;
            while (current != NULL) {
                Node *next = current->next;
                free(current->data);
                free(current);
                current = next;
            }
            return NULL;
        }

        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }

        token = strtok_r(NULL, delimiter, &saveptr);
    }

    free(str_copy);
    return head;
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

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }
}

int main(void) {
    const char *input = "apple,banana,cherry,date";
    Node *list = string_to_list(input, ",");

    if (list == NULL) {
        fprintf(stderr, "Failed to convert string to list\n");
        return EXIT_FAILURE;
    }

    print_list(list);
    free_list(list);

    return EXIT_SUCCESS;
}