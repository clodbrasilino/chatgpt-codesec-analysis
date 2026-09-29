#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

size_t count_lists(Node **lists, size_t num_lists) {
    size_t count = 0;
    if (lists == NULL) {
        return 0;
    }
    for (size_t i = 0; i < num_lists; i++) {
        if (lists[i] != NULL) {
            count++;
        }
    }
    return count;
}

Node *create_node(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void) {
    size_t num_lists = 4;
    Node **lists = (Node **)malloc(num_lists * sizeof(Node *));
    if (lists == NULL) {
        return EXIT_FAILURE;
    }

    lists[0] = create_node(1);
    lists[1] = NULL;
    lists[2] = create_node(2);
    lists[3] = NULL;

    size_t count = count_lists(lists, num_lists);
    printf("%zu\n", count);

    for (size_t i = 0; i < num_lists; i++) {
        free_list(lists[i]);
    }
    free(lists);

    return 0;
}