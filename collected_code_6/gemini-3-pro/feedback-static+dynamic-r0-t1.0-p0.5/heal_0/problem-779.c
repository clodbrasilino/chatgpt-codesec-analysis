#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    struct List* next;
} List;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

List* createList(Node* head) {
    List* newList = (List*)malloc(sizeof(List));
    if (!newList) {
        exit(EXIT_FAILURE);
    }
    newList->head = head;
    newList->next = NULL;
    return newList;
}

void freeNodeList(Node* head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

void freeListOfLists(List* head) {
    while (head) {
        List* temp = head;
        head = head->next;
        freeNodeList(temp->head);
        free(temp);
    }
}

bool areListsEqual(Node* list1, Node* list2) {
    while (list1 && list2) {
        if (list1->data != list2->data) {
            return false;
        }
        list1 = list1->next;
        list2 = list2->next;
    }
    return list1 == NULL && list2 == NULL;
}

int countUniqueLists(List* head) {
    if (!head) {
        return 0;
    }

    int uniqueCount = 0;
    List* current = head;

    while (current) {
        bool isUnique = true;
        List* checker = head;

        while (checker != current) {
            if (areListsEqual(current->head, checker->head)) {
                isUnique = false;
                break;
            }
            checker = checker->next;
        }

        if (isUnique) {
            uniqueCount++;
        }
        current = current->next;
    }

    return uniqueCount;
}

int main(void) {
    Node* n1 = createNode(1);
    n1->next = createNode(2);
    n1->next->next = createNode(3);

    Node* n2 = createNode(1);
    n2->next = createNode(2);
    n2->next->next = createNode(3);

    Node* n3 = createNode(4);
    n3->next = createNode(5);

    List* l1 = createList(n1);
    List* l2 = createList(n2);
    List* l3 = createList(n3);

    l1->next = l2;
    l2->next = l3;

    int uniqueCount = countUniqueLists(l1);
    printf("%d\n", uniqueCount);

    freeListOfLists(l1);

    return EXIT_SUCCESS;
}