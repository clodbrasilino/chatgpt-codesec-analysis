#include <stdio.h>
#include <stdlib.h>

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
    if (!newNode) return NULL;
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

List* createList() {
    List* newList = (List*)malloc(sizeof(List));
    if (!newList) return NULL;
    newList->head = NULL;
    newList->next = NULL;
    return newList;
}

void appendNode(List* list, int data) {
    if (!list) return;
    Node* newNode = createNode(data);
    if (!newNode) return;
    if (!list->head) {
        list->head = newNode;
        return;
    }
    Node* current = list->head;
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
}

void appendList(List** head, List* newList) {
    if (!head || !newList) return;
    if (!*head) {
        *head = newList;
        return;
    }
    List* current = *head;
    while (current->next) {
        current = current->next;
    }
    current->next = newList;
}

void freeNodeList(Node* head) {
    Node* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void freeListOfLists(List* head) {
    List* temp;
    while (head) {
        temp = head;
        head = head->next;
        freeNodeList(temp->head);
        free(temp);
    }
}

int mergeFirstLast(List* listOfLists, List** firsts, List** lasts) {
    if (!listOfLists || !firsts || !lasts) return -1;
    
    *firsts = createList();
    *lasts = createList();
    if (!*firsts || !*lasts) return -1;

    List* currentList = listOfLists;
    while (currentList) {
        if (currentList->head) {
            appendNode(*firsts, currentList->head->data);
            
            Node* current = currentList->head;
            while (current->next) {
                current = current->next;
            }
            appendNode(*lasts, current->data);
        }
        currentList = currentList->next;
    }
    return 0;
}

void printFirstLast(List* firsts, List* lasts) {
    if (firsts) {
        Node* current = firsts->head;
        while (current) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
    }
    if (lasts) {
        Node* current = lasts->head;
        while (current) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
    }
}

int main(void) {
    List* listOfLists = NULL;
    
    List* l1 = createList();
    if (!l1) return 1;
    appendNode(l1, 1);
    appendNode(l1, 2);
    appendNode(l1, 3);
    appendList(&listOfLists, l1);
    
    List* l2 = createList();
    if (!l2) {
        freeListOfLists(listOfLists);
        return 1;
    }
    appendNode(l2, 4);
    appendNode(l2, 5);
    appendNode(l2, 6);
    appendList(&listOfLists, l2);
    
    List* l3 = createList();
    if (!l3) {
        freeListOfLists(listOfLists);
        return 1;
    }
    appendNode(l3, 7);
    appendNode(l3, 8);
    appendList(&listOfLists, l3);

    List* firsts = NULL;
    List* lasts = NULL;

    if (mergeFirstLast(listOfLists, &firsts, &lasts) == 0) {
        printFirstLast(firsts, lasts);
    }

    freeListOfLists(listOfLists);
    freeListOfLists(firsts);
    freeListOfLists(lasts);

    return 0;
}