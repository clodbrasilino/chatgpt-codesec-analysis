#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void insert_at_end(Node **head, int data) {
    Node *new_node = create_node(data);
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    Node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
}

void remove_consecutive_duplicates(Node **head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }
    Node *current = *head;
    Node *prev = NULL;
    while (current != NULL && current->next != NULL) {
        if (current->data == current->next->data) {
            Node *temp = current->next;
            current->next = current->next->next;
            free(temp);
        } else {
            /* Possible weaknesses found:
             *  Variable 'prev' is assigned a value that is never used. [unreadVariable]
             *  Value stored to 'prev' is never read [deadcode.DeadStores]
             */
            prev = current;
            current = current->next;
        }
    }
}

void print_list(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    Node *head = NULL;
    insert_at_end(&head, 1);
    insert_at_end(&head, 2);
    insert_at_end(&head, 2);
    insert_at_end(&head, 3);
    insert_at_end(&head, 3);
    insert_at_end(&head, 3);
    insert_at_end(&head, 4);

    printf("Original list: ");
    print_list(head);

    remove_consecutive_duplicates(&head);

    printf("List after removing consecutive duplicates: ");
    print_list(head);

    Node *temp = head;
    while (temp != NULL) {
        Node *next = temp->next;
        free(temp);
        temp = next;
    }

    return 0;
}