#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node* next;
} Node;

Node* remove_even(Node* head) {
    Node* current = head;
    Node* prev = NULL;

    while (current != NULL) {
        if (current->value % 2 == 0) {
            if (prev != NULL) {
                prev->next = current->next;
                free(current);
                current = prev->next;
            } else {
                head = current->next;
                free(current);
                current = head;
            }
        } else {
            prev = current;
            current = current->next;
        }
    }
    return head;
}

Node* create_node(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    node->value = value;
    node->next = NULL;
    return node;
}

Node* append_node(Node* head, int value) {
    Node* new_node = create_node(value);
    if (head == NULL) {
        return new_node;
    }
    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
    return head;
}

void print_list(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->value);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    Node* head = NULL;
    head = append_node(head, 1);
    head = append_node(head, 2);
    head = append_node(head, 3);
    head = append_node(head, 4);
    head = append_node(head, 5);
    printf("Before: ");
    print_list(head);
    head = remove_even(head);
    printf("After: ");
    print_list(head);
    return 0;
}