#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

int get_nth_item(const struct Node *head, size_t n, int *out_value) {
    if (out_value == NULL) {
        return -1;
    }

    const struct Node *current = head;
    size_t index = 0;

    while (current != NULL && index < n) {
        current = current->next;
        index++;
    }

    if (current == NULL) {
        return -1;
    }

    *out_value = current->data;
    return 0;
}

struct Node *create_node(int data) {
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void free_list(struct Node *head) {
    struct Node *current = head;
    struct Node *next_node;
    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
}

int main(void) {
    struct Node *head = create_node(10);
    if (head == NULL) {
        return EXIT_FAILURE;
    }

    head->next = create_node(20);
    if (head->next == NULL) {
        free_list(head);
        return EXIT_FAILURE;
    }

    head->next->next = create_node(30);
    if (head->next->next == NULL) {
        free_list(head);
        return EXIT_FAILURE;
    }

    int value;
    if (get_nth_item(head, 1, &value) == 0) {
        printf("%d\n", value);
    } else {
        printf("Index out of bounds\n");
    }

    free_list(head);
    return EXIT_SUCCESS;
}