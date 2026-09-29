#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int value;
    struct ListNode *next;
} ListNode;

ListNode* createNode(int value) {
    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void freeList(ListNode *head) {
    while (head != NULL) {
        ListNode *temp = head;
        head = head->next;
        free(temp);
    }
}

ListNode* subtractLists(ListNode *list1, ListNode *list2) {
    if (list1 == NULL || list2 == NULL) {
        return NULL;
    }

    ListNode *resultHead = NULL;
    ListNode **current = &resultHead;

    for (ListNode *ptr1 = list1; ptr1 != NULL; ptr1 = ptr1->next) {
        int found = 0;
        for (ListNode *ptr2 = list2; ptr2 != NULL && !found; ptr2 = ptr2->next) {
            if (ptr1->value == ptr2->value) {
                found = 1;
            }
        }
        if (!found) {
            *current = createNode(ptr1->value);
            if (*current == NULL) {
                return NULL;
            }
            current = &(*current)->next;
        }
    }

    return resultHead;
}

int main() {
    ListNode *list1 = createNode(1);
    list1->next = createNode(2);
    list1->next->next = createNode(3);

    ListNode *list2 = createNode(2);
    list2->next = createNode(4);

    ListNode *result = subtractLists(list1, list2);

    for (ListNode *ptr = result; ptr != NULL; ptr = ptr->next) {
        printf("%d ", ptr->value);
    }
    printf("\n");

    freeList(list1);
    freeList(list2);
    freeList(result);

    return 0;
}