#include <stdio.h>
#include <stdlib.h>

int *find_odd_numbers(const int *input, size_t input_size, size_t *result_size) {
    if (input == NULL || result_size == NULL) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < input_size; i++) {
        if (input[i] % 2 != 0) {
            count++;
        }
    }

    int *result = NULL;
    if (count > 0) {
        result = (int *)malloc(count * sizeof(int));
        if (result == NULL) {
            return NULL;
        }
    }

    size_t index = 0;
    for (size_t i = 0; i < input_size; i++) {
        if (input[i] % 2 != 0) {
            result[index] = input[i];
            index++;
        }
    }

    *result_size = count;
    return result;
}

int main(void) {
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t list_size = sizeof(list) / sizeof(list[0]);
    size_t odd_count = 0;

    int *odd_numbers = find_odd_numbers(list, list_size, &odd_count);

    if (odd_numbers != NULL) {
        for (size_t i = 0; i < odd_count; i++) {
            printf("%d ", odd_numbers[i]);
        }
        printf("\n");
        free(odd_numbers);
        odd_numbers = NULL;
    } else {
        if (odd_count > 0) {
            return EXIT_FAILURE;
        }
        printf("No odd numbers found.\n");
    }

    return EXIT_SUCCESS;
}