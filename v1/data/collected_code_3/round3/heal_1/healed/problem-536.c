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
    struct Node* head = (struct Node*)malloc(sizeof(struct Node));
    struct Node* second = (struct Node*)malloc(sizeof(struct Node));
    struct Node* third = (struct Node*)malloc(sizeof(struct Node));

    if (head == NULL || second == NULL || third == NULL) {
        printf("Memory not allocated.\n");
        return -1;
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
    head = NULL;
    free(second);
    second = NULL;
    free(third);
    third = NULL;

    return 0;
}