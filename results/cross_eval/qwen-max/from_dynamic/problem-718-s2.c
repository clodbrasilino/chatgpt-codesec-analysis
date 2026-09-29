#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void free_list(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

Node* alternate_elements(Node* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    Node* new_head = NULL;
    Node* new_tail = NULL;
    Node* current = head;

    while (current != NULL && current->next != NULL) {
        if (new_head == NULL) {
            new_head = create_node(current->data);
            new_tail = new_head;
        } else {
            new_tail->next = create_node(current->data);
            new_tail = new_tail->next;
        }
        current = current->next->next;
    }

    return new_head;
}

int main() {
    Node* head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);
    head->next->next->next = create_node(4);
    head->next->next->next->next = create_node(5);

    Node* alternate = alternate_elements(head);

    Node* temp = alternate;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    free_list(head);
    free_list(alternate);

    return 0;
}