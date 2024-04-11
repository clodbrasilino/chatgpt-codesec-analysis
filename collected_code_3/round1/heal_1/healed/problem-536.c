#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* selectNth(struct Node* head, int n) {
    int count = 0;
    struct Node* temp = head;
    while (temp != NULL) {
        if (count == n)
            return temp;
        count++;
        temp = temp->next;
    }
    return NULL;
}

int main() {
    struct Node* head = malloc(sizeof(struct Node));
    struct Node* second = NULL;
    struct Node* third = NULL;

    if(head == NULL)
        return 1;

    head->data = 1;

    second = malloc(sizeof(struct Node));
    if(second == NULL) {
        free(head);
        return 1;
    }

    head->next = second;
    second->data = 2;

    third = malloc(sizeof(struct Node));
    if(third == NULL) {
        free(head);
        free(second);
        return 1;
    }

    second->next = third;
    third->data = 3;
    third->next = NULL;

    struct Node* nthNode = selectNth(head, 2);
    if (nthNode != NULL)
        printf("The nth node is: %d\n", nthNode->data);
    else
        printf("The nth node does not exist.\n");

    free(head);
    head = NULL;
    free(second);
    second = NULL;
    free(third);
    third = NULL;

    return 0;
}