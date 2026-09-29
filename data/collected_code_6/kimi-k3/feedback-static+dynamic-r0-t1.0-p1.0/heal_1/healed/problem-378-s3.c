#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

void shiftLastToFirst(struct Node **head)
{
    struct Node *last;
    struct Node *secondLast;

    if (head == NULL || *head == NULL || (*head)->next == NULL) {
        return;
    }

    secondLast = NULL;
    last = *head;

    while (last->next != NULL) {
        secondLast = last;
        last = last->next;
    }

    if (secondLast != NULL) {
        secondLast->next = NULL;
        last->next = *head;
        *head = last;
    }
}

struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void appendNode(struct Node **head, int data)
{
    struct Node *newNode = createNode(data);
    struct Node *temp;

    if (newNode == NULL) {
        return;
    }

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void printList(struct Node *head)
{
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void freeList(struct Node **head)
{
    if (head == NULL) {
        return;
    }

    while (*head != NULL) {
        struct Node *temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

int main(void)
{
    struct Node *head = NULL;

    appendNode(&head, 1);
    appendNode(&head, 2);
    appendNode(&head, 3);
    appendNode(&head, 4);
    appendNode(&head, 5);

    printf("Original list: ");
    printList(head);

    shiftLastToFirst(&head);

    printf("List after shifting last element to first: ");
    printList(head);

    freeList(&head);

    return 0;
}