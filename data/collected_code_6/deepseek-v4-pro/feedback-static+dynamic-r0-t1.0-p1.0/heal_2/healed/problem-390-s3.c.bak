#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} List;

Node *create_node(const char *data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = (char *)malloc(strlen(data) + 1);
    if (new_node->data == NULL) {
        free(new_node);
        return NULL;
    }
    strcpy(new_node->data, data);
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
    prefix_len = strlen(prefix);
    current = list->head;
    while (current != NULL) {
        size_t data_len = strlen(current->data);
        new_data = (char *)malloc(prefix_len + data_len + 1);
        if (new_data == NULL) {
            return 0;
        }
        strcpy(new_data, prefix);
        strcat(new_data, current->data);
        free(current->data);
        current->data = new_data;
        current = current->next;
    }
    return 1;
}

void list_print(const List *list) {
    Node *current;
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