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
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

void freeListOfLists(List* head) {
    List* current = head;
    while (current != NULL) {
        List* temp = current;
        current = current->next;
        freeNodeList(temp->head);
        free(temp);
    }
}

bool areListsEqual(Node* list1, Node* list2) {
    Node* curr1 = list1;
    Node* curr2 = list2;

    while (curr1 != NULL && curr2 != NULL) {
        if (curr1->data != curr2->data) {
            return false;
        }
        curr1 = curr1->next;
        curr2 = curr2->next;
    }

    return (curr1 == NULL && curr2 == NULL);
}

int countUniqueLists(List* head) {
    if (head == NULL) {
        return 0;
    }

    int uniqueCount = 0;
    List* current = head;

    while (current != NULL) {
        bool isDuplicate = false;
        List* checker = head;

        while (checker != current) {
            if (areListsEqual(current->head, checker->head)) {
                isDuplicate = true;
                break;
            }
            checker = checker->next;
        }

        if (!isDuplicate) {
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

    Node* n4 = createNode(1);
    n4->next = createNode(2);
    n4->next->next = createNode(3);

    List* l1 = createList(n1);
    List* l2 = createList(n2);
    List* l3 = createList(n3);
    List* l4 = createList(n4);

    l1->next = l2;
    l2->next = l3;
    l3->next = l4;

    int uniqueCount = countUniqueLists(l1);
    printf("%d\n", uniqueCount);

    freeListOfLists(l1);

    return EXIT_SUCCESS;
}