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

void freeList(struct Node *head)
{
    while (head != NULL) {
        struct Node *temp = head;
        head = head->next;
        free(temp);
    }
}

int appendNode(struct Node **head, struct Node **tail, int value)
{
    struct Node *node = createNode(value);
    if (node == NULL) {
        return -1;
    }
    if (*head == NULL) {
        *head = node;
        *tail = node;
    } else {
        (*tail)->next = node;
        *tail = node;
    }
    return 0;
}

struct Node *addLists(const struct Node *a, const struct Node *b)
{
    struct Node *head = NULL;
    struct Node *tail = NULL;

    while (a != NULL && b != NULL) {
        if (appendNode(&head, &tail, a->data + b->data) != 0) {
            freeList(head);
            return NULL;
        }
        a = a->next;
        b = b->next;
    }

    while (a != NULL) {
        if (appendNode(&head, &tail, a->data) != 0) {
            freeList(head);
            return NULL;
        }
        a = a->next;
    }

    while (b != NULL) {
        if (appendNode(&head, &tail, b->data) != 0) {
            freeList(head);
            return NULL;
        }
        b = b->next;
    }

    return head;
}

struct Node *buildList(const int *values, size_t count)
{
    struct Node *head = NULL;
    struct Node *tail = NULL;
    size_t i;

    for (i = 0; i < count; i++) {
        if (appendNode(&head, &tail, values[i]) != 0) {
            freeList(head);
            return NULL;
        }
    }
    return head;
}

void printList(const struct Node *head)
{
    while (head != NULL) {
        printf("%d", head->data);
        if (head->next != NULL) {
            printf(" -> ");
        }
        head = head->next;
    }
    printf("\n");
}

int main(void)
{
    int valuesA[] = {1, 2, 3, 4};
    int valuesB[] = {10, 20, 30};
    struct Node *listA = NULL;
    struct Node *listB = NULL;
    struct Node *sum = NULL;

    listA = buildList(valuesA, sizeof(valuesA) / sizeof(valuesA[0]));
    if (listA == NULL) {
        fprintf(stderr, "Failed to build list A\n");
        return EXIT_FAILURE;
    }

    listB = buildList(valuesB, sizeof(valuesB) / sizeof(valuesB[0]));
    if (listB == NULL) {
        fprintf(stderr, "Failed to build list B\n");
        freeList(listA);
        return EXIT_FAILURE;
    }

    sum = addLists(listA, listB);
    if (sum == NULL) {
        fprintf(stderr, "Failed to add lists\n");
        freeList(listA);
        freeList(listB);
        return EXIT_FAILURE;
    }

    printf("List A: ");
    printList(listA);
    printf("List B: ");
    printList(listB);
    printf("Sum:    ");
    printList(sum);

    freeList(listA);
    freeList(listB);
    freeList(sum);

    return EXIT_SUCCESS;
}