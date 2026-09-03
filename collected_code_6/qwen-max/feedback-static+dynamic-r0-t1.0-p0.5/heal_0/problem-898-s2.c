#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node* create_node(int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void append_node(Node **head, int value) {
    Node *new_node = create_node(value);
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

Node* extract_elements(Node *head, int start, int count) {
    if (head == NULL || count <= 0) {
        return NULL;
    }

    Node *dummy = (Node *)malloc(sizeof(Node));
    dummy->next = head;
    Node *prev = dummy;
    for (int i = 0; i < start && prev->next != NULL; ++i) {
        prev = prev->next;
    }

    Node *extracted_head = prev->next;
    Node *current = extracted_head;
    for (int i = 1; i < count && current != NULL && current->next != NULL; ++i) {
        current = current->next;
    }

    if (current != NULL) {
        prev->next = current->next;
        current->next = NULL;
    } else {
        prev->next = NULL;
    }

    Node *result = dummy->next;
    free(dummy);
    return extracted_head;
}

void print_list(Node *head) {
    while (head != NULL) {
        printf("%d -> ", head->value);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    Node *head = NULL;
    append_node(&head, 1);
    append_node(&head, 2);
    append_node(&head, 3);
    append_node(&head, 4);
    append_node(&head, 5);

    printf("Original list: ");
    print_list(head);

    Node *extracted = extract_elements(head, 1, 3);
    printf("Extracted list: ");
    print_list(extracted);

    printf("Remaining list: ");
    print_list(head);

    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }

    while (extracted != NULL) {
        Node *temp = extracted;
        extracted = extracted->next;
        free(temp);
    }

    return 0;
}