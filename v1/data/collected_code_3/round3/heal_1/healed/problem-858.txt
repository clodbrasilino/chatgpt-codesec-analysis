#include <stdio.h>
#include <stdlib.h>

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
    struct List* head = (struct List*)malloc(sizeof(struct List));
    struct List* second = (struct List*)malloc(sizeof(struct List));
    struct List* third = (struct List*)malloc(sizeof(struct List));

    if(!head || !second || !third){
        fprintf(stderr, "Memory allocation error\n");
        return 1;
    }
    
    head->next = second;
    second->next = third;
    third->next = NULL;

    printf("%d\n", countSquare(head));

    free(head);
    free(second);
    free(third);

    return 0;
}