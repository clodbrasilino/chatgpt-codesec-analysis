#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* removeEvenNumbers(struct ListNode* head) {
    struct ListNode* current = head;
    struct ListNode** prevPtr = &head;

    while (current != NULL) {
        if (current->val % 2 == 0) {
            *prevPtr = current->next;
            free(current);
            current = *prevPtr;
        } else {
            prevPtr = &current->next;
            current = current->next;
        }
    }
    return head;
}

int main() {
    // Example usage
    struct ListNode* head = malloc(sizeof(struct ListNode));
    head->val = 1;
    head->next = malloc(sizeof(struct ListNode));
    head->next->val = 2;
    head->next->next = malloc(sizeof(struct ListNode));
    head->next->next->val = 3;
    head->next->next->next = malloc(sizeof(struct ListNode));
    head->next->next->next->val = 4;
    head->next->next->next->next = NULL;

    head = removeEvenNumbers(head);

    struct ListNode* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->val);
        temp = temp->next;
    }
    printf("NULL\n");

    // Clean up
    temp = head;
    while (temp != NULL) {
        struct ListNode* toDelete = temp;
        temp = temp->next;
        free(toDelete);
    }

    return 0;
}