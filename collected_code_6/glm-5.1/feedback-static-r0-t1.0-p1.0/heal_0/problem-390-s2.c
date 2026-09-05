#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char *data;
    struct Node *next;
};

void insert_string_at_beginning(struct Node *head, const char *prefix) {
    if (head == NULL || prefix == NULL) {
        return;
    }

    struct Node *current = head;
    size_t prefix_len = strlen(prefix);

    while (current != NULL) {
        if (current->data == NULL) {
            current = current->next;
            continue;
        }

        size_t current_len = strlen(current->data);
        size_t new_len = prefix_len + current_len;
        
        char *new_data = (char *)malloc(new_len + 1);
        if (new_data == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            current = current->next;
            continue;
        }

        memcpy(new_data, prefix, prefix_len);
        memcpy(new_data + prefix_len, current->data, current_len);
        new_data[new_len] = '\0';

        free(current->data);
        current->data = new_data;

        current = current->next;
    }
}

struct Node *create_node(const char *str) {
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        return NULL;
    }

    new_node->data = (char *)malloc(strlen(str) + 1);
    if (new_node->data == NULL) {
        free(new_node);
        return NULL;
    }
    strcpy(new_node->data, str);
    new_node->next = NULL;
    return new_node;
}

void append_node(struct Node **head_ref, const char *str) {
    struct Node *new_node = create_node(str);
    if (new_node == NULL) {
        return;
    }

    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    struct Node *last = *head_ref;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = new_node;
}

void free_list(struct Node *head) {
    struct Node *tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp->data);
        free(tmp);
    }
}

void print_list(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }
}

int main() {
    struct Node *head = NULL;

    append_node(&head, "apple");
    append_node(&head, "banana");
    append_node(&head, "cherry");

    printf("Original list:\n");
    print_list(head);

    insert_string_at_beginning(head, "fruit_");

    printf("\nModified list:\n");
    print_list(head);

    free_list(head);

    return 0;
}