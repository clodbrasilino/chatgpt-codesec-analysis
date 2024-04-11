#include <stdio.h>

struct Node {
    int data;
    struct Node* next;
};

int countElementsInRange(struct Node* head, int min, int max) {
    struct Node* current = head;
    int count = 0;

    while (current != NULL) {
        if (current->data >= min && current->data <= max) {
            count++;
        }
        current = current->next;
    }

    return count;
}

int main() {
    struct Node* head = NULL;
    struct Node* second = NULL;
    struct Node* third = NULL;

    head = (struct Node*)malloc(sizeof(struct Node));
    second = (struct Node*)malloc(sizeof(struct Node));
    third = (struct Node*)malloc(sizeof(struct Node));

    head->data = 1;
    head->next = second;

    second->data = 5;
    second->next = third;

    third->data = 10;
    third->next = NULL;

    printf("Number of elements in range 1 to 10: %d\n", countElementsInRange(head, 1, 10));

    free(head);
    free(second);
    free(third);

    return 0;
}