#include <stdbool.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct LinkedList {
    Node *head;
} LinkedList;

bool hasCommonElement(LinkedList *list1, LinkedList *list2) {
    for (Node *current1 = list1->head; current1 != NULL; current1 = current1->next) {
        for (Node *current2 = list2->head; current2 != NULL; current2 = current2->next) {
            if (current1->value == current2->value) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    LinkedList list1, list2;
    list1.head = (Node *)malloc(sizeof(Node));
    list2.head = (Node *)malloc(sizeof(Node));

    if (list1.head == NULL || list2.head == NULL) {
        free(list1.head);
        free(list2.head);
        return 1;
    }

    list1.head->value = 1;
    list1.head->next = (Node *)malloc(sizeof(Node));
    if (list1.head->next == NULL) {
        free(list1.head);
        free(list2.head);
        return 1;
    }
    list1.head->next->value = 2;
    list1.head->next->next = (Node *)malloc(sizeof(Node));
    if (list1.head->next->next == NULL) {
        free(list1.head->next);
        free(list1.head);
        free(list2.head);
        return 1;
    }
    list1.head->next->next->value = 3;
    list1.head->next->next->next = NULL;

    list2.head->value = 4;
    list2.head->next = (Node *)malloc(sizeof(Node));
    if (list2.head->next == NULL) {
        free(list1.head->next->next);
        free(list1.head->next);
        free(list1.head);
        free(list2.head);
        return 1;
    }
    list2.head->next->value = 5;
    list2.head->next->next = (Node *)malloc(sizeof(Node));
    if (list2.head->next->next == NULL) {
        free(list1.head->next->next);
        free(list1.head->next);
        free(list1.head);
        free(list2.head->next);
        free(list2.head);
        return 1;
    }
    list2.head->next->next->value = 1;
    list2.head->next->next->next = NULL;

    bool result = hasCommonElement(&list1, &list2);

    free(list1.head->next->next);
    free(list1.head->next);
    free(list1.head);
    free(list2.head->next->next);
    free(list2.head->next);
    free(list2.head);

    return result ? 0 : 1;
}