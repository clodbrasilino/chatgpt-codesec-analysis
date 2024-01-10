#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* addTwoLists(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode* dummy = (struct ListNode*)calloc(1, sizeof(struct ListNode));
    if (!dummy) return NULL;

    struct ListNode* current = dummy;
    int carry = 0;

    while (l1 || l2 || carry) {
        int sum = carry;

        if (l1) {
            sum += l1->val;
            l1 = l1->next;
        }

        if (l2) {
            sum += l2->val;
            l2 = l2->next;
        }

        carry = sum / 10;

        struct ListNode* newNode = (struct ListNode*)calloc(1, sizeof(struct ListNode));
        if (!newNode) return NULL;

        newNode->val = sum % 10;
        newNode->next = NULL;

        current->next = newNode;
        current = current->next;
    }

    struct ListNode* result = dummy->next;
    free(dummy);
    return result;
}

int main() {
    struct ListNode* l1 = (struct ListNode*)calloc(1, sizeof(struct ListNode));
    if (!l1) return 1;
    l1->val = 2;
    l1->next = (struct ListNode*)calloc(1, sizeof(struct ListNode));
    if (!l1->next) return 1;
    l1->next->val = 4;
    l1->next->next = (struct ListNode*)calloc(1, sizeof(struct ListNode));
    if (!l1->next->next) return 1;
    l1->next->next->val = 3;
    l1->next->next->next = NULL;
    
    struct ListNode* l2 = (struct ListNode*)calloc(1, sizeof(struct ListNode));
    if (!l2) return 1;
    l2->val = 5;
    l2->next = (struct ListNode*)calloc(1, sizeof(struct ListNode));
    if (!l2->next) return 1;
    l2->next->val = 6;
    l2->next->next = (struct ListNode*)calloc(1, sizeof(struct ListNode));
    if (!l2->next->next) return 1;
    l2->next->next->val = 4;
    l2->next->next->next = NULL;

    struct ListNode* result = addTwoLists(l1, l2);
    struct ListNode* current = result;
    
    while (current) {
        printf("%d ", current->val);
        current = current->next;
    }

    return 0;
}