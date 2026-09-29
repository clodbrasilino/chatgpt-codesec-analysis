#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int convert_string_tuple(const char *const input[], size_t count, int **output)
{
    int *values;
    size_t i;

    if (input == NULL || output == NULL || count == 0 ||
        count > SIZE_MAX / sizeof(*values)) {
        return -1;
    }

    *output = NULL;
    values = malloc(count * sizeof(*values));
    if (values == NULL) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        char *end;
        long value;

        if (input[i] == NULL || input[i][0] == '\0') {
            free(values);
            return -1;
        }

        errno = 0;
        end = NULL;
        value = strtol(input[i], &end, 10);

        if (errno == ERANGE || end == input[i] || *end != '\0' ||
            value < INT_MIN || value > INT_MAX) {
            free(values);
            return -1;
        }

        values[i] = (int)value;
    }

    *output = values;
    return 0;
}

int main(void)
{
    const char *string_tuple[] = {"10", "-20", "30", "40"};
    const size_t count = sizeof(string_tuple) / sizeof(string_tuple[0]);
    int *integer_tuple = NULL;
    size_t i;

    if (convert_string_tuple(string_tuple, count, &integer_tuple) != 0) {
        fputs("Conversion failed\n", stderr);
        return EXIT_FAILURE;
    }

    putchar('(');
    for (i = 0; i < count; ++i) {
        if (i != 0) {
            fputs(", ", stdout);
        }
        printf("%d", integer_tuple[i]);
    }
    puts(")");

    free(integer_tuple);
    return EXIT_SUCCESS;
}