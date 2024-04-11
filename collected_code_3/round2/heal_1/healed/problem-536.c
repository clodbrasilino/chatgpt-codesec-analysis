#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* nthItem(struct Node* head, int n) {
    struct Node* temp = head;
    int count = 0;
    while (temp != NULL) {
        if (count == n)
            return temp;
        count++;
        temp = temp->next;
    }
    return NULL;
}

int main() {
    struct Node* head = NULL;
    struct Node* second = NULL;
    struct Node* third = NULL;

    head = (struct Node*)malloc(sizeof(struct Node));
    second = (struct Node*)malloc(sizeof(struct Node));
    third = (struct Node*)malloc(sizeof(struct Node));

    if (head == NULL || second == NULL || third == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    } 

    head->data = 1;
    head->next = second;

    second->data = 2;
    second->next = third;

    third->data = 3;
    third->next = NULL;

    struct Node* nth = nthItem(head, 2);
    if (nth != NULL)
        printf("The nth item is %d\n", nth->data);
    else
        printf("The nth item does not exist\n");

    free(head);
    free(second);
    free(third);

    return 0;
}