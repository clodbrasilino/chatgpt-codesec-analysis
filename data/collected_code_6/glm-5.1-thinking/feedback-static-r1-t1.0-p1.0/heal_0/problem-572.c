#include <stdio.h>
#include <stdlib.h>

int count_occurrences(int *arr, int size, int value) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) {
            count++;
        }
    }
    return count;
}

int remove_two_duplicates(int *arr, int size, int **result) {
    if (arr == NULL || size <= 0 || result == NULL) {
        return 0;
    }

    int *temp = (int *)malloc(size * sizeof(int));
    if (temp == NULL) {
        return 0;
    }

    int new_size = 0;
    for (int i = 0; i < size; i++) {
        if (count_occurrences(arr, size, arr[i]) != 2) {
            temp[new_size] = arr[i];
            new_size++;
        }
    }

    if (new_size == 0) {
        free(temp);
        *result = NULL;
        return 0;
    }

    int *final = (int *)malloc(new_size * sizeof(int));
    if (final == NULL) {
        free(temp);
        return 0;
    }

    for (int i = 0; i < new_size; i++) {
        final[i] = temp[i];
    }

    free(temp);
    *result = final;
    return new_size;
}

int main(void) {
    int arr[] = {1, 2, 3, 2, 4, 5, 5, 6, 7};
    int size = sizeof(arr) / sizeof(arr[0]);
    int *result = NULL;

    printf("Original array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    int new_size = remove_two_duplicates(arr, size, &result);

    printf("After removing two duplicates: ");
    if (result != NULL) {
        for (int i = 0; i < new_size; i++) {
            printf("%d ", result[i]);
        }
        free(result);
    }
    printf("\n");

    return 0;
}