#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node** lists;
    size_t count;
} ListArray;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void free_list(Node* head) {
    while (head) {
        Node* tmp = head;
        head = head->next;
        free(tmp);
    }
}

ListArray split_list(Node* head, size_t n) {
    ListArray result = {NULL, 0};
    if (!head || n == 0) {
        return result;
    }

    size_t total_nodes = 0;
    Node* current = head;
    while (current) {
        total_nodes++;
        current = current->next;
    }

    result.count = (total_nodes + n - 1) / n;
    result.lists = (Node**)malloc(result.count * sizeof(Node*));
    if (!result.lists) {
        result.count = 0;
        return result;
    }

    current = head;
    for (size_t i = 0; i < result.count; i++) {
        result.lists[i] = current;
        Node* prev = NULL;
        for (size_t j = 0; j < n && current != NULL; j++) {
            prev = current;
            current = current->next;
        }
        if (prev) {
            prev->next = NULL;
        }
    }

    return result;
}

void print_list(const Node* head) {
    const Node* current = head;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    Node* head = NULL;
    Node** tail = &head;

    for (int i = 1; i <= 10; i++) {
        Node* new_node = create_node(i);
        if (!new_node) {
            free_list(head);
            return EXIT_FAILURE;
        }
        *tail = new_node;
        tail = &new_node->next;
    }

    ListArray splitted = split_list(head, 3);
    if (!splitted.lists && head != NULL) {
        free_list(head);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < splitted.count; i++) {
        print_list(splitted.lists[i]);
        free_list(splitted.lists[i]);
    }

    if (splitted.lists) {
        free(splitted.lists);
    }

    return EXIT_SUCCESS;
}