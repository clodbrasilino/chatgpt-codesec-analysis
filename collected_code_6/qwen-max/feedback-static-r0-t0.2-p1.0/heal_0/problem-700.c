#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

int countInRange(Node *head, int lower, int upper) {
    int count = 0;
    for (Node *current = head; current != NULL; current = current->next) {
        if (current->value >= lower && current->value <= upper) {
            count++;
        }
    }
    return count;
}

int main() {
    Node *head = NULL;
    Node *second = NULL;
    Node *third = NULL;

    head = (Node *)malloc(sizeof(Node));
    second = (Node *)malloc(sizeof(Node));
    third = (Node *)malloc(sizeof(Node));

    head->value = 5;
    head->next = second;

    second->value = 10;
    second->next = third;

    third->value = 15;
    third->next = NULL;

    int lower = 6;
    int upper = 14;

    int result = countInRange(head, lower, upper);
    printf("Number of elements in range: %d\n", result);

    free(head);
    free(second);
    free(third);

    return 0;
}