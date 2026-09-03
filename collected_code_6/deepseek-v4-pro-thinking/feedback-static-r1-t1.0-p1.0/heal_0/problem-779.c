#include <stdio.h>
#include <stddef.h>

typedef struct IntNode {
    int value;
    struct IntNode *next;
} IntNode;

typedef struct ListNode {
    IntNode *list;
    struct ListNode *next;
} ListNode;

int intListEqual(const IntNode *a, const IntNode *b) {
    while (a != NULL && b != NULL) {
        if (a->value != b->value) {
            return 0;
        }
        a = a->next;
        b = b->next;
    }
    return a == NULL && b == NULL;
}

int countUniqueLists(const ListNode *head) {
    int count = 0;
    const ListNode *current = head;

    while (current != NULL) {
        const ListNode *previous = head;
        int unique = 1;

        while (previous != current) {
            if (intListEqual(previous->list, current->list)) {
                unique = 0;
                break;
            }
            previous = previous->next;
        }

        if (unique) {
            count++;
        }

        current = current->next;
    }

    return count;
}

int main(void) {
    IntNode n11 = {1, NULL};
    IntNode n12 = {2, NULL};
    IntNode n13 = {3, NULL};
    IntNode n21 = {1, NULL};
    IntNode n22 = {2, NULL};
    IntNode n23 = {3, NULL};
    IntNode n31 = {4, NULL};
    IntNode n32 = {5, NULL};

    n11.next = &n12;
    n12.next = &n13;

    n21.next = &n22;
    n22.next = &n23;

    n31.next = &n32;

    ListNode node1 = {&n11, NULL};
    ListNode node2 = {&n21, NULL};
    ListNode node3 = {&n31, NULL};

    node1.next = &node2;
    node2.next = &node3;

    printf("%d\n", countUniqueLists(&node1));

    return 0;
}