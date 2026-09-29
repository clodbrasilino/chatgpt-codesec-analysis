#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

typedef struct Node {
    Tuple data;
    struct Node *next;
} ListNode;

ListNode* addTupleToList(ListNode* head, Tuple newTuple) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        return head;
    }
    newNode->data = newTuple;
    newNode->next = head;
    return newNode;
}

int main() {
    ListNode* list = NULL;
    Tuple tuple1 = {1, 2};
    Tuple tuple2 = {3, 4};

    list = addTupleToList(list, tuple1);
    list = addTupleToList(list, tuple2);

    for (ListNode* current = list; current != NULL; current = current->next) {
        printf("(%d, %d)\n", current->data.a, current->data.b);
    }

    while (list != NULL) {
        ListNode* temp = list;
        list = list->next;
        free(temp);
    }

    return 0;
}