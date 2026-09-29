#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

int insert_before_each(Node** head, int insert_value) {
    if (!head) {
        return -1;
    }

    Node* current = *head;
    Node* prev = NULL;

    while (current != NULL) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        if (!new_node) {
            return -1;
        }

        new_node->data = insert_value;
        new_node->next = current;

        if (prev == NULL) {
            *head = new_node;
        } else {
            prev->next = new_node;
        }

        prev = current;
        current = current->next;
    }

    return 0;
}

int push_back(Node** head, int data) {
    if (!head) {
        return -1;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        return -1;
    }

    new_node->data = data;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return 0;
    }

    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = new_node;
    return 0;
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
        Node* next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    Node* head = NULL;

    if (push_back(&head, 1) == 0 &&
        push_back(&head, 2) == 0 &&
        push_back(&head, 3) == 0) {
        
        print_list(head);
        
        if (insert_before_each(&head, 0) == 0) {
            print_list(head);
        }
    }

    free_list(head);
    return 0;
}