#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *create_node(int data) {
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void append_node(struct Node **head, int data) {
    struct Node *new_node = create_node(data);
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    struct Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

void remove_consecutive_duplicates(struct Node *head) {
    if (head == NULL) {
        return;
    }
    struct Node *current = head;
    while (current->next != NULL) {
        if (current->data == current->next->data) {
            struct Node *duplicate = current->next;
            current->next = duplicate->next;
            free(duplicate);
        } else {
            current = current->next;
        }
    }
}

void print_list(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void free_list(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        struct Node *next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    struct Node *list = NULL;
    int values[] = {1, 1, 2, 3, 3, 3, 4, 5, 5, 5, 5, 6};
    size_t count = sizeof(values) / sizeof(values[0]);

    for (size_t i = 0; i < count; i++) {
        append_node(&list, values[i]);
    }

    printf("Original list: ");
    print_list(list);

    remove_consecutive_duplicates(list);

    printf("After removing consecutive duplicates: ");
    print_list(list);

    free_list(list);
    return 0;
}