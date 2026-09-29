#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node {
    double data;
    struct Node *next;
} Node;

Node *create_node(double data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void append_node(Node **head, double data) {
    Node *new_node = create_node(data);
    if (new_node == NULL) {
        return;
    }
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

Node *map_power(int *bases, int size, int number) {
    if (bases == NULL || size <= 0) {
        return NULL;
    }
    Node *head = NULL;
    for (int i = 0; i < size; i++) {
        double result = pow((double)number, (double)bases[i]);
        append_node(&head, result);
    }
    return head;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%.2f ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    int bases[] = {0, 1, 2, 3, 4};
    int size = sizeof(bases) / sizeof(bases[0]);
    int number = 2;

    Node *result = map_power(bases, size, number);
    if (result == NULL) {
        fprintf(stderr, "Failed to create list\n");
        return EXIT_FAILURE;
    }

    print_list(result);
    free_list(result);

    return EXIT_SUCCESS;
}