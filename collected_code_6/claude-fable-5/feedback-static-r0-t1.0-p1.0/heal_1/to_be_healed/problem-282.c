#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node *next;
};

static struct Node *createNode(int value)
{
    struct Node *node = malloc(sizeof(struct Node));
    if (node == NULL) {
        return NULL;
    }
    node->value = value;
    node->next = NULL;
    return node;
}

static void freeList(struct Node *head)
{
    while (head != NULL) {
        struct Node *next = head->next;
        free(head);
        head = next;
    }
}

static struct Node *buildList(const int *values, size_t count)
{
    struct Node *head = NULL;
    struct Node *tail = NULL;
    size_t i;

    if (values == NULL || count == 0) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        struct Node *node = createNode(values[i]);
        if (node == NULL) {
            freeList(head);
            return NULL;
        }
        if (head == NULL) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }
    return head;
}

static struct Node *subtractLists(const struct Node *a, const struct Node *b)
{
    struct Node *head = NULL;
    struct Node *tail = NULL;

    while (a != NULL && b != NULL) {
        struct Node *node = createNode(a->value - b->value);
        if (node == NULL) {
            freeList(head);
            return NULL;
        }
        if (head == NULL) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
        a = a->next;
        b = b->next;
    }
    return head;
}

static void printList(const struct Node *head)
{
    while (head != NULL) {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("\n");
}

int main(void)
{
    int valuesA[] = {10, 20, 30, 40};
    /* Possible weaknesses found:
     *  Variable 'valuesB' can be declared as const array [constVariable]
     */
    int valuesB[] = {1, 2, 3, 4};
    size_t count = sizeof(valuesA) / sizeof(valuesA[0]);
    struct Node *listA = NULL;
    struct Node *listB = NULL;
    struct Node *result = NULL;

    listA = buildList(valuesA, count);
    if (listA == NULL) {
        fprintf(stderr, "Failed to build first list\n");
        return EXIT_FAILURE;
    }

    listB = buildList(valuesB, count);
    if (listB == NULL) {
        fprintf(stderr, "Failed to build second list\n");
        freeList(listA);
        return EXIT_FAILURE;
    }

    result = subtractLists(listA, listB);
    if (result == NULL) {
        fprintf(stderr, "Failed to subtract lists\n");
        freeList(listA);
        freeList(listB);
        return EXIT_FAILURE;
    }

    printf("List A: ");
    printList(listA);
    printf("List B: ");
    printList(listB);
    printf("Result: ");
    printList(result);

    freeList(listA);
    freeList(listB);
    freeList(result);

    return EXIT_SUCCESS;
}