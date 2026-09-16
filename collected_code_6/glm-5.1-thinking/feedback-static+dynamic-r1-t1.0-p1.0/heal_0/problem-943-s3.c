#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *createNode(int data) {
    struct Node *node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

void freeList(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        struct Node *next = current->next;
        free(current);
        current = next;
    }
}

struct Node *insertEnd(struct Node *head, int data) {
    struct Node *newNode = createNode(data);
    if (newNode == NULL) {
        freeList(head);
        return NULL;
    }
    if (head == NULL) {
        return newNode;
    }
    struct Node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    return head;
}

struct Node *mergeSortedLists(struct Node *l1, struct Node *l2) {
    struct Node dummy;
    struct Node *tail = &dummy;
    dummy.next = NULL;

    while (l1 != NULL && l2 != NULL) {
        if (l1->data <= l2->data) {
            struct Node *newNode = createNode(l1->data);
            if (newNode == NULL) {
                freeList(dummy.next);
                return NULL;
            }
            tail->next = newNode;
            tail = tail->next;
            l1 = l1->next;
        } else {
            struct Node *newNode = createNode(l2->data);
            if (newNode == NULL) {
                freeList(dummy.next);
                return NULL;
            }
            tail->next = newNode;
            tail = tail->next;
            l2 = l2->next;
        }
    }

    while (l1 != NULL) {
        struct Node *newNode = createNode(l1->data);
        if (newNode == NULL) {
            freeList(dummy.next);
            return NULL;
        }
        tail->next = newNode;
        tail = tail->next;
        l1 = l1->next;
    }

    while (l2 != NULL) {
        struct Node *newNode = createNode(l2->data);
        if (newNode == NULL) {
            freeList(dummy.next);
            return NULL;
        }
        tail->next = newNode;
        tail = tail->next;
        l2 = l2->next;
    }

    return dummy.next;
}

void printList(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    struct Node *list1 = NULL;
    struct Node *list2 = NULL;

    list1 = insertEnd(list1, 1);
    if (list1 != NULL) {
        list1 = insertEnd(list1, 3);
    }
    if (list1 != NULL) {
        list1 = insertEnd(list1, 5);
    }

    list2 = insertEnd(list2, 2);
    if (list2 != NULL) {
        list2 = insertEnd(list2, 4);
    }
    if (list2 != NULL) {
        list2 = insertEnd(list2, 6);
    }

    if (list1 == NULL || list2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        freeList(list1);
        freeList(list2);
        return EXIT_FAILURE;
    }

    struct Node *merged = mergeSortedLists(list1, list2);
    if (merged == NULL) {
        fprintf(stderr, "Memory allocation failed during merge\n");
        freeList(list1);
        freeList(list2);
        return EXIT_FAILURE;
    }

    printList(merged);

    freeList(list1);
    freeList(list2);
    freeList(merged);

    return EXIT_SUCCESS;
}