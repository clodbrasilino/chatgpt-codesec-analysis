#include <stdio.h>
#include <stdlib.h>

int* find_consecutive_differences(const int *list, int size, int *diff_size) {
    /* Possible weaknesses found:
     *  Assuming that condition 'diff_size==NULL' is not redundant
     */
    if (list == NULL || size <= 1 || diff_size == NULL) {
        /* Possible weaknesses found:
         *  Either the condition 'diff_size==NULL' is redundant or there is possible null pointer dereference: diff_size. [nullPointerRedundantCheck]
         *  Null pointer dereference
         */
        *diff_size = 0;
        return NULL;
    }

    int *differences = (int *)malloc((size - 1) * sizeof(int));
    if (differences == NULL) {
        *diff_size = 0;
        return NULL;
    }

    for (int i = 0; i < size - 1; i++) {
        differences[i] = list[i + 1] - list[i];
    }

    *diff_size = size - 1;
    return differences;
}

int main(void) {
    int numbers[] = {4, 9, 15, 22, 30};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int diff_size = 0;

    int *diffs = find_consecutive_differences(numbers, size, &diff_size);

    if (diffs == NULL) {
        printf("Error: unable to compute differences\n");
        return 1;
    }

    printf("Differences: ");
    for (int i = 0; i < diff_size; i++) {
        printf("%d ", diffs[i]);
    }
    printf("\n");

    free(diffs);
    return 0;
}