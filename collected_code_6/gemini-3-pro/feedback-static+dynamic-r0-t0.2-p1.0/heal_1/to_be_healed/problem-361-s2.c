#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct ListOfLists {
    Node* head;
    struct ListOfLists* next;
} ListOfLists;

void freeList(Node* head) {
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void freeListOfLists(ListOfLists* head) {
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    ListOfLists* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        freeList(temp->head);
        free(temp);
    }
}

ListOfLists* removeEmptyLists(ListOfLists* head) {
    ListOfLists* current = head;
    ListOfLists* prev = NULL;

    while (current != NULL) {
        if (current->head == NULL) {
            ListOfLists* temp = current;
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            current = current->next;
            free(temp);
        } else {
            prev = current;
            current = current->next;
        }
    }
    return head;
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return NULL;
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

ListOfLists* createListOfListsNode(Node* listHead) {
    ListOfLists* newNode = (ListOfLists*)malloc(sizeof(ListOfLists));
    if (!newNode) return NULL;
    newNode->head = listHead;
    newNode->next = NULL;
    return newNode;
}

void printListOfLists(ListOfLists* head) {
    while (head != NULL) {
        Node* current = head->head;
        printf("[ ");
        while (current != NULL) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("]\n");
        head = head->next;
    }
}

int main(void) {
    Node* list1 = createNode(1);
    if (list1) list1->next = createNode(2);

    Node* list2 = NULL;

    Node* list3 = createNode(3);

    ListOfLists* lolHead = createListOfListsNode(list1);
    if (!lolHead) {
        freeList(list1);
        freeList(list3);
        return 1;
    }

    ListOfLists* lol2 = createListOfListsNode(list2);
    if (!lol2) {
        freeListOfLists(lolHead);
        freeList(list3);
        return 1;
    }
    lolHead->next = lol2;

    ListOfLists* lol3 = createListOfListsNode(list3);
    if (!lol3) {
        freeListOfLists(lolHead);
        return 1;
    }
    lol2->next = lol3;

    lolHead = removeEmptyLists(lolHead);

    printListOfLists(lolHead);

    freeListOfLists(lolHead);

    return 0;
}