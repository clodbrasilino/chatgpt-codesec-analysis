#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

static struct Node *createNode(int value)
{
    struct Node *node = malloc(sizeof(struct Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = value;
    node->next = NULL;
    return node;
}

static int appendNode(struct Node **head, int value)
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

static int containsValue(const struct Node *head, int value)
{
    const struct Node *current = head;

    while (current != NULL) {
        if (current->data == value) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

static void removeElements(struct Node **head, const struct Node *filter)
{
    struct Node *current;
    struct Node *previous;

    if (head == NULL) {
        return;
    }

    current = *head;
    previous = NULL;

    while (current != NULL) {
        if (containsValue(filter, current->data)) {
            struct Node *toDelete = current;
            if (previous == NULL) {
                *head = current->next;
            } else {
                previous->next = current->next;
            }
            current = current->next;
            free(toDelete);
        } else {
            previous = current;
            current = current->next;
        }
    }
}

static void freeList(struct Node *head)
{
    struct Node *current = head;

    while (current != NULL) {
        struct Node *next = current->next;
        free(current);
        current = next;
    }
}

static void printList(const struct Node *head)
{
    const struct Node *current = head;

    while (current != NULL) {
        if (printf("%d ", current->data) < 0) {
            return;
        }
        current = current->next;
    }
    if (printf("\n") < 0) {
        return;
    }
}

int main(void)
{
    struct Node *mainList = NULL;
    struct Node *filterList = NULL;
    int mainValues[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int filterValues[] = {2, 4, 6, 8};
    size_t i;

    for (i = 0; i < sizeof(mainValues) / sizeof(mainValues[0]); i++) {
        if (appendNode(&mainList, mainValues[i]) != 0) {
            fprintf(stderr, "Memory allocation failed\n");
            freeList(mainList);
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < sizeof(filterValues) / sizeof(filterValues[0]); i++) {
        if (appendNode(&filterList, filterValues[i]) != 0) {
            fprintf(stderr, "Memory allocation failed\n");
            freeList(mainList);
            freeList(filterList);
            return EXIT_FAILURE;
        }
    }

    printf("Original list: ");
    printList(mainList);

    printf("Filter list: ");
    printList(filterList);

    removeElements(&mainList, filterList);

    printf("Result list: ");
    printList(mainList);

    freeList(mainList);
    freeList(filterList);

    return EXIT_SUCCESS;
}