#include <stdio.h>
#include <stdlib.h>

void print_duplicates(int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return;
    }

    int *temp = malloc(size * sizeof(int));
    if (temp == NULL) {
        return;
    }

    for (size_t i = 0; i < size; i++) {
        temp[i] = arr[i];
    }

    for (size_t i = 0; i < size; i++) {
        for (size_t j = i + 1; j < size; j++) {
            if (temp[i] > temp[j]) {
                int swap = temp[i];
                temp[i] = temp[j];
                temp[j] = swap;
            }
        }
    }

    int printed = 0;
    size_t i = 0;
    while (i < size) {
        size_t j = i + 1;
        while (j < size && temp[j] == temp[i]) {
            j++;
        }
        if (j - i > 1) {
            if (printed) {
                printf(" ");
            }
            printf("%d", temp[i]);
            printed = 1;
        }
        i = j;
    }

    if (printed) {
        printf("\n");
    }

    free(temp);
}

int main(void) {
    int arr[] = {4, 2, 5, 2, 4, 4, 7, 9, 9};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    print_duplicates(arr, size);

    return 0;
}