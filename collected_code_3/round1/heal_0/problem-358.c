#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(!newNode) {
        printf("Memory error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertNode(Node** head, int data) {
    if(*head == NULL) {
        *head = createNode(data);
    } else {
        Node* temp = *head;
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = createNode(data);
    }
}

Node* moduloDivision(Node* list1, Node* list2) {
    Node* result = NULL;
    while(list1 && list2) {
        if(list2->data == 0) {
            printf("Division by zero error\n");
            return NULL;
        }
        insertNode(&result, list1->data % list2->data);
        list1 = list1->next;
        list2 = list2->next;
    }
    return result;
}

void printList(Node* head) {
    while(head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {
    Node* list1 = NULL;
    Node* list2 = NULL;
    Node* result = NULL;

    insertNode(&list1, 10);
    insertNode(&list1, 20);
    insertNode(&list1, 30);
    insertNode(&list1, 40);

    insertNode(&list2, 3);
    insertNode(&list2, 4);
    insertNode(&list2, 5);
    insertNode(&list2, 6);

    result = moduloDivision(list1, list2);

    printList(result);

    return 0;
}