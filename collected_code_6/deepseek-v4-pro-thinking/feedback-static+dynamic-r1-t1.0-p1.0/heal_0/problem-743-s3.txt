#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

static int append_node(struct Node **head, int data) {
    struct Node *node = malloc(sizeof *node);
    if (node == NULL) {
        return 0;
    }
    node->data = data;
    node->next = NULL;

    if (*head == NULL) {
        *head = node;
        return 1;
    }

    struct Node *tail = *head;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    tail->next = node;
    return 1;
}

static void free_list(struct Node *head) {
    while (head != NULL) {
        struct Node *next = head->next;
        free(head);
        head = next;
    }
}

struct Node *rotate_right(struct Node *head, int k) {
    if (head == NULL || k <= 0) {
        return head;
    }

    int length = 1;
    struct Node *tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
        length++;
    }

    k %= length;
    if (k == 0) {
        return head;
    }

    int steps = length - k;
    struct Node *new_tail = head;
    for (int i = 1; i < steps; i++) {
        new_tail = new_tail->next;
    }

    struct Node *new_head = new_tail->next;
    new_tail->next = NULL;
    tail->next = head;
    return new_head;
}

static void print_list(const struct Node *head) {
    const struct Node *current = head;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    struct Node *head = NULL;
    int values[] = {1, 2, 3, 4, 5};
    size_t count = sizeof values / sizeof values[0];

    for (size_t i = 0; i < count; i++) {
        if (!append_node(&head, values[i])) {
            fprintf(stderr, "malloc failed\n");
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    print_list(head);
    head = rotate_right(head, 2);
    print_list(head);

    free_list(head);
    return EXIT_SUCCESS;
}