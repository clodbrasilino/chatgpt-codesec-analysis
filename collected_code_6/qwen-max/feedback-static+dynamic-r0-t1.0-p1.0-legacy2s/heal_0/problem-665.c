#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

Node* create_node(int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void add_to_list(Node** head, int value) {
    Node* new_node = create_node(value);
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void shift_first_element_to_end(Node** head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }

    Node* first = *head;
    Node* prev = *head;
    while (prev->next != NULL) {
        if (prev->next->next == NULL) {
            break;
        }
        prev = prev->next;
    }

    *head = (*head)->next;
    prev->next = first;
    first->next = NULL;
}

void print_list(Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->value);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    Node* list = NULL;
    add_to_list(&list, 10);
    add_to_list(&list, 20);
    add_to_list(&list, 30);
    add_to_list(&list, 40);

    printf("Original list: ");
    print_list(list);

    shift_first_element_to_end(&list);

    printf("List after shifting first element to end: ");
    print_list(list);

    return 0;
}