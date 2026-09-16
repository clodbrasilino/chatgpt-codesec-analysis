#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int convert_tuple(const char *const strings[], size_t count, int **result)
{
    int *values;
    size_t i;

    if (strings == NULL || result == NULL || count == 0 ||
        count > SIZE_MAX / sizeof(*values)) {
        return -1;
    }

    *result = NULL;
    values = malloc(count * sizeof(*values));
    if (values == NULL) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        char *end;
        long value;

        if (strings[i] == NULL || strings[i][0] == '\0') {
            free(values);
            return -1;
        }

        errno = 0;
        end = NULL;
        value = strtol(strings[i], &end, 10);

        if (errno == ERANGE || end == strings[i] || *end != '\0' ||
            value < INT_MIN || value > INT_MAX) {
            free(values);
            return -1;
        }

        values[i] = (int)value;
    }

    *result = values;
    return 0;
}

int main(void)
{
    const char *strings[] = {"10", "-20", "30", "40"};
    const size_t count = sizeof(strings) / sizeof(strings[0]);
    int *values = NULL;
    size_t i;

    if (convert_tuple(strings, count, &values) != 0) {
        fputs("Conversion failed\n", stderr);
        return EXIT_FAILURE;
    }

    putchar('(');
    for (i = 0; i < count; ++i) {
        if (i != 0) {
            fputs(", ", stdout);
        }
        printf("%d", values[i]);
    }
    puts(")");

    free(values);
    return EXIT_SUCCESS;
}