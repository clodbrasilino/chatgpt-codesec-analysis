#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    if(node == NULL) {
        return NULL;
    }

    node->data = data;
    node->next = NULL;
    return node;
}

int compareLists(struct Node* list1, struct Node* list2) {
    while (list1 != NULL && list2 != NULL) {
        if (list1->data != list2->data) {
            return 0;
        }
        list1 = list1->next;
        list2 = list2->next;
    }
    return (list1 == NULL && list2 == NULL);
}

int countUniqueLists(struct Node** arr, int n) {
    int count = n;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (compareLists(arr[i], arr[j])) {
                count--;
                break;
            }
        }
    }
    return count;
}

int main() {
    struct Node* arr[5];

    arr[0] = newNode(1);
    if(arr[0] != NULL){
        arr[0]->next = newNode(2);
        if(arr[0]->next != NULL){
            arr[0]->next->next = newNode(3);
        }
    }

    arr[1] = newNode(1);
    if(arr[1] != NULL){
        arr[1]->next = newNode(2);
        if(arr[1]->next != NULL){
            arr[1]->next->next = newNode(3);
        }
    }

    arr[2] = newNode(1);
    if( arr[2] != NULL){
        arr[2]->next = newNode(2);
    }

    arr[3] = newNode(1);
    if(arr[3] != NULL){
        arr[3]->next = newNode(2);
        if(arr[3]->next != NULL){
            arr[3]->next->next = newNode(3);
        }
    }

    arr[4] = newNode(1);
    if(arr[4] != NULL){
        arr[4]->next = newNode(2);
    }

    printf("Number of unique lists: %d\n", countUniqueLists(arr, 5));

    return 0;
}