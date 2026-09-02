#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define ARRAY_SIZE 10
#define HASH_SIZE 1000

int find_first_duplicate(const int *arr, int size) {
    if (arr == NULL || size <= 0) {
        return INT_MIN;
    }

    int *hash_table = (int *)calloc(HASH_SIZE, sizeof(int));
    if (hash_table == NULL) {
        return INT_MIN;
    }

    for (int i = 0; i < size; i++) {
        int index = arr[i] % HASH_SIZE;
        if (index < 0) {
            index += HASH_SIZE;
        }

        if (hash_table[index] == 1) {
            free(hash_table);
            return arr[i];
        }
        hash_table[index] = 1;
    }

    free(hash_table);
    return INT_MIN;
}

int main(void) {
    const int arr[ARRAY_SIZE] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    int result = find_first_duplicate(arr, ARRAY_SIZE);

    if (result != INT_MIN) {
        printf("First duplicate: %d\n", result);
    } else {
        printf("No duplicate found\n");
    }

    return 0;
}