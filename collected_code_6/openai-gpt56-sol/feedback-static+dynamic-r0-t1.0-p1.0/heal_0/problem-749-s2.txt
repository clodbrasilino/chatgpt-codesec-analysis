#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int compare_numeric_strings(const void *left, const void *right)
{
    const char *a = *(const char *const *)left;
    const char *b = *(const char *const *)right;
    char *a_end = NULL;
    char *b_end = NULL;
    long double a_value;
    long double b_value;
    int a_error;
    int b_error;

    errno = 0;
    a_value = strtold(a, &a_end);
    a_error = errno;

    errno = 0;
    b_value = strtold(b, &b_end);
    b_error = errno;

    if (a_error != 0 || a_end == a || *a_end != '\0') {
        return (b_error != 0 || b_end == b || *b_end != '\0')
                   ? strcmp(a, b)
                   : 1;
    }

    if (b_error != 0 || b_end == b || *b_end != '\0') {
        return -1;
    }

    if (a_value < b_value) {
        return -1;
    }

    if (a_value > b_value) {
        return 1;
    }

    return strcmp(a, b);
}

static int sort_numeric_strings(char **strings, size_t count)
{
    if (strings == NULL && count != 0U) {
        return -1;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (strings[i] == NULL) {
            return -1;
        }
    }

    qsort(strings, count, sizeof(*strings), compare_numeric_strings);
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s number [number ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (sort_numeric_strings(&argv[1], (size_t)(argc - 1)) != 0) {
        fprintf(stderr, "Failed to sort input\n");
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; ++i) {
        if (puts(argv[i]) == EOF) {
            fprintf(stderr, "Failed to write output\n");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}