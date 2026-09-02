#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int data;
    struct List *next;
} ListNode, *List;

List newNode(int data) {
    List node = (List)malloc(sizeof(ListNode));
    node->data = data;
    node->next = NULL;
    return node;
}

void appendNode(List *head, int data) {
    if (*head == NULL) {
        *head = newNode(data);
    } else {
        List temp = *head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode(data);
    }
}

List* createListOfLists(int *values, int n, int m) {
    List *lists = (List*)calloc(n, sizeof(List));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            appendNode(&lists[i], values[i * m + j]);
        }
    }
    return lists;
}

void freeListOfLists(List *lists, int n) {
    for (int i = 0; i < n; ++i) {
        List current = lists[i];
        while (current) {
            List toFree = current;
            current = current->next;
            free(toFree);
        }
    }
    free(lists);
}

void printList(List head) {
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

List zipLists(List a, List b) {
    List result = NULL;
    while (a || b) {
        if (a) {
            appendNode(&result, a->data);
            a = a->next;
        }
        if (b) {
            appendNode(&result, b->data);
            b = b->next;
        }
    }
    return result;
}

List* zipListOfLists(List *list1, List *list2, int n) {
    List *result = (List*)calloc(n, sizeof(List));
    for (int i = 0; i < n; ++i) {
        result[i] = zipLists(list1[i], list2[i]);
    }
    return result;
}

int main() {
    int values1[] = {1, 2, 3, 4, 5, 6};
    int values2[] = {10, 20, 30, 40, 50, 60};

    List *list1 = createListOfLists(values1, 2, 3);
    List *list2 = createListOfLists(values2, 2, 3);

    List *zippedLists = zipListOfLists(list1, list2, 2);

    for (int i = 0; i < 2; ++i) {
        printList(zippedLists[i]);
    }

    freeListOfLists(list1, 2);
    freeListOfLists(list2, 2);
    freeListOfLists(zippedLists, 2);

    return 0;
}