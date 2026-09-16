#include <stdio.h>
#include <stdlib.h>

struct IntNode {
    int value;
    struct IntNode *next;
};

struct ListNode {
    struct IntNode *head;
    struct ListNode *next;
};

static struct IntNode *createIntNode(int value)
{
    struct IntNode *node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }
    node->value = value;
    node->next = NULL;
    return node;
}

static struct ListNode *createListNode(void)
{
    struct ListNode *node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }
    node->head = NULL;
    node->next = NULL;
    return node;
}

static int appendInt(struct ListNode *list, int value)
{
    struct IntNode *node;
    struct IntNode *cur;

    if (list == NULL) {
        return -1;
    }
    node = createIntNode(value);
    if (node == NULL) {
        return -1;
    }
    if (list->head == NULL) {
        list->head = node;
        return 0;
    }
    cur = list->head;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = node;
    return 0;
}

static void freeIntList(struct IntNode *head)
{
    while (head != NULL) {
        struct IntNode *tmp = head;
        head = head->next;
        free(tmp);
    }
}

static void freeListOfLists(struct ListNode *head)
{
    while (head != NULL) {
        struct ListNode *tmp = head;
        head = head->next;
        freeIntList(tmp->head);
        free(tmp);
    }
}

static struct ListNode *removeEmptyLists(struct ListNode *head)
{
    struct ListNode *cur = head;
    struct ListNode *prev = NULL;

    while (cur != NULL) {
        if (cur->head == NULL) {
            struct ListNode *toRemove = cur;
            if (prev == NULL) {
                head = cur->next;
            } else {
                prev->next = cur->next;
            }
            cur = cur->next;
            free(toRemove);
        } else {
            prev = cur;
            cur = cur->next;
        }
    }
    return head;
}

static void printListOfLists(const struct ListNode *head)
{
    const struct ListNode *cur = head;

    printf("[");
    while (cur != NULL) {
        const struct IntNode *inner = cur->head;
        printf("[");
        while (inner != NULL) {
            printf("%d", inner->value);
            if (inner->next != NULL) {
                printf(", ");
            }
            inner = inner->next;
        }
        printf("]");
        if (cur->next != NULL) {
            printf(", ");
        }
        cur = cur->next;
    }
    printf("]\n");
}

int main(void)
{
    struct ListNode *head = NULL;
    struct ListNode *tail = NULL;
    size_t i;
    int status = EXIT_SUCCESS;

    for (i = 0; i < 5; i++) {
        struct ListNode *node = createListNode();
        if (node == NULL) {
            fprintf(stderr, "Allocation failure\n");
            freeListOfLists(head);
            return EXIT_FAILURE;
        }
        if (head == NULL) {
            head = node;
        } else {
            tail->next = node;
        }
        tail = node;
    }

    if (appendInt(head, 1) != 0 ||
        appendInt(head, 2) != 0 ||
        appendInt(head->next->next, 3) != 0 ||
        appendInt(head->next->next->next->next, 4) != 0 ||
        appendInt(head->next->next->next->next, 5) != 0) {
        fprintf(stderr, "Allocation failure\n");
        freeListOfLists(head);
        return EXIT_FAILURE;
    }

    printf("Before: ");
    printListOfLists(head);

    head = removeEmptyLists(head);

    printf("After:  ");
    printListOfLists(head);

    freeListOfLists(head);
    return status;
}