#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

size_t remove_odd_numbers(const int *input, size_t count, int **output)
{
    size_t even_count;
    size_t i;
    size_t j;
    int *result;

    if (output == NULL) {
        return 0;
    }
    *output = NULL;

    if (input == NULL || count == 0) {
        return 0;
    }

    even_count = 0;
    for (i = 0; i < count; i++) {
        if (input[i] % 2 == 0) {
            even_count++;
        }
    }

    if (even_count == 0) {
        return 0;
    }

    if (even_count > SIZE_MAX / sizeof(int)) {
        return 0;
    }

    result = malloc(even_count * sizeof(int));
    if (result == NULL) {
        return 0;
    }

    j = 0;
    for (i = 0; i < count; i++) {
        if (input[i] % 2 == 0) {
            result[j] = input[i];
            j++;
        }
    }

    *output = result;
    return even_count;
}

int main(void)
{
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t count;
    int *evens;
    size_t even_count;

    count = sizeof(numbers) / sizeof(numbers[0]);
    evens = NULL;

    even_count = remove_odd_numbers(numbers, count, &evens);

    if (evens != NULL) {
        printf("Even numbers: ");
        for (size_t i = 0; i < even_count; i++) {
            printf("%d ", evens[i]);
        }
        printf("\n");
        free(evens);
        evens = NULL;
    } else {
        printf("No even numbers found or an error occurred.\n");
    }

    return 0;
}