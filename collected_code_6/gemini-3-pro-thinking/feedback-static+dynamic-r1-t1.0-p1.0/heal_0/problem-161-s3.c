#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

bool contains(const Node* head, int value) {
    const Node* current = head;
    while (current != NULL) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void append_node(Node** head, int data) {
    if (head == NULL) {
        return;
    }
    Node* new_node = create_node(data);
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

void remove_elements(Node** target_list, const Node* filter_list) {
    if (target_list == NULL || *target_list == NULL || filter_list == NULL) {
        return;
    }

    Node* current = *target_list;
    Node* prev = NULL;

    while (current != NULL) {
        if (contains(filter_list, current->data)) {
            Node* temp = current;
            if (prev == NULL) {
                *target_list = current->next;
            } else {
                prev->next = current->next;
            }
            current = current->next;
            free(temp);
        } else {
            prev = current;
            current = current->next;
        }
    }
}

void print_list(const Node* head) {
    const Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void free_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main(void) {
    Node* target_list = NULL;
    Node* filter_list = NULL;

    append_node(&target_list, 10);
    append_node(&target_list, 20);
    append_node(&target_list, 30);
    append_node(&target_list, 40);
    append_node(&target_list, 50);
    append_node(&target_list, 20);

    append_node(&filter_list, 20);
    append_node(&filter_list, 50);

    remove_elements(&target_list, filter_list);

    print_list(target_list);

    free_list(target_list);
    free_list(filter_list);

    return EXIT_SUCCESS;
}