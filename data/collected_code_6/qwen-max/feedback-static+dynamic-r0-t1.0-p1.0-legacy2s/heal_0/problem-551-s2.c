#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    struct List *sublist;
} List;

List* createList() {
    return (List*)calloc(1, sizeof(List));
}

void insertNode(List *list, int val) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->val = val;
    newNode->next = list->head;
    list->head = newNode;
}

List* getColumn(List *matrix, int col) {
    if (!matrix || col < 0) return NULL;
    List *result = createList();
    List *current = matrix;
    while (current) {
        if (col == 0) {
            for (Node *n = current->head; n != NULL; n = n->next) {
                insertNode(result, n->val);
            }
        } else {
            if (current->sublist) {
                List *res = getColumn(current->sublist, col - 1);
                for (Node *n = res->head; n != NULL; n = n->next) {
                    insertNode(result, n->val);
                }
                free(res->sublist);
                free(res);
            }
        }
        current = current->sublist;
    }
    return result;
}

void printList(List *list) {
    for (Node *n = list->head; n != NULL; n = n->next) {
        printf("%d ", n->val);
    }
    printf("\n");
}

void freeList(List *list) {
    while (list) {
        Node *curr = list->head;
        while (curr) {
            Node *next = curr->next;
            free(curr);
            curr = next;
        }
        List *nextSub = list->sublist;
        free(list);
        list = nextSub;
    }
}

int main() {
    List *matrix = createList();
    List *sublist1 = createList();
    List *sublist2 = createList();

    insertNode(matrix, 1);
    insertNode(sublist1, 2);
    insertNode(sublist1, 5);
    insertNode(sublist2, 3);
    insertNode(sublist2, 8);

    matrix->sublist = sublist1;
    sublist1->sublist = sublist2;

    List *col = getColumn(matrix, 1);
    printList(col);

    freeList(matrix);
    freeList(col);

    return 0;
}