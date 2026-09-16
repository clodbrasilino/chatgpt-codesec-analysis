#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    struct List* next;
} List;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        exit(EXIT_FAILURE);
    }
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

List* createList() {
    List* newList = (List*)malloc(sizeof(List));
    if (!newList) {
        exit(EXIT_FAILURE);
    }
    newList->head = NULL;
    newList->next = NULL;
    return newList;
}

void appendNode(List* list, int value) {
    if (!list) return;
    Node* newNode = createNode(value);
    if (!list->head) {
        list->head = newNode;
    } else {
        Node* curr = list->head;
        while (curr->next) {
            curr = curr->next;
        }
        curr->next = newNode;
    }
}

void appendList(List** listOfLists, List* newList) {
    if (!listOfLists || !newList) return;
    if (!*listOfLists) {
        *listOfLists = newList;
    } else {
        List* curr = *listOfLists;
        while (curr->next) {
            curr = curr->next;
        }
        curr->next = newList;
    }
}

bool areListsEqual(List* list1, List* list2) {
    if (!list1 && !list2) return true;
    if (!list1 || !list2) return false;
    
    Node* p1 = list1->head;
    Node* p2 = list2->head;
    
    while (p1 && p2) {
        if (p1->value != p2->value) {
            return false;
        }
        p1 = p1->next;
        p2 = p2->next;
    }
    return p1 == NULL && p2 == NULL;
}

int countUniqueLists(List* listOfLists) {
    if (!listOfLists) return 0;
    
    int uniqueCount = 0;
    List* curr = listOfLists;
    
    while (curr) {
        bool isUnique = true;
        List* temp = listOfLists;
        while (temp != curr) {
            if (areListsEqual(curr, temp)) {
                isUnique = false;
                break;
            }
            temp = temp->next;
        }
        if (isUnique) {
            uniqueCount++;
        }
        curr = curr->next;
    }
    
    return uniqueCount;
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

int main(void) {
    List* listOfLists = NULL;
    
    List* list1 = createList();
    appendNode(list1, 1);
    appendNode(list1, 2);
    
    List* list2 = createList();
    appendNode(list2, 1);
    appendNode(list2, 2);
    
    List* list3 = createList();
    appendNode(list3, 3);
    
    List* list4 = createList();
    
    appendList(&listOfLists, list1);
    appendList(&listOfLists, list2);
    appendList(&listOfLists, list3);
    appendList(&listOfLists, list4);
    
    int uniqueCount = countUniqueLists(listOfLists);
    printf("%d\n", uniqueCount);
    
    freeListOfLists(listOfLists);
    return EXIT_SUCCESS;
}