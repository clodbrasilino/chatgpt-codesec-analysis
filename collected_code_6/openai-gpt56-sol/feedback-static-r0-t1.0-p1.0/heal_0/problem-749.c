#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int compare_numeric_strings(const void *lhs, const void *rhs)
{
    const char *a = *(const char *const *)lhs;
    const char *b = *(const char *const *)rhs;
    char *end_a = NULL;
    char *end_b = NULL;
    long double value_a;
    long double value_b;
    int error_a;
    int error_b;

    errno = 0;
    value_a = strtold(a, &end_a);
    error_a = errno;

    errno = 0;
    value_b = strtold(b, &end_b);
    error_b = errno;

    if (error_a != 0 || end_a == a || *end_a != '\0') {
        return (error_b != 0 || end_b == b || *end_b != '\0')
                   ? strcmp(a, b)
                   : 1;
    }

    if (error_b != 0 || end_b == b || *end_b != '\0') {
        return -1;
    }

    if (value_a < value_b) {
        return -1;
    }

    if (value_a > value_b) {
        return 1;
    }

    return strcmp(a, b);
}

static int sort_numeric_strings(char **strings, size_t count)
{
    if (strings == NULL && count != 0U) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        if (strings[i] == NULL) {
            return -1;
        }
    }

    qsort(strings, count, sizeof(*strings), compare_numeric_strings);
    return 0;
}

int main(int argc, char *argv[])
{
    char **numbers;
    size_t count;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s NUMBER...\n", argv[0]);
        return EXIT_FAILURE;
    }

    count = (size_t)(argc - 1);

    if (count > SIZE_MAX / sizeof(*numbers)) {
        fprintf(stderr, "Too many arguments\n");
        return EXIT_FAILURE;
    }

    numbers = malloc(count * sizeof(*numbers));
    if (numbers == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        numbers[i] = argv[i + 1];
    }

    if (sort_numeric_strings(numbers, count) != 0) {
        fprintf(stderr, "Failed to sort strings\n");
        free(numbers);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (puts(numbers[i]) == EOF) {
            perror("puts");
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    free(numbers);

    if (fflush(stdout) == EOF) {
        perror("fflush");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}