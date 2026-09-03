#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

typedef struct Node {
    Tuple value;
    struct Node *next;
} ListNode;

ListNode* addTupleToList(ListNode *head, Tuple tuple) {
    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        return head;  // Memory allocation failed, do not modify the list.
    }
    newNode->value.a = tuple.a;
    newNode->value.b = tuple.b;
    newNode->next = NULL;

    if (head == NULL) {
        return newNode;
    }

    ListNode *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    return head;
}

int main() {
    Tuple t1 = {1, 2};
    Tuple t2 = {3, 4};

    ListNode *list = NULL;
    list = addTupleToList(list, t1);
    list = addTupleToList(list, t2);

    for (ListNode *current = list; current != NULL; current = current->next) {
        printf("(%d, %d) ", current->value.a, current->value.b);
    }
    printf("\n");

    ListNode *temp = NULL;
    while (list != NULL) {
        temp = list;
        list = list->next;
        free(temp);
    }

    return 0;
}