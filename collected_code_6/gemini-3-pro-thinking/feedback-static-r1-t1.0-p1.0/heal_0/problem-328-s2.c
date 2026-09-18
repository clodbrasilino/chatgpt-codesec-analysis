#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_node(int data);
Node* rotate_left(Node* head, size_t k);
void print_list(const Node* head);
void free_list(Node* head);

int main(void) {
    Node* head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);
    head->next->next->next = create_node(4);
    head->next->next->next->next = create_node(5);

    head = rotate_left(head, 2);

    print_list(head);

    free_list(head);

    return EXIT_SUCCESS;
}

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

Node* rotate_left(Node* head, size_t k) {
    if (!head || !head->next || k == 0) {
        return head;
    }

    size_t length = 1;
    Node* tail = head;
    while (tail->next) {
        length++;
        tail = tail->next;
    }

    k = k % length;
    if (k == 0) {
        return head;
    }

    Node* current = head;
    for (size_t i = 1; i < k; i++) {
        current = current->next;
    }

    Node* new_head = current->next;
    current->next = NULL;
    tail->next = head;

    return new_head;
}

void print_list(const Node* head) {
    const Node* current = head;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void free_list(Node* head) {
    Node* current = head;
    while (current) {
        Node* next_node = current->next;
        free(current);
        current = next_node;
    }
}