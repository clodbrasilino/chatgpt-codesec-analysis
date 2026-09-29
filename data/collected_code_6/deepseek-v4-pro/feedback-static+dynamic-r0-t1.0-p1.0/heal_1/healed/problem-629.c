#include <stdio.h>
#include <stdlib.h>

int* find_even_numbers(const int* list, int size, int* even_count) {
    if (list == NULL || size <= 0 || even_count == NULL) {
        if (even_count != NULL) *even_count = 0;
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < size; i++) {
        if (list[i] % 2 == 0) {
            count++;
        }
    }

    if (count == 0) {
        *even_count = 0;
        return NULL;
    }

    int* result = (int*)malloc(count * sizeof(int));
    if (result == NULL) {
        *even_count = 0;
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < size; i++) {
        if (list[i] % 2 == 0) {
            result[index++] = list[i];
        }
    }

    *even_count = count;
    return result;
}

int main(void) {
    int mixed_list[] = {3, 8, 5, 12, 7, 16, 9, 2, 11, 14, -4, 23, 18, 6, 1};
    int size = sizeof(mixed_list) / sizeof(mixed_list[0]);
    int even_count = 0;

    int* evens = find_even_numbers(mixed_list, size, &even_count);

    if (evens != NULL && even_count > 0) {
        printf("Even numbers: ");
        for (int i = 0; i < even_count; i++) {
            printf("%d", evens[i]);
            if (i < even_count - 1) {
                printf(", ");
            }
        }
        printf("\n");
        free(evens);
    } else {
        printf("No even numbers found or invalid input.\n");
    }

    return 0;
}