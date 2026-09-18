#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedList{
    int data;
    struct LinkedList *next;
}Node;

Node* createNode(int data) {
    Node * newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory Error!");
        exit(0);
    }
    newNode -> data = data;
    newNode -> next = NULL;
    return newNode;
}

void addNode(Node** head, int data){
    Node* newNode = createNode(data);
    newNode -> next = *head;
    *head = newNode;
}

void removeOutsideRange(Node **head, int min, int max) {
    Node *prev = NULL, *curr = *head;

    while (curr){
        if (curr -> data < min || curr -> data > max){
            if (prev == NULL){
                Node *temp = *head;
                *head = (*head) -> next;
                curr = *head;
                free(temp);
            }
            else {
                Node *temp = curr;
                prev -> next = curr -> next;
                curr = curr -> next;
                free(temp);
            }
        }
        else {
            prev = curr;
            curr = curr -> next;
        }
    }
}

void printList(Node* head) {
    while (head) {
        printf("%d ", head -> data);
        head = head -> next;
    }
    printf("\n");
}

int main() {
    Node* MyList = NULL;
    addNode(&MyList, 10);
    addNode(&MyList, 20);
    addNode(&MyList, 30);
    addNode(&MyList, 40);
    addNode(&MyList, 50);
    printList(MyList);
    removeOutsideRange(&MyList, 20, 40);
    printList(MyList);
    return 0;
}