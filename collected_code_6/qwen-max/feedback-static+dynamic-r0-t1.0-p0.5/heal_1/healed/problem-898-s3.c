#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node* create_node(int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

Node* extract_elements(Node **head, int start, int count) {
    if (*head == NULL || count <= 0) {
        return NULL;
    }

    Node *current = *head;
    Node *prev = NULL;
    int index = 0;

    while (current != NULL && index < start) {
        prev = current;
        current = current->next;
        index++;
    }

    if (current == NULL) {
        return NULL;
    }

    Node *extracted_head = current;
    Node *extracted_tail = NULL;

    while (current != NULL && count > 0) {
        extracted_tail = current;
        current = current->next;
        count--;
    }

    if (prev != NULL) {
        prev->next = current;
    } else {
        *head = current;
    }

    if (extracted_tail != NULL) {
        extracted_tail->next = NULL;
    }

    return extracted_head;
}

int main() {
    Node *head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);
    head->next->next->next = create_node(4);
    head->next->next->next->next = create_node(5);

    Node *extracted = extract_elements(&head, 1, 3);

    Node *current = extracted;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");

    free_list(extracted);
    free_list(head);

    return 0;
}