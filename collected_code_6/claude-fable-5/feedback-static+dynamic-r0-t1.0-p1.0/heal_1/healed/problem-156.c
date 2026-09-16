#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

int convert_string_tuple_to_int_tuple(const char **strings, size_t count, long **result)
{
    long *values;
    size_t i;
    char *endptr;

    if (strings == NULL || result == NULL || count == 0) {
        return -1;
    }

    if (count > SIZE_MAX / sizeof(long)) {
        return -1;
    }

    values = malloc(count * sizeof(long));
    if (values == NULL) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        long parsed;

        if (strings[i] == NULL || strings[i][0] == '\0') {
            free(values);
            return -1;
        }

        errno = 0;
        parsed = strtol(strings[i], &endptr, 10);

        if (errno == ERANGE) {
            free(values);
            return -1;
        }

        if (endptr == strings[i] || *endptr != '\0') {
            free(values);
            return -1;
        }

        values[i] = parsed;
    }

    *result = values;
    return 0;
}

int main(void)
{
    const char *string_tuple[] = { "10", "-25", "300", "4096" };
    size_t count = sizeof(string_tuple) / sizeof(string_tuple[0]);
    long *int_tuple = NULL;
    size_t i;

    if (convert_string_tuple_to_int_tuple(string_tuple, count, &int_tuple) != 0) {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }

    printf("(");
    for (i = 0; i < count; i++) {
        printf("%ld", int_tuple[i]);
        if (i < count - 1) {
            printf(", ");
        }
    }
    printf(")\n");

    free(int_tuple);
    int_tuple = NULL;

    return EXIT_SUCCESS;
}