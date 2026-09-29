#include <stdio.h>
#include <stdlib.h>

int choosePoints(const int *range1, const int *range2, int size, int **result1, int **result2) {
    int count1 = 0, count2 = 0;
    for (int i = 0; i < size; i++) {
        if (range1[i] < range2[0] || range1[i] > range2[size-1]) {
            (*result1)[count1++] = range1[i];
        }
        if (range2[i] < range1[0] || range2[i] > range1[size-1]) {
            (*result2)[count2++] = range2[i];
        }
    }
    return count1 + count2;
}

int main() {
    const int range1[] = {1, 3, 5, 7, 9};
    const int range2[] = {2, 4, 6, 8, 10};
    int size = 5;

    int *result1 = (int *)malloc(size * sizeof(int));
    int *result2 = (int *)malloc(size * sizeof(int));

    if (result1 == NULL || result2 == NULL) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    int totalUniquePoints = choosePoints(range1, range2, size, &result1, &result2);

    printf("Result from Range 1: ");
    for (int i = 0; i < totalUniquePoints / 2; i++) {
        if (result1[i] != 0) {
            printf("%d ", result1[i]);
        }
    }
    printf("\n");

    printf("Result from Range 2: ");
    for (int i = 0; i < totalUniquePoints / 2; i++) {
        if (result2[i] != 0) {
            printf("%d ", result2[i]);
        }
    }
    printf("\n");

    free(result1);
    free(result2);

    return 0;
}