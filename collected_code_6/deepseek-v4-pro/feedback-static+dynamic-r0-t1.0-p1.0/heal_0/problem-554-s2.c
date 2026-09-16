#include <stdio.h>
#include <stdlib.h>

int *find_odd_numbers(const int *list, size_t size, size_t *odd_count) {
    int *odd_numbers = NULL;
    size_t count = 0;
    size_t i;

    if (list == NULL || odd_count == NULL) {
        return NULL;
    }

    for (i = 0; i < size; i++) {
        if (list[i] % 2 != 0) {
            count++;
        }
    }

    if (count > 0) {
        odd_numbers = (int *)malloc(count * sizeof(int));
        if (odd_numbers == NULL) {
            return NULL;
        }

        count = 0;
        for (i = 0; i < size; i++) {
            if (list[i] % 2 != 0) {
                odd_numbers[count++] = list[i];
            }
        }
    }

    *odd_count = count;
    return odd_numbers;
}

int main(void) {
    int mixed_list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t list_size = sizeof(mixed_list) / sizeof(mixed_list[0]);
    size_t odd_count = 0;
    int *odd_numbers = NULL;
    size_t i;

    odd_numbers = find_odd_numbers(mixed_list, list_size, &odd_count);

    if (odd_numbers == NULL && odd_count > 0) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Odd numbers found: ");
    for (i = 0; i < odd_count; i++) {
        printf("%d ", odd_numbers[i]);
    }
    printf("\n");

    free(odd_numbers);
    odd_numbers = NULL;

    return 0;
}