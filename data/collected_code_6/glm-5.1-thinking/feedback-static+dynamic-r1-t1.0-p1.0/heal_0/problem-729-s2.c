#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

Node *build_list(const int *values, size_t count) {
    Node dummy;
    dummy.next = NULL;
    Node *tail = &dummy;

    for (size_t i = 0; i < count; ++i) {
        Node *node = create_node(values[i]);
        if (node == NULL) {
            free_list(dummy.next);
            return NULL;
        }
        tail->next = node;
        tail = node;
    }

    return dummy.next;
}

Node *add_lists(Node *l1, Node *l2) {
    Node dummy;
    dummy.next = NULL;
    Node *tail = &dummy;

    while (l1 != NULL || l2 != NULL) {
        int sum = 0;
        if (l1 != NULL) {
            sum += l1->data;
            l1 = l1->next;
        }
        if (l2 != NULL) {
            sum += l2->data;
            l2 = l2->next;
        }

        Node *new_node = create_node(sum);
        if (new_node == NULL) {
            free_list(dummy.next);
            return NULL;
        }
        tail->next = new_node;
        tail = new_node;
    }

    return dummy.next;
}

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    int vals1[] = {1, 2, 3};
    int vals2[] = {4, 5, 6, 7};

    Node *l1 = build_list(vals1, ARRAY_SIZE(vals1));
    if (l1 == NULL) {
        return EXIT_FAILURE;
    }

    Node *l2 = build_list(vals2, ARRAY_SIZE(vals2));
    if (l2 == NULL) {
        free_list(l1);
        return EXIT_FAILURE;
    }

    Node *result = add_lists(l1, l2);
    if (result == NULL) {
        free_list(l1);
        free_list(l2);
        return EXIT_FAILURE;
    }

    print_list(result);

    free_list(l1);
    free_list(l2);
    free_list(result);

    return EXIT_SUCCESS;
}