#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

static int read_int64(int64_t *result)
{
    char buffer[128];
    char *end;
    int64_t value;

    if (result == NULL || fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -1;
    }

    errno = 0;
    value = strtoimax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *result = value;
    return 0;
}

static int read_size(size_t *result)
{
    char buffer[128];
    char *end;
    uintmax_t value;

    if (result == NULL || fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -1;
    }

    errno = 0;
    value = strtoumax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || value == 0 || value > SIZE_MAX) {
        return -1;
    }

    *result = (size_t)value;
    return 0;
}

static int cube_int64(int64_t value, int64_t *result)
{
    if (result == NULL || value > INT64_C(2097151) ||
        value < -INT64_C(2097152)) {
        return -1;
    }

    *result = value * value * value;
    return 0;
}

int main(void)
{
    size_t count;
    int64_t *values;

    if (printf("Enter the number of elements: ") < 0 || fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (read_size(&count) != 0 ||
        count > SIZE_MAX / sizeof(*values)) {
        fprintf(stderr, "Invalid element count.\n");
        return EXIT_FAILURE;
    }

    values = malloc(count * sizeof(*values));
    if (values == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (printf("Element %zu: ", i + 1) < 0 ||
            fflush(stdout) == EOF ||
            read_int64(&values[i]) != 0) {
            fprintf(stderr, "Invalid input.\n");
            free(values);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        int64_t cube;

        if (cube_int64(values[i], &cube) != 0) {
            fprintf(stderr,
                    "Cube of element %zu is outside the int64_t range.\n",
                    i + 1);
            free(values);
            return EXIT_FAILURE;
        }

        if (printf("%" PRId64 "%c", cube,
                   i + 1 == count ? '\n' : ' ') < 0) {
            free(values);
            return EXIT_FAILURE;
        }
    }

    free(values);
    return EXIT_SUCCESS;
}