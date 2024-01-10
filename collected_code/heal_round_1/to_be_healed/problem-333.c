#include <stdio.h>

void swap(int* a, int* b) {
    /* Possible weaknesses found:
     *  Cannot determine that '*a' is initialized [premium-bughuntingUninit]
     */
    int temp = *a;
    /* Possible weaknesses found:
     *  Cannot determine that '*b' is initialized [premium-bughuntingUninit]
     */
    *a = *b;
    *b = temp;
}

void sortList(int arr[][2], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[j+1][1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'arr[j][1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (arr[j][1] > arr[j + 1][1]) {
                swap(&arr[j][0], &arr[j + 1][0]);
                swap(&arr[j][1], &arr[j + 1][1]);
            }
        }
    }
}

int main() {
    int arr[][2] = {{1, 4}, {2, 3}, {3, 2}, {4, 1}, {5, 5}};
    int size = sizeof(arr) / sizeof(arr[0]);

    sortList(arr, size);

    for (int i = 0; i < size; i++) {
        printf("(%d, %d) ", arr[i][0], arr[i][1]);
    }

    return 0;
}