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

Node* newNode(int data) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

List* newList(Node* node) {
    List* temp = (List*)malloc(sizeof(List));
    temp->head = node;
    temp->next = NULL;
    return temp;
}

void removeEmptyLists(List** head) {
    List* temp = *head, *prev = NULL;
    while (temp != NULL) {
        if (temp->head == NULL) {
            if (prev == NULL) {
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
    Node* n1 = newNode(1);
    Node* n2 = NULL;
    Node* n3 = newNode(3);

    List* l1 = newList(n1);
    List* l2 = newList(n2);
    List* l3 = newList(n3);

    l1->next = l2;
    l2->next = l3;

    removeEmptyLists(&l1);

    // After removing, the list should only contain l1 and l3.
    List* temp = l1;
    /* Possible weaknesses found:
     *  Potential leak of memory pointed to by 'temp' [unix.Malloc]
     */
    while(temp != NULL) {
        if(temp->head != NULL) {
            printf("%d ", temp->head->data);
        }
        temp = temp->next;
    }

    return 0;
}