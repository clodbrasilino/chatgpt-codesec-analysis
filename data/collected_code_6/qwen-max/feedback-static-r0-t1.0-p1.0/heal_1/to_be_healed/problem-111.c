#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int size;
} List;

void add(List *list, int value) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) exit(EXIT_FAILURE);
    node->value = value;
    node->next = list->head;
    list->head = node;
    list->size++;
}

int contains(List *list, int value) {
    Node *current = list->head;
    while (current != NULL) {
        if (current->value == value) return 1;
        current = current->next;
    }
    return 0;
}

List *findCommonElements(List **lists, int n) {
    List *common = (List *)malloc(sizeof(List));
    common->head = NULL;
    common->size = 0;

    if (n <= 0) return common;

    for (Node *i = lists[0]->head; i != NULL; i = i->next) {
        int inAll = 1;
        for (int j = 1; j < n; j++) {
            if (!contains(lists[j], i->value)) {
                inAll = 0;
                break;
            }
        }
        if (inAll && !contains(common, i->value)) {
            add(common, i->value);
        }
    }

    return common;
}

void printList(List *list) {
    for (Node *current = list->head; current != NULL; current = current->next) {
        printf("%d ", current->value);
    }
    printf("\n");
}

void freeList(List *list) {
    Node *current = list->head;
    Node *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

int main() {
    List *lists[] = {NULL, NULL, NULL};
    for (int i = 0; i < 3; i++) {
        lists[i] = (List *)malloc(sizeof(List));
        lists[i]->head = NULL;
        lists[i]->size = 0;
    }

    /* Possible weaknesses found:
     *  Variable 'elements1' can be declared as const array [constVariable]
     */
    int elements1[] = {1, 2, 3};
    /* Possible weaknesses found:
     *  Variable 'elements2' can be declared as const array [constVariable]
     */
    int elements2[] = {2, 3, 4};
    /* Possible weaknesses found:
     *  Variable 'elements3' can be declared as const array [constVariable]
     */
    int elements3[] = {2, 5};

    for (int i = 0; i < 3; i++) {
        add(lists[0], elements1[i]);
    }
    for (int i = 0; i < 3; i++) {
        add(lists[1], elements2[i]);
    }
    for (int i = 0; i < 2; i++) {
        add(lists[2], elements3[i]);
    }

    List *common = findCommonElements(lists, 3);

    printList(common);

    for (int i = 0; i < 3; i++) {
        freeList(lists[i]);
    }
    freeList(common);

    return 0;
}