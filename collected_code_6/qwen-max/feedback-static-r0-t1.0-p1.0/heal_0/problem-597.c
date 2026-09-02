#include <stdio.h>
#include <stdlib.h>

int findKthElement(int* arr1, int size1, int* arr2, int size2, int k) {
    if (k > size1 + size2 || k <= 0) return -1;
    int i = 0, j = 0;
    while (1) {
        if (i == size1) return arr2[j + k - 1];
        if (j == size2) return arr1[i + k - 1];
        if (k == 1) return (arr1[i] < arr2[j]) ? arr1[i] : arr2[j];
        int new_i = i + k / 2 - 1;
        int new_j = j + k / 2 - 1;
        new_i = (new_i < size1) ? new_i : size1 - 1;
        new_j = (new_j < size2) ? new_j : size2 - 1;
        if (arr1[new_i] <= arr2[new_j]) {
            k = k - (new_i - i + 1);
            i = new_i + 1;
        } else {
            k = k - (new_j - j + 1);
            j = new_j + 1;
        }
    }
}

int main() {
    int arr1[] = {1, 3, 5};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int arr2[] = {2, 4, 6};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int k = 4;
    int result = findKthElement(arr1, size1, arr2, size2, k);
    printf("The %dth element is: %d\n", k, result);
    return 0;
}