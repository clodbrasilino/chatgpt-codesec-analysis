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

Node* extract_elements(Node *head, int start, int count) {
    if (head == NULL || count <= 0) {
        return NULL;
    }

    Node *dummy = create_node(0);
    if (dummy == NULL) {
        return NULL;
    }
    Node *tail = dummy;

    Node *current = head;
    for (int i = 0; i < start && current != NULL; ++i) {
        current = current->next;
    }

    for (int i = 0; i < count && current != NULL; ++i) {
        Node *new_node = create_node(current->value);
        if (new_node == NULL) {
            free_list(dummy->next);
            free(dummy);
            return NULL;
        }
        tail->next = new_node;
        tail = new_node;
        current = current->next;
    }

    return dummy->next;
}

int main() {
    Node *head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);
    head->next->next->next = create_node(4);
    head->next->next->next->next = create_node(5);

    Node *extracted = extract_elements(head, 1, 3);

    Node *current = extracted;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");

    free_list(head);
    free_list(extracted);

    return 0;
}