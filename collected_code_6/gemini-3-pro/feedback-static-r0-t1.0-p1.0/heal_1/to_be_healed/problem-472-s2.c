#include <stdio.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
bool checkConsecutive(int arr[], int size) {
    if (size <= 0) {
        return false;
    }

    if (size == 1) {
        return true;
    }

    int min = arr[0];
    int max = arr[0];

    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    if (max - min + 1 != size) {
        return false;
    }

    bool visited[size];
    for (int i = 0; i < size; i++) {
        visited[i] = false;
    }

    for (int i = 0; i < size; i++) {
        int index = arr[i] - min;
        if (visited[index]) {
            return false;
        }
        visited[index] = true;
    }

    return true;
}

int main(void) {
    int arr1[] = {5, 2, 3, 1, 4};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    if (checkConsecutive(arr1, size1)) {
        printf("arr1 contains consecutive numbers\n");
    } else {
        printf("arr1 does not contain consecutive numbers\n");
    }

    int arr2[] = {83, 78, 80, 81, 79, 82};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    if (checkConsecutive(arr2, size2)) {
        printf("arr2 contains consecutive numbers\n");
    } else {
        printf("arr2 does not contain consecutive numbers\n");
    }

    int arr3[] = {34, 23, 52, 12, 3};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    if (checkConsecutive(arr3, size3)) {
        printf("arr3 contains consecutive numbers\n");
    } else {
        printf("arr3 does not contain consecutive numbers\n");
    }
    
    int arr4[] = {7, 7, 8, 9};
    int size4 = sizeof(arr4) / sizeof(arr4[0]);
    if (checkConsecutive(arr4, size4)) {
        printf("arr4 contains consecutive numbers\n");
    } else {
        printf("arr4 does not contain consecutive numbers\n");
    }

    return 0;
}