#include <stdbool.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

bool haveCommonElement(struct ListNode *list1, struct ListNode *list2) {
    struct ListNode *current1 = list1;
    struct ListNode *current2;

    while (current1 != NULL) {
        current2 = list2;
        while (current2 != NULL) {
            if (current1->val == current2->val) {
                return true;
            }
            current2 = current2->next;
        }
        current1 = current1->next;
    }

    return false;
}

struct ListNode *createNode(int val) {
    struct ListNode *newNode = (struct ListNode *)malloc(sizeof(struct ListNode));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

void freeList(struct ListNode *head) {
    struct ListNode *current = head;
    struct ListNode *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    struct ListNode *list1 = createNode(1);
    list1->next = createNode(2);
    list1->next->next = createNode(3);

    struct ListNode *list2 = createNode(4);
    list2->next = createNode(5);
    list2->next->next = createNode(3);

    bool result = haveCommonElement(list1, list2);

    freeList(list1);
    freeList(list2);

    return result ? 0 : 1;
}