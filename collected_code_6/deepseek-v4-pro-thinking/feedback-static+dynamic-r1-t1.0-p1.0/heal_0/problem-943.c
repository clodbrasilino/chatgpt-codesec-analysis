#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

int append_node(struct Node **head, int data) {
    struct Node *node = malloc(sizeof(*node));
    if (node == NULL) {
        return 0;
    }
    node->data = data;
    node->next = NULL;

    if (*head == NULL) {
        *head = node;
        return 1;
    }

    struct Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
    return 1;
}

struct Node *merge_sorted_lists(struct Node *a, struct Node *b) {
    struct Node dummy;
    struct Node *tail = &dummy;
    dummy.next = NULL;

    while (a != NULL && b != NULL) {
        if (a->data <= b->data) {
            tail->next = a;
            a = a->next;
        } else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }

    if (a != NULL) {
        tail->next = a;
    } else {
        tail->next = b;
    }

    return dummy.next;
}

void print_list(const struct Node *head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void free_list(struct Node *head) {
    while (head != NULL) {
        struct Node *next = head->next;
        free(head);
        head = next;
    }
}

int main(void) {
    struct Node *list1 = NULL;
    struct Node *list2 = NULL;

    if (!append_node(&list1, 1) ||
        !append_node(&list1, 3) ||
        !append_node(&list1, 5) ||
        !append_node(&list2, 2) ||
        !append_node(&list2, 4) ||
        !append_node(&list2, 6)) {
        fprintf(stderr, "Error: memory allocation failed\n");
        free_list(list1);
        free_list(list2);
        return EXIT_FAILURE;
    }

    struct Node *merged = merge_sorted_lists(list1, list2);
    list1 = NULL;
    list2 = NULL;

    print_list(merged);
    free_list(merged);

    return EXIT_SUCCESS;
}