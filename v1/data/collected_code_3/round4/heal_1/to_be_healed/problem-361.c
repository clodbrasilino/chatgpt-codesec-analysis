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
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newNode' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

List* createList(Node* node) {
    List* newList = (List*)malloc(sizeof(List));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newList' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    newList->head = node;
    newList->next = NULL;
    return newList;
}

void removeEmptyLists(List** head) {
    List* temp = *head;
    List* prev = NULL;

    while(temp != NULL) {
        if(temp->head == NULL) {
            if(prev == NULL) {
                *head = temp->next;
                free(temp);
                temp = *head;
            } else {
                prev->next = temp->next;
                free(temp);
                temp = prev->next;
            }
        } else {
            prev = temp;
            temp = temp->next;
        }
    }
}

int main() {
    Node* node1 = createNode(1);
    Node* node2 = createNode(2);
    Node* node3 = createNode(3);

    List* list1 = createList(node1);
    List* list2 = createList(NULL);
    List* list3 = createList(node2);
    List* list4 = createList(NULL);
    List* list5 = createList(node3);

    list1->next = list2;
    list2->next = list3;
    list3->next = list4;
    list4->next = list5;

    removeEmptyLists(&list1);

    List* temp = list1;
    while(temp != NULL) {
        if(temp->head != NULL) {
            printf("%d ", temp->head->data);
        }
        temp = temp->next;
    }

    return 0;
}