#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int add_consecutive(const int64_t *numbers, size_t count, int64_t *sum)
{
    int64_t total = 0;

    if (numbers == NULL || sum == NULL || count == 0U) {
        return -1;
    }

    for (size_t i = 0U; i < count; ++i) {
        if ((numbers[i] > 0 && total > INT64_MAX - numbers[i]) ||
            (numbers[i] < 0 && total < INT64_MIN - numbers[i])) {
            return -1;
        }
        total += numbers[i];
    }

    *sum = total;
    return 0;
}

int main(void)
{
    size_t count = 0U;
    int64_t *numbers = NULL;
    int64_t sum = 0;

    if (scanf("%zu", &count) != 1 || count == 0U ||
        count > SIZE_MAX / sizeof(*numbers)) {
        fprintf(stderr, "Invalid list size.\n");
        return EXIT_FAILURE;
    }

    numbers = malloc(count * sizeof(*numbers));
    if (numbers == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (scanf("%" SCNd64, &numbers[i]) != 1) {
            fprintf(stderr, "Invalid number.\n");
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    if (add_consecutive(numbers, count, &sum) != 0) {
        fprintf(stderr, "Unable to calculate sum.\n");
        free(numbers);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", sum);
    free(numbers);

    return EXIT_SUCCESS;
}