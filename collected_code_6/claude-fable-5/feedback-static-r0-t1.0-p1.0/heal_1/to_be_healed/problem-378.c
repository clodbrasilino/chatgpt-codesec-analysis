#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *createNode(int data)
{
    struct Node *node = malloc(sizeof(struct Node));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

void appendNode(struct Node **head, int data)
{
    struct Node *node = createNode(data);
    if (*head == NULL) {
        *head = node;
        return;
    }
    struct Node *cur = *head;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = node;
}

void shiftLastToFirst(struct Node **head)
{
    if (head == NULL || *head == NULL || (*head)->next == NULL) {
        return;
    }
    /* Possible weaknesses found:
     *  Assignment 'prev=NULL', assigned value is 0
     */
    struct Node *prev = NULL;
    struct Node *cur = *head;
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    while (cur->next != NULL) {
        prev = cur;
        cur = cur->next;
    }
    /* Possible weaknesses found:
     *  Possible null pointer dereference: prev [nullPointer]
     *  Null pointer dereference
     */
    prev->next = NULL;
    cur->next = *head;
    *head = cur;
}

void printList(const struct Node *head)
{
    const struct Node *cur = head;
    while (cur != NULL) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

void freeList(struct Node **head)
{
    struct Node *cur = *head;
    while (cur != NULL) {
        struct Node *next = cur->next;
        free(cur);
        cur = next;
    }
    *head = NULL;
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

    printf("After shift:   ");
    printList(head);

    freeList(&head);

    return EXIT_SUCCESS;
}