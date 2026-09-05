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

void append_node(Node **head, void *data, int is_list) {
    Node *new_node = create_node(data, is_list);
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
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

void free_list(Node *head, int free_sublists) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        if (current->is_list && free_sublists) {
            free_list((Node *)current->data, 1);
        }
        free(current);
        current = next;
    }
}

int main(void) {
    Node *sublist1 = NULL;
    append_node(&sublist1, (void *)(long)10, 0);
    append_node(&sublist1, (void *)(long)20, 0);

    Node *sublist2 = NULL;
    append_node(&sublist2, (void *)(long)30, 0);

    Node *main_list = NULL;
    append_node(&main_list, (void *)(long)5, 0);
    append_node(&main_list, sublist1, 1);
    append_node(&main_list, (void *)(long)15, 0);
    append_node(&main_list, sublist2, 1);
    append_node(&main_list, (void *)(long)25, 0);

    size_t result = count_and_square_lists(main_list);
    printf("%zu\n", result);

    free_list(main_list, 1);

    return 0;
}