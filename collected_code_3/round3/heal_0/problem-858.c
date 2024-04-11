#include <stdio.h>

struct Node {
    int data;
    struct Node* next;
};

struct List {
    struct Node* head;
    struct List* next;
};

int countSquare(struct List* head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count * count;
}

int main() {
    struct List* head = NULL;
    struct List* second = NULL;
    struct List* third = NULL;

    head = (struct List*)malloc(sizeof(struct List));
    second = (struct List*)malloc(sizeof(struct List));
    third = (struct List*)malloc(sizeof(struct List));

    head->next = second;
    second->next = third;
    third->next = NULL;

    printf("%d\n", countSquare(head));

    free(head);
    free(second);
    free(third);

    return 0;
}