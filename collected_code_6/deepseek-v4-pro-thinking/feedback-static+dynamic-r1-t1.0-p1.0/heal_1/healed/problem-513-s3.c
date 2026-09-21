#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *value;
    struct Node *next;
} Node;

static char *string_duplicate(const char *src, size_t max_len) {
    if (!src) {
        return NULL;
    }

    const char *null_pos = memchr(src, '\0', max_len);
    size_t len;
    if (null_pos) {
        len = (size_t)(null_pos - src) + 1;
    } else {
        len = max_len + 1;
    }

    char *copy = malloc(len);
    if (!copy) {
        return NULL;
    }

    if (null_pos) {
        memcpy(copy, src, len);
    } else {
        memcpy(copy, src, max_len);
        copy[max_len] = '\0';
    }

    return copy;
}

static Node *node_create(const char *value, size_t max_len) {
    Node *node = malloc(sizeof(*node));
    if (!node) {
        return NULL;
    }

    node->value = string_duplicate(value, max_len);
    if (!node->value) {
        free(node);
        return NULL;
    }

    node->next = NULL;
    return node;
}

static void list_free(Node *head) {
    while (head) {
        Node *next = head->next;
        free(head->value);
        free(head);
        head = next;
    }
}

Node *tuple_to_list(const char *tuple[], size_t length, const char *separator, size_t max_len) {
    Node *head = NULL;
    Node *tail = NULL;

    if (!tuple || !separator || length == 0) {
        return NULL;
    }

    for (size_t i = 0; i < length; i++) {
        Node *item = node_create(tuple[i], max_len);
        if (!item) {
            list_free(head);
            return NULL;
        }

        if (!head) {
            head = tail = item;
        } else {
            tail->next = item;
            tail = item;
        }

        Node *sep = node_create(separator, max_len);
        if (!sep) {
            list_free(head);
            return NULL;
        }

        tail->next = sep;
        tail = sep;
    }

    return head;
}

int main(void) {
    const char *tuple[] = {"apple", "banana", "cherry"};
    const char *separator = "-";
    size_t max_len = 1024;

    Node *list = tuple_to_list(tuple, sizeof(tuple) / sizeof(tuple[0]), separator, max_len);
    if (!list) {
        fprintf(stderr, "Failed to convert tuple to list\n");
        return EXIT_FAILURE;
    }

    for (Node *node = list; node; node = node->next) {
        printf("%s\n", node->value);
    }

    list_free(list);
    return EXIT_SUCCESS;
}