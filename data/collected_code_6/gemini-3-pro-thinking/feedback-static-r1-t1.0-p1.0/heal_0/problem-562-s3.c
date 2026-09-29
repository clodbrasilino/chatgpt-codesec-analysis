#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

size_t get_list_length(const Node* head) {
    size_t length = 0;
    const Node* current = head;
    
    while (current != NULL) {
        length++;
        current = current->next;
    }
    
    return length;
}

size_t get_max_sublist_length(Node** sublists, size_t count) {
    if (sublists == NULL || count == 0) {
        return 0;
    }

    size_t max_length = 0;

    for (size_t i = 0; i < count; i++) {
        size_t current_length = get_list_length(sublists[i]);
        if (current_length > max_length) {
            max_length = current_length;
        }
    }

    return max_length;
}

int append_node(Node** head, int data) {
    if (head == NULL) {
        return 0;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return 0;
    }

    new_node->data = data;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }

    return 1;
}

void free_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* next_node = current->next;
        free(current);
        current = next_node;
    }
}

int main(void) {
    size_t count = 3;
    Node** sublists = (Node**)calloc(count, sizeof(Node*));
    
    if (sublists == NULL) {
        return EXIT_FAILURE;
    }

    append_node(&sublists[0], 10);

    append_node(&sublists[1], 20);
    append_node(&sublists[1], 30);

    append_node(&sublists[2], 40);
    append_node(&sublists[2], 50);
    append_node(&sublists[2], 60);

    size_t max_len = get_max_sublist_length(sublists, count);

    printf("%zu\n", max_len);

    for (size_t i = 0; i < count; i++) {
        free_list(sublists[i]);
    }
    free(sublists);

    return EXIT_SUCCESS;
}