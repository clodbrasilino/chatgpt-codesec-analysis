#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
void printDuplicates(int *arr, int size) {
    int *count = (int *)calloc(size, sizeof(int));
    if (!count) {
        return;
    }
    for (int i = 0; i < size; ++i) {
        count[arr[i]]++;
    }
    for (int i = 0; i < size; ++i) {
        if (count[i] > 1) {
            printf("%d ", i);
        }
    }
    free(count);
}

int main() {
    int arr[] = {1, 2, 3, 2, 4, 5, 3, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    printDuplicates(arr, size);
    return 0;
}