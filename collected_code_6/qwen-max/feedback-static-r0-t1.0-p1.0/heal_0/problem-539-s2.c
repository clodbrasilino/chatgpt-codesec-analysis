#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node* create_node(int value) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
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
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int power(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

void map_powers(Node *bases, int index, Node **result_list) {
    if (bases == NULL) {
        return;
    }
    Node *current = bases;
    while (current != NULL) {
        append_to_list(result_list, power(current->value, index));
        current = current->next;
        index++;
    }
}

int main() {
    Node *bases = NULL;
    append_to_list(&bases, 2);
    append_to_list(&bases, 3);
    append_to_list(&bases, 4);

    Node *result_list = NULL;
    map_powers(bases, 1, &result_list);

    Node *current = result_list;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }

    free_list(bases);
    free_list(result_list);
    return 0;
}