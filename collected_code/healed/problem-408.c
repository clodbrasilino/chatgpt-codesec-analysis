#include <stdio.h>

void findPairs(const int arr1[], int size1, const int arr2[], int size2, int k) {
    int count = 0;
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            printf("(%d, %d)\n", arr1[i], arr2[j]);
            count++;
            if (count == k) {
                return;
            }
        }
    }
}

int main() {
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5, 6};
    int k = 3;

    findPairs(arr1, sizeof(arr1) / sizeof(arr1[0]), arr2, sizeof(arr2) / sizeof(arr2[0]), k);

    return 0;
}