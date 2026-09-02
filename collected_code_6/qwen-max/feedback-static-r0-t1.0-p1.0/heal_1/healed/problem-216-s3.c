#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct ListNode {
    int value;
    struct ListNode *next;
} ListNode;

typedef struct List {
    ListNode *head;
} List;

bool isSubsetNested(List *main_list, List *subset) {
    if (subset->head == NULL) return true;
    for (ListNode *sub = subset->head; sub != NULL; sub = sub->next) {
        bool found = false;
        for (ListNode *main_node = main_list->head; main_node != NULL; main_node = main_node->next) {
            if (main_node->value == sub->value) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}

int main() {
    List list1 = { .head = NULL };
    list1.head = (ListNode *)malloc(sizeof(ListNode));
    list1.head->value = 1;
    list1.head->next = (ListNode *)malloc(sizeof(ListNode));
    list1.head->next->value = 2;
    list1.head->next->next = (ListNode *)malloc(sizeof(ListNode));
    list1.head->next->next->value = 3;
    list1.head->next->next->next = (ListNode *)malloc(sizeof(ListNode));
    list1.head->next->next->next->value = 4;
    list1.head->next->next->next->next = (ListNode *)malloc(sizeof(ListNode));
    list1.head->next->next->next->next->value = 5;
    list1.head->next->next->next->next->next = (ListNode *)malloc(sizeof(ListNode));
    list1.head->next->next->next->next->next->value = 6;
    list1.head->next->next->next->next->next->next = NULL;

    List list2 = { .head = NULL };
    list2.head = (ListNode *)malloc(sizeof(ListNode));
    list2.head->value = 2;
    list2.head->next = (ListNode *)malloc(sizeof(ListNode));
    list2.head->next->value = 4;
    list2.head->next->next = (ListNode *)malloc(sizeof(ListNode));
    list2.head->next->next->value = 6;
    list2.head->next->next->next = NULL;

    if (isSubsetNested(&list1, &list2)) {
        printf("List2 is a subset of List1\n");
    } else {
        printf("List2 is not a subset of List1\n");
    }

    ListNode *current;
    for (current = list1.head; current != NULL; ) {
        ListNode *temp = current;
        current = current->next;
        free(temp);
    }
    for (current = list2.head; current != NULL; ) {
        ListNode *temp = current;
        current = current->next;
        free(temp);
    }
    return 0;
}