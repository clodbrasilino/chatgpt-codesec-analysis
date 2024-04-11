#include <stdio.h>

#define SIZE 5

void multiplyLists(int list1[], int list2[], int result[], int size) {
    for(int i = 0; i < size; i++) {
        result[i] = list1[i] * list2[i];
    }
}

int main() {
    int list1[SIZE] = {1, 2, 3, 4, 5};
    int list2[SIZE] = {6, 7, 8, 9, 10};
    int result[SIZE];

    multiplyLists(list1, list2, result, SIZE);

    for(int i = 0; i < SIZE; i++) {
        printf("%d ", result[i]);
    }

    return 0;
}