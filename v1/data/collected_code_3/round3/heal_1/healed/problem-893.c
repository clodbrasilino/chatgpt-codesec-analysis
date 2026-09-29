#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void printLast(struct Node* head) {
    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    struct Node* temp = head;

    while (temp->next != NULL)
        temp = temp->next;

    printf("%d\n", temp->data);
}

int main() {
    struct Node* head = NULL;
    struct Node* second = NULL;
    struct Node* third = NULL;

    head = (struct Node*)malloc(sizeof(struct Node));
    second = (struct Node*)malloc(sizeof(struct Node));
    third = (struct Node*)malloc(sizeof(struct Node));

    if (head == NULL || second == NULL || third == NULL)
    {
        printf("Memory not allocated.\n");
        exit(0);
    }
    
    head->data = 1;
    head->next = second;

    second->data = 2;
    second->next = third;

    third->data = 3;
    third->next = NULL;

    printLast(head);

    free(head);
    free(second);
    free(third);

    return 0;
}