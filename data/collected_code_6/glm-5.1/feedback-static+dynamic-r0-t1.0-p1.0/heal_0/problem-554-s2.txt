#include <stdio.h>
#include <stdlib.h>

int *find_odd_numbers(const int *list, size_t size, size_t *out_size) {
    if (list == NULL || out_size == NULL) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < size; i++) {
        if (list[i] % 2 != 0) {
            count++;
        }
    }

    int *odd_list = (int *)malloc(count * sizeof(int));
    if (odd_list == NULL) {
        *out_size = 0;
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; i < size; i++) {
        if (list[i] % 2 != 0) {
            odd_list[index++] = list[i];
        }
    }

    *out_size = count;
    return odd_list;
}

int main(void) {
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t size = sizeof(list) / sizeof(list[0]);
    size_t out_size = 0;

    int *odd_numbers = find_odd_numbers(list, size, &out_size);

    if (odd_numbers != NULL) {
        for (size_t i = 0; i < out_size; i++) {
            printf("%d ", odd_numbers[i]);
        }
        printf("\n");
        free(odd_numbers);
    }

    return 0;
}