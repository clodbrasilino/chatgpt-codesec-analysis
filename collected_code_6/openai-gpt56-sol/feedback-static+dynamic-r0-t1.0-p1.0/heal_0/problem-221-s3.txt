#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool find_first_even(const int numbers[], size_t count, int *result)
{
    if (numbers == NULL || result == NULL) {
        return false;
    }

    for (size_t i = 0; i < count; ++i) {
        if (numbers[i] % 2 == 0) {
            *result = numbers[i];
            return true;
        }
    }

    return false;
}

int main(void)
{
    size_t count = 0;

    if (scanf("%zu", &count) != 1 || count == 0 ||
        count > SIZE_MAX / sizeof(int)) {
        return EXIT_FAILURE;
    }

    int *numbers = malloc(count * sizeof(*numbers));
    if (numbers == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (scanf("%d", &numbers[i]) != 1) {
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    int first_even = 0;
    bool found = find_first_even(numbers, count, &first_even);

    free(numbers);

    if (found) {
        printf("%d\n", first_even);
    } else {
        puts("No even number found");
    }

    return EXIT_SUCCESS;
}