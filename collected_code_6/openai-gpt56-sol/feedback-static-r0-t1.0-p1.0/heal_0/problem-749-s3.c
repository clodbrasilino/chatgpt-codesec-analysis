#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int compare_numeric_strings(const void *lhs, const void *rhs)
{
    const char *left = *(const char *const *)lhs;
    const char *right = *(const char *const *)rhs;
    char *left_end = NULL;
    char *right_end = NULL;
    long double left_value;
    long double right_value;
    int left_errno;
    int right_errno;

    errno = 0;
    left_value = strtold(left, &left_end);
    left_errno = errno;

    errno = 0;
    right_value = strtold(right, &right_end);
    right_errno = errno;

    if (left_end == left || *left_end != '\0' || left_errno == ERANGE) {
        if (right_end == right || *right_end != '\0' || right_errno == ERANGE) {
            return strcmp(left, right);
        }
        return 1;
    }

    if (right_end == right || *right_end != '\0' || right_errno == ERANGE) {
        return -1;
    }

    if (left_value < right_value) {
        return -1;
    }
    if (left_value > right_value) {
        return 1;
    }

    return strcmp(left, right);
}

static void sort_numeric_strings(char **strings, size_t count)
{
    if (strings != NULL && count > 1U) {
        qsort(strings, count, sizeof(*strings), compare_numeric_strings);
    }
}

int main(int argc, char *argv[])
{
    size_t count;
    size_t i;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s number [number ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    count = (size_t)(argc - 1);
    sort_numeric_strings(&argv[1], count);

    for (i = 0U; i < count; ++i) {
        if (puts(argv[i + 1U]) == EOF) {
            fprintf(stderr, "Failed to write output\n");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}