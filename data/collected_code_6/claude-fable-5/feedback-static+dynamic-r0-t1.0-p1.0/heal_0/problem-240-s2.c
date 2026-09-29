#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *createNode(int value)
{
    struct Node *node = malloc(sizeof(struct Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = value;
    node->next = NULL;
    return node;
}

int appendNode(struct Node **head, int value)
{
    struct Node *node;
    struct Node *current;

    if (head == NULL) {
        return -1;
    }

    node = createNode(value);
    if (node == NULL) {
        return -1;
    }

    if (*head == NULL) {
        *head = node;
        return 0;
    }

    current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
    return 0;
}

int replaceLastWithList(struct Node **head, struct Node **replacement)
{
    struct Node *current;
    struct Node *prev;

    if (head == NULL || *head == NULL || replacement == NULL) {
        return -1;
    }

    prev = NULL;
    current = *head;
    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }

    free(current);

    if (prev == NULL) {
        *head = *replacement;
    } else {
        prev->next = *replacement;
    }

    *replacement = NULL;
    return 0;
}

void printList(const struct Node *head)
{
    const struct Node *current = head;

    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void freeList(struct Node **head)
{
    struct Node *current;
    struct Node *next;

    if (head == NULL) {
        return;
    }

    current = *head;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

int main(void)
{
    struct Node *list1 = NULL;
    struct Node *list2 = NULL;
    int i;

    for (i = 1; i <= 4; i++) {
        if (appendNode(&list1, i) != 0) {
            freeList(&list1);
            fprintf(stderr, "Allocation failure\n");
            return EXIT_FAILURE;
        }
    }

    for (i = 10; i <= 30; i += 10) {
        if (appendNode(&list2, i) != 0) {
            freeList(&list1);
            freeList(&list2);
            fprintf(stderr, "Allocation failure\n");
            return EXIT_FAILURE;
        }
    }

    printf("List 1: ");
    printList(list1);
    printf("List 2: ");
    printList(list2);

    if (replaceLastWithList(&list1, &list2) != 0) {
        freeList(&list1);
        freeList(&list2);
        fprintf(stderr, "Replacement failed\n");
        return EXIT_FAILURE;
    }

    printf("Result: ");
    printList(list1);

    freeList(&list1);
    return EXIT_SUCCESS;
}