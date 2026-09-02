#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int findMinAndIndices(int *arr, int len, int **indices, int *indexCount) {
    int min = INT_MAX;
    for (int i = 0; i < len; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }

    *indexCount = 0;
    for (int i = 0; i < len; i++) {
        if (arr[i] == min) {
            (*indexCount)++;
        }
    }

    *indices = (int *)malloc((*indexCount) * sizeof(int));
    if (*indices == NULL) {
        return -1;
    }

    int idx = 0;
    for (int i = 0; i < len; i++) {
        if (arr[i] == min) {
            (*indices)[idx++] = i;
        }
    }

    return 0;
}

int main() {
    int arr[] = {3, 1, 4, 1, 5, 9, 1};
    int len = sizeof(arr) / sizeof(arr[0]);
    int *indices = NULL;
    int indexCount;

    if (findMinAndIndices(arr, len, &indices, &indexCount) == 0) {
        for (int i = 0; i < indexCount; i++) {
            printf("Index %d: %d\n", i, indices[i]);
        }
        free(indices);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}