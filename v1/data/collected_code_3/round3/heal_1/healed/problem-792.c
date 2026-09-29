#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

int countLists(struct Node* arr[], int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] != NULL) {
            count++;
        }
    }
    return count;
}

int main() {
    int n = 5;
    struct Node* arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = NULL;
    }
    arr[0] = (struct Node*)malloc(sizeof(struct Node));
    arr[2] = (struct Node*)malloc(sizeof(struct Node));
    arr[4] = (struct Node*)malloc(sizeof(struct Node));
    printf("Number of lists: %d\n", countLists(arr, n));
    return 0;
}