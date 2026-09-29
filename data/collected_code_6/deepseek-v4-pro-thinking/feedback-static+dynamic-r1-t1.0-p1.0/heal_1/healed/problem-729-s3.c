#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *newNode(int val) {
    struct ListNode *node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }
    node->val = val;
    node->next = NULL;
    return node;
}

void freeList(struct ListNode *head) {
    while (head != NULL) {
        struct ListNode *tmp = head;
        head = head->next;
        free(tmp);
    }
}

struct ListNode *createList(const int *values, int size) {
    struct ListNode dummy;
    dummy.val = 0;
    dummy.next = NULL;
    struct ListNode *tail = &dummy;
    for (int i = 0; i < size; i++) {
        struct ListNode *node = newNode(values[i]);
        if (node == NULL) {
            freeList(dummy.next);
            return NULL;
        }
        tail->next = node;
        tail = node;
    }
    return dummy.next;
}

struct ListNode *addLists(struct ListNode *l1, struct ListNode *l2) {
    struct ListNode *dummy = newNode(0);
    if (dummy == NULL) {
        return NULL;
    }
    struct ListNode *current = dummy;
    int carry = 0;
    while (l1 != NULL || l2 != NULL || carry != 0) {
        int sum = carry;
        if (l1 != NULL) {
            sum += l1->val;
            l1 = l1->next;
        }
        if (l2 != NULL) {
            sum += l2->val;
            l2 = l2->next;
        }
        carry = sum / 10;
        struct ListNode *node = newNode(sum % 10);
        if (node == NULL) {
            freeList(dummy->next);
            free(dummy);
            return NULL;
        }
        current->next = node;
        current = node;
    }
    struct ListNode *result = dummy->next;
    free(dummy);
    return result;
}

int main(void) {
    const int values1[] = {2, 4, 3};
    const int values2[] = {5, 6, 4};

    struct ListNode *l1 = createList(values1, 3);
    if (l1 == NULL) {
        return EXIT_FAILURE;
    }

    struct ListNode *l2 = createList(values2, 3);
    if (l2 == NULL) {
        freeList(l1);
        return EXIT_FAILURE;
    }

    struct ListNode *sum = addLists(l1, l2);
    if (sum == NULL) {
        freeList(l1);
        freeList(l2);
        return EXIT_FAILURE;
    }

    struct ListNode *tmp = sum;
    while (tmp != NULL) {
        printf("%d", tmp->val);
        if (tmp->next != NULL) {
            printf(" -> ");
        }
        tmp = tmp->next;
    }
    printf("\n");

    freeList(l1);
    freeList(l2);
    freeList(sum);

    return 0;
}