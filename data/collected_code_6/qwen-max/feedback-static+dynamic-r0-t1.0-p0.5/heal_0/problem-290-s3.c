#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode;

typedef struct List {
    ListNode *head;
    int length;
} List;

List* createList() {
    List *list = (List*)malloc(sizeof(List));
    list->head = NULL;
    list->length = 0;
    return list;
}

void addNode(List *list, int data) {
    ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->data = data;
    newNode->next = list->head;
    list->head = newNode;
    list->length++;
}

List** findMaxLengthLists(List **lists, int n) {
    if (n == 0) return NULL;

    int max_length = 0;
    for (int i = 0; i < n; i++) {
        if (lists[i]->length > max_length) {
            max_length = lists[i]->length;
        }
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        if (lists[i]->length == max_length) {
            count++;
        }
    }

    List **result = (List**)malloc(count * sizeof(List*));
    int index = 0;
    for (int i = 0; i < n; i++) {
        if (lists[i]->length == max_length) {
            result[index++] = lists[i];
        }
    }

    return result;
}

int main() {
    List *list1 = createList();
    List *list2 = createList();
    List *list3 = createList();

    addNode(list1, 1);
    addNode(list1, 2);
    addNode(list1, 3);

    addNode(list2, 4);
    addNode(list2, 5);

    addNode(list3, 6);
    addNode(list3, 7);
    addNode(list3, 8);

    List *lists[] = {list1, list2, list3};
    int n = 3;

    List **maxLengthLists = findMaxLengthLists(lists, n);

    for (int i = 0; maxLengthLists && maxLengthLists[i]; i++) {
        printf("List with length %d: ", maxLengthLists[i]->length);
        ListNode *current = maxLengthLists[i]->head;
        while (current) {
            printf("%d -> ", current->data);
            current = current->next;
        }
        printf("NULL\n");
    }

    for (int i = 0; i < n; i++) {
        ListNode *current = lists[i]->head;
        while (current) {
            ListNode *temp = current;
            current = current->next;
            free(temp);
        }
        free(lists[i]);
    }

    if (maxLengthLists) {
        free(maxLengthLists);
    }

    return 0;
}