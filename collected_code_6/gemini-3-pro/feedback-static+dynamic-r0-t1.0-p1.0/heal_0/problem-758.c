#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct ListList {
    Node* list;
    struct ListList* next;
} ListList;

int isIdentical(Node* a, Node* b) {
    while (a != NULL && b != NULL) {
        if (a->data != b->data) {
            return 0;
        }
        a = a->next;
        b = b->next;
    }
    return (a == NULL && b == NULL);
}

int countUniqueLists(ListList* head) {
    int uniqueCount = 0;
    ListList* current = head;
    ListList* checked = NULL;

    while (current != NULL) {
        ListList* temp = checked;
        int isDuplicate = 0;

        while (temp != NULL) {
            if (isIdentical(current->list, temp->list)) {
                isDuplicate = 1;
                break;
            }
            temp = temp->next;
        }

        if (!isDuplicate) {
            uniqueCount++;
            ListList* newNode = (ListList*)malloc(sizeof(ListList));
            if (newNode == NULL) {
                while (checked != NULL) {
                    ListList* toFree = checked;
                    checked = checked->next;
                    free(toFree);
                }
                return -1;
            }
            newNode->list = current->list;
            newNode->next = checked;
            checked = newNode;
        }

        current = current->next;
    }

    while (checked != NULL) {
        ListList* toFree = checked;
        checked = checked->next;
        free(toFree);
    }

    return uniqueCount;
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->next = NULL;
    }
    return newNode;
}

ListList* addList(ListList* head, Node* list) {
    ListList* newNode = (ListList*)malloc(sizeof(ListList));
    if (newNode != NULL) {
        newNode->list = list;
        newNode->next = head;
    }
    return newNode;
}

void freeList(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

void freeListList(ListList* head) {
    while (head != NULL) {
        ListList* temp = head;
        head = head->next;
        freeList(temp->list);
        free(temp);
    }
}

int main() {
    Node* list1 = createNode(1);
    if (list1) {
        list1->next = createNode(2);
        if (list1->next) {
            list1->next->next = createNode(3);
        }
    }

    Node* list2 = createNode(1);
    if (list2) {
        list2->next = createNode(4);
    }

    Node* list3 = createNode(1);
    if (list3) {
        list3->next = createNode(2);
        if (list3->next) {
            list3->next->next = createNode(3);
        }
    }

    ListList* listsOfLists = NULL;
    listsOfLists = addList(listsOfLists, list1);
    listsOfLists = addList(listsOfLists, list2);
    listsOfLists = addList(listsOfLists, list3);

    int uniqueCount = countUniqueLists(listsOfLists);
    
    if (uniqueCount != -1) {
        printf("%d\n", uniqueCount);
    }

    freeListList(listsOfLists);

    return 0;
}