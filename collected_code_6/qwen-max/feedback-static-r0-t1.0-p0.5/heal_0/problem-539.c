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

void append_to_list(Node **head, int value) {
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

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

int power(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; ++i) {
        result *= base;
    }
    return result;
}

Node* map_power(Node *bases, int index) {
    if (bases == NULL) {
        return NULL;
    }
    Node *result = NULL;
    Node *current = bases;
    int idx = 0;
    while (current != NULL) {
        append_to_list(&result, power(current->value, idx + index));
        current = current->next;
        idx++;
    }
    return result;
}

int main() {
    Node *bases = NULL;
    append_to_list(&bases, 2);
    append_to_list(&bases, 3);
    append_to_list(&bases, 4);

    Node *result = map_power(bases, 0);

    Node *current = result;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");

    free_list(bases);
    free_list(result);

    return 0;
}