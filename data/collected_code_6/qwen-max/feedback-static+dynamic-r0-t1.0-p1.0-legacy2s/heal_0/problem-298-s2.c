#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int value;
    struct ListNode *next;
} ListNode;

ListNode* create_node(int value) {
    ListNode *new_node = (ListNode*)malloc(sizeof(ListNode));
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

int find_in_list(ListNode *list, int value) {
    while (list != NULL) {
        if (list->value == value) {
            return 1;
        }
        list = list->next;
    }
    return 0;
}

void find_common_elements(ListNode *list1, ListNode *list2, ListNode **result) {
    while (list1 != NULL) {
        if (find_in_list(list2, list1->value)) {
            ListNode *new_node = create_node(list1->value);
            if (*result == NULL) {
                *result = new_node;
            } else {
                ListNode *temp = *result;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = new_node;
            }
        }
        list1 = list1->next;
    }
}

void free_list(ListNode *list) {
    while (list != NULL) {
        ListNode *temp = list;
        list = list->next;
        free(temp);
    }
}

void print_list(ListNode *list) {
    while (list != NULL) {
        printf("%d ", list->value);
        list = list->next;
    }
    printf("\n");
}

int main() {
    ListNode *list1 = create_node(1);
    list1->next = create_node(2);
    list1->next->next = create_node(3);

    ListNode *list2 = create_node(2);
    list2->next = create_node(3);
    list2->next->next = create_node(4);

    ListNode *result = NULL;
    find_common_elements(list1, list2, &result);

    print_list(result);

    free_list(list1);
    free_list(list2);
    free_list(result);

    return 0;
}