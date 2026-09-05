#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generateCombinations(int *arr, int n, int r, int index, int *data, int i) {
    if (index == r) {
        printf("{");
        for (int j = 0; j < r; j++) {
            printf("%d", data[j]);
            if (j < r - 1) {
                printf(", ");
            }
        }
        printf("}\n");
        return;
    }

    if (i >= n) {
        return;
    }

    data[index] = arr[i];
    generateCombinations(arr, n, r, index + 1, data, i + 1);

    generateCombinations(arr, n, r, index, data, i + 1);
}

void findAllCombinations(int *arr, int n) {
    if (arr == NULL || n <= 0) {
        fprintf(stderr, "Invalid input\n");
        return;
    }

    for (int r = 1; r <= n; r++) {
        int *data = (int *)malloc(r * sizeof(int));
        if (data == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return;
        }
        generateCombinations(arr, n, r, 0, data, 0);
        free(data);
        data = NULL;
    }
}

int main(void) {
    int arr[] = {1, 2, 3, 4};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    if (n == 0) {
        fprintf(stderr, "Array is empty\n");
        return EXIT_FAILURE;
    }

    printf("All possible combinations:\n");
    findAllCombinations(arr, (int)n);

    return EXIT_SUCCESS;
}