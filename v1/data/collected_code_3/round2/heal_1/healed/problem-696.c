#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

Node* zipLists(Node* list1, Node* list2) {
    Node* head = newNode(0);
    if (!head) {
        return NULL;
    }
    Node* current = head;
    while (list1 != NULL || list2 != NULL) {
        if (list1 != NULL) {
            current->next = list1;
            current = current->next;
            list1 = list1->next;
        }
        if (list2 != NULL) {
            current->next = list2;
            current = current->next;
            list2 = list2->next;
        }
    }
    Node* temp = head;
    head = head->next;
    free(temp);
    return head;
}

void printList(Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int main() {
    Node* list1 = newNode(1);
    if (list1 != NULL) {
        list1->next = newNode(3);
        if (list1->next != NULL) {
            list1->next->next = newNode(5);
        }
    }

    Node* list2 = newNode(2);
    if (list2 != NULL) {
        list2->next = newNode(4);
        if (list2->next != NULL) {
            list2->next->next = newNode(6);
        } 
    } 

    Node* zippedList = zipLists(list1, list2);

    if(zippedList != NULL){
       printList(zippedList);
    }
    return 0;
}