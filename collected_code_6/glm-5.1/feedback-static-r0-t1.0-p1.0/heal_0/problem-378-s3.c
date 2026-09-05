#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node* shift_last_to_first(struct Node *head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    struct Node *second_last = head;
    while (second_last->next->next != NULL) {
        second_last = second_last->next;
    }

    struct Node *last = second_last->next;
    second_last->next = NULL;
    last->next = head;
    head = last;

    return head;
}

struct Node* create_node(int data) {
    struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void free_list(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        struct Node *next = current->next;
        free(current);
        current = next;
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

int main() {
    struct Node *head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);
    head->next->next->next = create_node(4);

    print_list(head);
    head = shift_last_to_first(head);
    print_list(head);

    free_list(head);
    return 0;
}