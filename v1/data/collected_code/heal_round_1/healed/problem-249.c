#include <stdio.h>

void findIntersection(const int arr1[], int size1, const int arr2[], int size2) {
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            if (arr1[i] == arr2[j]) {
                printf("%d ", arr1[i]);
                break;
            }
        }
    }
}

int main() {
    const int arr1[] = {1, 2, 3, 4, 5};
    const int arr2[] = {4, 5, 6, 7, 8};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);

    findIntersection(arr1, size1, arr2, size2);

    return 0;
}