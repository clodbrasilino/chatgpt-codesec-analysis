#include <stdio.h>
#include <stdlib.h>

int *filter_odd_numbers(const int *input, size_t input_size, size_t *output_size);
void print_array(const int *array, size_t size);

int *filter_odd_numbers(const int *input, size_t input_size, size_t *output_size)
{
    int *result = NULL;
    size_t count = 0;
    size_t i;

    if (output_size != NULL) {
        *output_size = 0;
    }

    if (input == NULL || output_size == NULL || input_size == 0) {
        return NULL;
    }

    for (i = 0; i < input_size; i++) {
        if (input[i] % 2 != 0) {
            count++;
        }
    }

    if (count == 0) {
        return NULL;
    }

    result = malloc(count * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    count = 0;
    for (i = 0; i < input_size; i++) {
        if (input[i] % 2 != 0) {
            result[count] = input[i];
            count++;
        }
    }

    *output_size = count;
    return result;
}

void print_array(const int *array, size_t size)
{
    size_t i;

    if (array == NULL || size == 0) {
        printf("[]\n");
        fflush(stdout);
        return;
    }

    printf("[");
    for (i = 0; i < size; i++) {
        printf("%d", array[i]);
        if (i + 1 < size) {
            printf(", ");
        }
    }
    printf("]\n");
    fflush(stdout);
}

int main(void)
{
    int test0[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int test1[] = {45, 22, 67, 88, 93, 100};
    int test2[] = {5, 7, 9, 3, 2, 4, 6};
    size_t odd_count = 0;
    int *odd_numbers;

    odd_numbers = filter_odd_numbers(test0, sizeof(test0) / sizeof(test0[0]), &odd_count);
    print_array(odd_numbers, odd_count);
    free(odd_numbers);
    odd_numbers = NULL;

    odd_numbers = filter_odd_numbers(test1, sizeof(test1) / sizeof(test1[0]), &odd_count);
    print_array(odd_numbers, odd_count);
    free(odd_numbers);
    odd_numbers = NULL;

    odd_numbers = filter_odd_numbers(test2, sizeof(test2) / sizeof(test2[0]), &odd_count);
    print_array(odd_numbers, odd_count);
    free(odd_numbers);
    odd_numbers = NULL;

    return EXIT_SUCCESS;
}