#include <stdio.h>
#include <stdlib.h>

int isSubset(const int *arr1, int size1, const int *arr2, int size2) {
    if (arr1 == NULL || arr2 == NULL) {
        return 0;
    }

    if (size2 > size1) {
        return 0;
    }

    int *visited = (int *)calloc(size1, sizeof(int));
    if (visited == NULL) {
        return 0;
    }

    for (int i = 0; i < size2; i++) {
        int found = 0;
        for (int j = 0; j < size1; j++) {
            if (arr2[i] == arr1[j] && !visited[j]) {
                visited[j] = 1;
                found = 1;
                break;
            }
        }
        if (!found) {
            free(visited);
            return 0;
        }
    }

    free(visited);
    return 1;
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5, 1};
    int arr2[] = {1, 2, 1};
    int arr3[] = {1, 2, 6};

    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int size3 = sizeof(arr3) / sizeof(arr3[0]);

    int result1 = isSubset(arr1, size1, arr2, size2);
    int result2 = isSubset(arr1, size1, arr3, size3);

    printf("%d\n", result1);
    printf("%d\n", result2);

    return 0;
}