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
    if (newNode == NULL) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

List* createList() {
    List* newList = (List*)malloc(sizeof(List));
    if (newList == NULL) {
        return NULL;
    }
    newList->head = NULL;
    newList->next = NULL;
    return newList;
}

void appendNode(List* list, int data) {
    if (list == NULL) {
        return;
    }
    Node* newNode = createNode(data);
    if (newNode == NULL) {
        return;
    }
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

int compareLists(Node* list1, Node* list2) {
    Node* current1 = list1;
    Node* current2 = list2;
    
    while (current1 != NULL && current2 != NULL) {
        if (current1->data != current2->data) {
            return 0;
        }
        current1 = current1->next;
        current2 = current2->next;
    }
    
    return (current1 == NULL && current2 == NULL);
}

void freeList(List* list) {
    if (list == NULL) {
        return;
    }
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

void freeListOfLists(List* listOfLists) {
    List* current = listOfLists;
    while (current != NULL) {
        List* temp = current;
        current = current->next;
        freeList(temp);
    }
}

List* removeDuplicates(List* listOfLists) {
    if (listOfLists == NULL) {
        return NULL;
    }
    
    List* current = listOfLists;
    
    while (current != NULL && current->next != NULL) {
        List* runner = current;
        
        while (runner->next != NULL) {
            if (compareLists(current->head, runner->next->head)) {
                List* duplicate = runner->next;
                runner->next = duplicate->next;
                freeList(duplicate);
            } else {
                runner = runner->next;
            }
        }
        
        current = current->next;
    }
    
    return listOfLists;
}

void printListOfLists(List* listOfLists) {
    List* current = listOfLists;
    while (current != NULL) {
        Node* node = current->head;
        printf("[");
        while (node != NULL) {
            printf("%d", node->data);
            if (node->next != NULL) {
                printf(", ");
            }
            node = node->next;
        }
        printf("] ");
        current = current->next;
    }
    printf("\n");
}

int main() {
    List* listOfLists = createList();
    if (listOfLists == NULL) {
        return 1;
    }
    
    List* list1 = createList();
    if (list1 == NULL) {
        freeListOfLists(listOfLists);
        return 1;
    }
    appendNode(list1, 1);
    appendNode(list1, 2);
    appendNode(list1, 3);
    list1->next = listOfLists->next;
    listOfLists->next = list1;
    
    List* list2 = createList();
    if (list2 == NULL) {
        freeListOfLists(listOfLists);
        return 1;
    }
    appendNode(list2, 4);
    appendNode(list2, 5);
    list2->next = listOfLists->next;
    listOfLists->next = list2;
    
    List* list3 = createList();
    if (list3 == NULL) {
        freeListOfLists(listOfLists);
        return 1;
    }
    appendNode(list3, 1);
    appendNode(list3, 2);
    appendNode(list3, 3);
    list3->next = listOfLists->next;
    listOfLists->next = list3;
    
    List* list4 = createList();
    if (list4 == NULL) {
        freeListOfLists(listOfLists);
        return 1;
    }
    appendNode(list4, 6);
    list4->next = listOfLists->next;
    listOfLists->next = list4;
    
    printf("Original list of lists: ");
    printListOfLists(listOfLists);
    
    listOfLists = removeDuplicates(listOfLists);
    
    printf("After removing duplicates: ");
    printListOfLists(listOfLists);
    
    freeListOfLists(listOfLists);
    
    return 0;
}