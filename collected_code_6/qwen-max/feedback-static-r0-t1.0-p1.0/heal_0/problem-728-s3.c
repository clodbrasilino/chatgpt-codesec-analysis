#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

Node* create_node(int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void append_node(Node** head, int value) {
    if (*head == NULL) {
        *head = create_node(value);
    } else {
        Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = create_node(value);
    }
}

int sum_lists(Node* list1, Node* list2) {
    int sum = 0;
    while (list1 != NULL && list2 != NULL) {
        sum += list1->value + list2->value;
        list1 = list1->next;
        list2 = list2->next;
    }
    return sum;
}

void destroy_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    Node* list1 = NULL;
    append_node(&list1, 1);
    append_node(&list1, 2);
    append_node(&list1, 3);

    Node* list2 = NULL;
    append_node(&list2, 4);
    append_node(&list2, 5);
    append_node(&list2, 6);

    int result = sum_lists(list1, list2);
    printf("Sum: %d\n", result);

    destroy_list(list1);
    destroy_list(list2);

    return 0;
}