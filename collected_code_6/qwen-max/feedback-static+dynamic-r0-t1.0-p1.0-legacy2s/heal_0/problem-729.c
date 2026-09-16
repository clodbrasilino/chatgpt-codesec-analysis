#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_node(int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

void append_node(Node** head, int value) {
    Node* new_node = create_node(value);
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

Node* add_lists(Node* list1, Node* list2) {
    Node* result = NULL;
    int carry = 0;
    while (list1 || list2 || carry) {
        int sum = (list1 ? list1->data : 0) + (list2 ? list2->data : 0) + carry;
        carry = sum / 10;
        append_node(&result, sum % 10);
        if (list1) list1 = list1->next;
        if (list2) list2 = list2->next;
    }
    return result;
}

void free_list(Node* head) {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    Node* list1 = NULL;
    append_node(&list1, 2);
    append_node(&list1, 4);
    append_node(&list1, 3);

    Node* list2 = NULL;
    append_node(&list2, 5);
    append_node(&list2, 6);
    append_node(&list2, 4);

    Node* result = add_lists(list1, list2);

    Node* temp = result;
    while (temp) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");

    free_list(list1);
    free_list(list2);
    free_list(result);

    return 0;
}