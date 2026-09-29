#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

Node* find_max_ascending_sublist(Node* head) {
    if (head == NULL) {
        return NULL;
    }

    Node* max_start = head;
    int max_len = 1;

    Node* current_start = head;
    int current_len = 1;
    Node* current = head;

    while (current->next != NULL) {
        if (current->next->data > current->data) {
            current_len++;
        } else {
            if (current_len > max_len) {
                max_len = current_len;
                max_start = current_start;
            }
            current_start = current->next;
            current_len = 1;
        }
        current = current->next;
    }

    if (current_len > max_len) {
        max_start = current_start;
    }

    Node* new_head = NULL;
    Node* tail = NULL;
    current = max_start;

    for (int i = 0; i < max_len; i++) {
        Node* new_node = create_node(current->data);
        if (new_head == NULL) {
            new_head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
        current = current->next;
    }

    return new_head;
}

void free_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
}

void print_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    Node* head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);
    head->next->next->next = create_node(1);
    head->next->next->next->next = create_node(2);
    head->next->next->next->next->next = create_node(3);
    head->next->next->next->next->next->next = create_node(4);
    head->next->next->next->next->next->next->next = create_node(5);

    Node* max_sublist = find_max_ascending_sublist(head);
    print_list(max_sublist);

    free_list(head);
    free_list(max_sublist);

    return 0;
}