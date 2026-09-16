#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct ListNode {
    Tuple* value;
    struct ListNode* next;
} ListNode;

ListNode* insert_into_list(ListNode* head, Tuple* t) {
    ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));
    if (!new_node) return head;
    new_node->value = t;
    new_node->next = NULL;

    if (head == NULL) {
        return new_node;
    } else {
        ListNode* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
        return head;
    }
}

void free_list(ListNode* head) {
    while (head) {
        ListNode* temp = head;
        head = head->next;
        free(temp->value);
        free(temp);
    }
}

void group_by_second_element(Tuple* tuples, int length, ListNode*** grouped_list, int* list_size) {
    *list_size = 0;
    *grouped_list = (ListNode**)malloc(10 * sizeof(ListNode*));
    for (int i = 0; i < 10; i++) (*grouped_list)[i] = NULL;

    for (int i = 0; i < length; i++) {
        int key = tuples[i].second % 10;
        if (!(*grouped_list)[key]) (*list_size)++;
        (*grouped_list)[key] = insert_into_list((*grouped_list)[key], &tuples[i]);
    }
}

int main() {
    Tuple tuples[] = {{1, 3}, {2, 4}, {3, 3}, {4, 2}, {5, 4}};
    int length = sizeof(tuples)/sizeof(tuples[0]);

    ListNode** grouped_list;
    int list_size;
    
    group_by_second_element(tuples, length, &grouped_list, &list_size);

    for (int i = 0; i < 10; i++) {
        if (grouped_list[i] != NULL) {
            printf("Group %d: ", i);
            for (ListNode* node = grouped_list[i]; node != NULL; node = node->next) {
                printf("(%d, %d) ", node->value->first, node->value->second);
            }
            printf("\n");
        }
    }

    for (int i = 0; i < 10; i++) {
        free_list(grouped_list[i]);
    }
    free(grouped_list);

    return 0;
}