#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    void *data;
    int is_list;
    struct Node *next;
} Node;

Node *create_node(void *data, int is_list) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->is_list = is_list;
    node->next = NULL;
    return node;
}

void append_node(Node *head, Node *new_node) {
    if (head == NULL || new_node == NULL) {
        return;
    }
    Node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

size_t count_and_square_lists(Node *head) {
    size_t count = 0;
    Node *current = head;
    while (current != NULL) {
        if (current->is_list) {
            count++;
        }
        current = current->next;
    }
    return count * count;
}

void free_list(Node *head, int is_top_level) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        if (current->is_list) {
            free_list((Node *)current->data, 0);
        } else {
            free(current->data);
        }
        free(current);
        current = next;
    }
}

int main(void) {
    Node *sub_list1 = create_node(malloc(sizeof(int)), 0);
    *(int *)sub_list1->data = 1;
    append_node(sub_list1, create_node(malloc(sizeof(int)), 0));
    *(int *)sub_list1->next->data = 2;

    Node *sub_list2 = create_node(malloc(sizeof(int)), 0);
    *(int *)sub_list2->data = 3;

    Node *top_list = create_node(sub_list1, 1);
    append_node(top_list, create_node(malloc(sizeof(int)), 0));
    *(int *)top_list->next->data = 100;
    append_node(top_list, create_node(sub_list2, 1));
    append_node(top_list, create_node(malloc(sizeof(int)), 0));
    *(int *)top_list->next->next->next->data = 200;

    size_t result = count_and_square_lists(top_list);
    printf("%zu\n", result);

    free_list(top_list, 1);

    return 0;
}