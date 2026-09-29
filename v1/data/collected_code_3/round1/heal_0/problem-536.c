#include <stdio.h>

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
    struct Node* head = NULL;
    struct Node* second = NULL;
    struct Node* third = NULL;

    head = (struct Node*)malloc(sizeof(struct Node));
    second = (struct Node*)malloc(sizeof(struct Node));
    third = (struct Node*)malloc(sizeof(struct Node));

    head->data = 1;
    head->next = second;

    second->data = 2;
    second->next = third;

    third->data = 3;
    third->next = NULL;

    struct Node* nthNode = selectNth(head, 2);
    if (nthNode != NULL)
        printf("The nth node is: %d\n", nthNode->data);
    else
        printf("The nth node does not exist.\n");

    free(head);
    free(second);
    free(third);

    return 0;
}