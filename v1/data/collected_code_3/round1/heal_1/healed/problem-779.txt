#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* newNode(int data) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    if(newNode == NULL){
        return NULL;
    }
    
    newNode->data = data;
    newNode->next = NULL;
    
    return newNode;
}

int compareLists(struct Node* a, struct Node* b) {
    while (a != NULL && b != NULL) {
        if (a->data != b->data)
            return 0;
            
        a = a->next;
        b = b->next;
    }
    
    return (a == NULL && b == NULL);
}

int countUnique(struct Node** arr, int n) {
    int count = 1;
    for (int i = 1; i < n; i++) {
        int j;
        for (j = 0; j < i; j++)
            if (compareLists(arr[i], arr[j]))
                break;
                
        if (i == j)
            count++;
    }
    
    return count;
}

int main() {
    struct Node* arr[5];
    
    arr[0] = newNode(10);
    if(arr[0] == NULL){
        return 1;
    }
    arr[0]->next = newNode(20);
    if(arr[0]->next == NULL){
        return 1;
    }
    arr[0]->next->next = newNode(30);
    if(arr[0]->next->next == NULL){
        return 1;
    }

    arr[1] = newNode(10);
    if(arr[1] == NULL){
        return 1;
    }
    arr[1]->next = newNode(20);
    if(arr[1]->next == NULL){
        return 1;
    }
    arr[1]->next->next = newNode(30);
    if(arr[1]->next->next == NULL){
        return 1;
    }

    arr[2] = newNode(40);
    if(arr[2] == NULL){
        return 1;
    }
    arr[2]->next = newNode(50);
    if(arr[2]->next == NULL){
        return 1;
    }

    arr[3] = newNode(10);
    if(arr[3] == NULL){
        return 1;
    }
    arr[3]->next = newNode(20);
    if(arr[3]->next == NULL){
        return 1;
    }
    arr[3]->next->next = newNode(30);
    if(arr[3]->next->next == NULL){
        return 1;
    }

    arr[4] = newNode(60);
    if(arr[4] == NULL){
        return 1;
    }

    printf("Number of unique lists: %d", countUnique(arr, 5));

    return 0;
}