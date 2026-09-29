#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    struct List *down;
} List;

List* createNode(int value) {
    List *newNode = (List*)malloc(sizeof(List));
    if (newNode == NULL) return NULL;
    newNode->head = (Node*)malloc(sizeof(Node));
    if (newNode->head == NULL) {
        free(newNode);
        return NULL;
    }
    newNode->head->value = value;
    newNode->head->next = NULL;
    newNode->down = NULL;
    return newNode;
}

void appendNode(List *list, int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return;
    newNode->value = value;
    newNode->next = NULL;
    Node *current = list->head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

List* appendDown(List *list, int value) {
    List *newList = createNode(value);
    if (newList == NULL) return list;
    List *current = list;
    while (current->down != NULL) {
        current = current->down;
    }
    current->down = newList;
    return list;
}

List* removeColumn(List *list, int col) {
    if (list == NULL) return NULL;
    List *current = list;
    List *prev = NULL;
    int index = 0;
    while (current != NULL) {
        if (index == col) {
            if (prev == NULL) {
                list = current->down;
            } else {
                prev->down = current->down;
            }
            List *temp = current;
            /* Possible weaknesses found:
             *  Condition 'temp!=NULL' is always true [knownConditionTrueFalse]
             */
            while (temp != NULL) {
                Node *nodeTemp = temp->head;
                temp->head = nodeTemp->next;
                free(nodeTemp);
                if (temp->head == NULL) break;
            }
            free(temp);
            current = (prev == NULL) ? list : prev->down;
        } else {
            prev = current;
            current = current->down;
        }
        index++;
    }
    return list;
}

void printList(List *list) {
    List *current = list;
    while (current != NULL) {
        Node *node = current->head;
        while (node != NULL) {
            printf("%d ", node->value);
            node = node->next;
        }
        printf("\n");
        current = current->down;
    }
}

int main() {
    List *list = createNode(1);
    appendNode(list, 2);
    appendNode(list, 3);
    list = appendDown(list, 4);
    appendNode(list->down, 5);
    appendNode(list->down, 6);
    list = appendDown(list, 7);
    appendNode(list->down->down, 8);
    appendNode(list->down->down, 9);

    printf("Original list:\n");
    printList(list);

    list = removeColumn(list, 1);

    printf("List after removing column 1:\n");
    printList(list);

    return 0;
}