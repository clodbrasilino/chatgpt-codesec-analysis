#include <stdio.h>
#include <stdlib.h>

static int product_is_even(const long long *numbers, size_t count)
{
    size_t i;

    if (numbers == NULL || count == 0U) {
        return -1;
    }

    for (i = 0U; i < count; ++i) {
        if (numbers[i] % 2LL == 0LL) {
            return 1;
        }
    }

    return 0;
}

int main(void)
{
    size_t count;
    size_t i;
    long long *numbers;
    int result;

    if (scanf("%zu", &count) != 1 || count == 0U ||
        count > SIZE_MAX / sizeof(*numbers)) {
        return EXIT_FAILURE;
    }

    numbers = malloc(count * sizeof(*numbers));
    if (numbers == NULL) {
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; ++i) {
        if (scanf("%lld", &numbers[i]) != 1) {
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    result = product_is_even(numbers, count);
    free(numbers);

    if (result < 0) {
        return EXIT_FAILURE;
    }

    puts(result == 1 ? "Even" : "Odd");
    return EXIT_SUCCESS;
}