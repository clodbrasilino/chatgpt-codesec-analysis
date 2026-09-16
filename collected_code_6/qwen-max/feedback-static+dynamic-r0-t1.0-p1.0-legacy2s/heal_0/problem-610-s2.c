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

void insert_at_end(Node** head, int data) {
    Node* new_node = create_node(data);
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
}

Node* remove_kth_element(Node* head, int k) {
    if (k <= 0 || head == NULL) {
        return head;
    }

    Node* dummy = (Node*)malloc(sizeof(Node));
    if (dummy == NULL) {
        return head;
    }
    dummy->next = head;

    Node* first = dummy;
    for (int i = 0; i < k && first != NULL; i++) {
        first = first->next;
    }

    if (first == NULL) {
        free(dummy);
        return head;
    }

    Node* second = dummy;
    while (first->next != NULL) {
        first = first->next;
        second = second->next;
    }

    Node* to_delete = second->next;
    second->next = second->next->next;
    free(to_delete);

    Node* new_head = dummy->next;
    free(dummy);
    return new_head;
}

void print_list(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    Node* head = NULL;
    insert_at_end(&head, 10);
    insert_at_end(&head, 20);
    insert_at_end(&head, 30);
    insert_at_end(&head, 40);
    insert_at_end(&head, 50);

    printf("Original List: ");
    print_list(head);

    head = remove_kth_element(head, 3);

    printf("List after removing 3rd element: ");
    print_list(head);

    return 0;
}