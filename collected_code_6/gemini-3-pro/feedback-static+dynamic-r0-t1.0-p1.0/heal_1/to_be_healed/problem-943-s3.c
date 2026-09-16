#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    struct ListNode dummy;
    struct ListNode* tail = &dummy;
    dummy.next = NULL;

    while (list1 != NULL && list2 != NULL) {
        if (list1->val <= list2->val) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }

    if (list1 != NULL) {
        tail->next = list1;
    } else {
        tail->next = list2;
    }

    return dummy.next;
}

struct ListNode* createNode(int val) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (newNode != NULL) {
        newNode->val = val;
        newNode->next = NULL;
    }
    return newNode;
}

void freeList(struct ListNode* head) {
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    struct ListNode* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void printList(struct ListNode* head) {
    while (head != NULL) {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
}

int main() {
    struct ListNode* list1 = createNode(1);
    if (list1 == NULL) return 1;
    list1->next = createNode(3);
    if (list1->next == NULL) { freeList(list1); return 1; }
    list1->next->next = createNode(5);
    if (list1->next->next == NULL) { freeList(list1); return 1; }

    struct ListNode* list2 = createNode(2);
    if (list2 == NULL) { freeList(list1); return 1; }
    list2->next = createNode(4);
    if (list2->next == NULL) { freeList(list1); freeList(list2); return 1; }
    list2->next->next = createNode(6);
    if (list2->next->next == NULL) { freeList(list1); freeList(list2); return 1; }

    struct ListNode* mergedList = mergeTwoLists(list1, list2);

    printList(mergedList);

    freeList(mergedList);

    return 0;
}