#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
void printDuplicates(int *arr, int size) {
    int *freq = (int *)calloc(size, sizeof(int));
    for (int i = 0; i < size; ++i) {
        if (arr[i] >= 0 && arr[i] < size) {
            freq[arr[i]]++;
        }
    }
    for (int i = 0; i < size; ++i) {
        if (freq[i] > 1) {
            printf("%d ", i);
        }
    }
    free(freq);
}

int main() {
    int arr[] = {1, 2, 3, 2, 1, 5, 6, 5, 5, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    printDuplicates(arr, size);
    return 0;
}