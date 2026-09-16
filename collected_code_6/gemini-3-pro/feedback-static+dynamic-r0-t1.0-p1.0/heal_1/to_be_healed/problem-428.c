#include <stdio.h>
#include <stdlib.h>

void shellSort(int arr[], int n) {
    if (arr == NULL || n <= 0) {
        return;
    }

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i += 1) {
            int temp = arr[i];
            int j;            
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
void printArray(int arr[], int n) {
    if (arr == NULL || n <= 0) {
        return;
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    int arr[] = {12, 34, 54, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    printArray(arr, n);
    shellSort(arr, n);
    printArray(arr, n);

    return 0;
}