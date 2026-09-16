#include <stdio.h>
#include <stdlib.h>

static int print_lucky_numbers(int n)
{
    if (n <= 0 || n > 100000) {
        return -1;
    }

    size_t limit = (size_t)n * 25u + 100u;
    long *arr = malloc(limit * sizeof *arr);
    if (arr == NULL) {
        return -1;
    }

    size_t count = 0;
    for (size_t i = 1; i <= limit; i += 2) {
        arr[count] = (long)i;
        count++;
    }

    size_t idx = 1;
    while (idx < count) {
        size_t step = (size_t)arr[idx];
        if (step > count) {
            break;
        }
        size_t kept = 0;
        for (size_t i = 0; i < count; i++) {
            if ((i + 1u) % step != 0u) {
                arr[kept] = arr[i];
                kept++;
            }
        }
        count = kept;
        idx++;
    }

    if (count < (size_t)n) {
        free(arr);
        return -1;
    }

    for (size_t i = 0; i < (size_t)n; i++) {
        if (printf("%ld ", arr[i]) < 0) {
            free(arr);
            return -1;
        }
    }

    if (printf("\n") < 0) {
        free(arr);
        return -1;
    }

    free(arr);
    return 0;
}

int main(void)
{
    int n = 20;

    if (print_lucky_numbers(n) != 0) {
        if (fprintf(stderr, "Failed to generate lucky numbers\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}