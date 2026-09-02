#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int value;
    struct ListNode *next;
} ListNode;

ListNode* create_node(int value) {
    ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void free_list(ListNode *head) {
    while (head != NULL) {
        ListNode *temp = head;
        head = head->next;
        free(temp);
    }
}

ListNode* subtract_lists(ListNode *list1, ListNode *list2) {
    if (list1 == NULL || list2 == NULL) {
        return NULL;
    }

    ListNode *result_head = NULL;
    ListNode *result_tail = NULL;

    ListNode *current1 = list1;
    ListNode *current2 = list2;

    while (current1 != NULL && current2 != NULL) {
        if (current1->value > current2->value) {
            ListNode *new_node = create_node(current1->value - current2->value);
            if (new_node == NULL) {
                free_list(result_head);
                return NULL;
            }
            if (result_head == NULL) {
                result_head = new_node;
                result_tail = new_node;
            } else {
                result_tail->next = new_node;
                result_tail = new_node;
            }
            current1 = current1->next;
            current2 = current2->next;
        } else if (current1->value < current2->value) {
            ListNode *new_node = create_node(current2->value - current1->value);
            if (new_node == NULL) {
                free_list(result_head);
                return NULL;
            }
            if (result_head == NULL) {
                result_head = new_node;
                result_tail = new_node;
            } else {
                result_tail->next = new_node;
                result_tail = new_node;
            }
            current1 = current1->next;
            current2 = current2->next;
        } else {
            current1 = current1->next;
            current2 = current2->next;
        }
    }

    while (current1 != NULL) {
        ListNode *new_node = create_node(current1->value);
        if (new_node == NULL) {
            free_list(result_head);
            return NULL;
        }
        if (result_head == NULL) {
            result_head = new_node;
            result_tail = new_node;
        } else {
            result_tail->next = new_node;
            result_tail = new_node;
        }
        current1 = current1->next;
    }

    while (current2 != NULL) {
        ListNode *new_node = create_node(current2->value);
        if (new_node == NULL) {
            free_list(result_head);
            return NULL;
        }
        if (result_head == NULL) {
            result_head = new_node;
            result_tail = new_node;
        } else {
            result_tail->next = new_node;
            result_tail = new_node;
        }
        current2 = current2->next;
    }

    return result_head;
}

int main() {
    ListNode *list1 = create_node(10);
    list1->next = create_node(20);
    list1->next->next = create_node(30);

    ListNode *list2 = create_node(15);
    list2->next = create_node(25);

    ListNode *result = subtract_lists(list1, list2);

    ListNode *current = result;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }

    free_list(list1);
    free_list(list2);
    free_list(result);

    return 0;
}