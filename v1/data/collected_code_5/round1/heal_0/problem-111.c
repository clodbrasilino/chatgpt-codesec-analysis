#include <stdio.h>

#define SIZE 5

void findCommon(int arr1[SIZE], int arr2[SIZE]) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (arr1[i] == arr2[j]) {
                printf("Common element : %d\n", arr1[i]);
                arr2[j] = -1;
                break;
            }
        }
    }
}

int main() {
    int list1[SIZE] = {5, 10, 15, 20, 25};
    int list2[SIZE] = {50, 15, 20, 75, 30};

    findCommon(list1, list2);

    return 0;
}