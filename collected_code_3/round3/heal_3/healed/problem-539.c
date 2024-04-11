#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)calloc(1, sizeof(Node));
    if (!newNode) {
        printf("Memory error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Node* createList(int base, int n) {
    Node* head = NULL;
    Node* temp;

    for (int i = 0; i < n; i++) {
        if (i == 0) {
            head = createNode(pow(base, i));
            temp = head;
        } else {
            if (temp != NULL) {
                temp->next = createNode(pow(base, i));
                if(temp->next == NULL){
                    freeList(head);
                    return NULL;
                }   
                temp = temp->next;
            }
        }
    }
    return head;
}

void freeList(Node* head) {
    Node* tmp;

    while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }

}

void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    int base = 2;
    int n = 10;
    Node* list = createList(base, n);
    if(list != NULL){
        printList(list);
        freeList(list);
    }
    return 0;
}