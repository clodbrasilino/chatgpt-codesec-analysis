#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} List;

static Node *create_node(const char *data) {
    Node *new_node;
    size_t len;
    size_t max_safe_len = SIZE_MAX - 1;

    if (data == NULL) {
        return NULL;
    }

    len = 0;
    while (len < max_safe_len && data[len] != '\0') {
        len++;
    }
    if (len == max_safe_len) {
        return NULL;
    }

    new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }

    new_node->data = (char *)malloc(len + 1);
    if (new_node->data == NULL) {
        free(new_node);
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        new_node->data[i] = data[i];
    }
    new_node->data[len] = '\0';
    new_node->next = NULL;
    return new_node;
}

void list_init(List *list) {
    if (list != NULL) {
        list->head = NULL;
    }
}

int list_append(List *list, const char *data) {
    Node *new_node;
    Node *current;

    if (list == NULL || data == NULL) {
        return 0;
    }

    new_node = create_node(data);
    if (new_node == NULL) {
        return 0;
    }

    if (list->head == NULL) {
        list->head = new_node;
        return 1;
    }

    current = list->head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
    return 1;
}

void list_free(List *list) {
    Node *current;
    Node *next;

    if (list == NULL) {
        return;
    }

    current = list->head;
    while (current != NULL) {
        next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    list->head = NULL;
}

int list_prepend_string(List *list, const char *prefix) {
    Node *current;
    char *new_data;
    size_t prefix_len;

    if (list == NULL || prefix == NULL) {
        return 0;
    }

    if (list->head == NULL) {
        return 1;
    }

    prefix_len = 0;
    while (prefix[prefix_len] != '\0') {
        prefix_len++;
    }

    current = list->head;
    while (current != NULL) {
        size_t data_len = 0;
        while (current->data[data_len] != '\0') {
            data_len++;
        }

        if (prefix_len > SIZE_MAX - data_len - 1) {
            return 0;
        }

        new_data = (char *)malloc(prefix_len + data_len + 1);
        if (new_data == NULL) {
            return 0;
        }

        for (size_t i = 0; i < prefix_len; i++) {
            new_data[i] = prefix[i];
        }
        for (size_t i = 0; i < data_len; i++) {
            new_data[prefix_len + i] = current->data[i];
        }
        new_data[prefix_len + data_len] = '\0';
        free(current->data);
        current->data = new_data;
        current = current->next;
    }
    return 1;
}

void list_print(const List *list) {
    const Node *current;

    if (list == NULL) {
        return;
    }

    current = list->head;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }
}

int main(void) {
    List list;

    list_init(&list);
    list_append(&list, "world");
    list_append(&list, "example");
    list_append(&list, "test");

    printf("Before:\n");
    list_print(&list);

    list_prepend_string(&list, "hello_");

    printf("After:\n");
    list_print(&list);

    list_free(&list);

    return 0;
}