#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int strings_to_integers(const char *const strings[], size_t count, int **integers)
{
    int *result;
    size_t i;

    if (strings == NULL || integers == NULL) {
        return -1;
    }

    *integers = NULL;

    if (count == 0) {
        return 0;
    }

    if (count > SIZE_MAX / sizeof(*result)) {
        return -1;
    }

    result = malloc(count * sizeof(*result));
    if (result == NULL) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        char *end;
        long value;

        if (strings[i] == NULL || strings[i][0] == '\0') {
            free(result);
            return -1;
        }

        errno = 0;
        end = NULL;
        value = strtol(strings[i], &end, 10);

        if (errno == ERANGE || end == strings[i] || *end != '\0' ||
            value < INT_MIN || value > INT_MAX) {
            free(result);
            return -1;
        }

        result[i] = (int)value;
    }

    *integers = result;
    return 0;
}

int main(void)
{
    const char *values[] = {"42", "-7", "1000", "0"};
    const size_t count = sizeof(values) / sizeof(values[0]);
    int *integers = NULL;
    size_t i;

    if (strings_to_integers(values, count, &integers) != 0) {
        fputs("Conversion failed\n", stderr);
        return EXIT_FAILURE;
    }

    putchar('(');
    for (i = 0; i < count; ++i) {
        if (i != 0) {
            fputs(", ", stdout);
        }
        printf("%d", integers[i]);
    }
    puts(")");

    free(integers);
    return EXIT_SUCCESS;
}