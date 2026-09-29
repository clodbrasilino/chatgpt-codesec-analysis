#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

int string_to_tuple(const char *str, long **tuple, size_t *count)
{
    size_t capacity = 8;
    size_t n = 0;
    long *result = NULL;
    const char *p = str;
    char *end = NULL;

    if (str == NULL || tuple == NULL || count == NULL) {
        return -1;
    }

    result = malloc(capacity * sizeof(long));
    if (result == NULL) {
        return -1;
    }

    while (*p != '\0') {
        while (*p != '\0' && (isspace((unsigned char)*p) || *p == ',')) {
            p++;
        }
        if (*p == '\0') {
            break;
        }

        errno = 0;
        long value = strtol(p, &end, 10);
        if (end == p || errno == ERANGE) {
            free(result);
            return -1;
        }

        if (n >= capacity) {
            if (capacity > SIZE_MAX / (2 * sizeof(long))) {
                free(result);
                return -1;
            }
            capacity *= 2;
            long *tmp = realloc(result, capacity * sizeof(long));
            if (tmp == NULL) {
                free(result);
                return -1;
            }
            result = tmp;
        }

        result[n] = value;
        n++;
        p = end;
    }

    if (n == 0) {
        free(result);
        return -1;
    }

    *tuple = result;
    *count = n;
    return 0;
}

void print_tuple(const long *tuple, size_t count)
{
    size_t i;

    if (tuple == NULL || count == 0) {
        return;
    }

    printf("(");
    for (i = 0; i < count; i++) {
        printf("%ld", tuple[i]);
        if (i + 1 < count) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void)
{
    const char *input = "1, 5, 4, 6, 7";
    long *tuple = NULL;
    size_t count = 0;

    if (string_to_tuple(input, &tuple, &count) != 0) {
        fprintf(stderr, "Failed to convert string to tuple\n");
        return EXIT_FAILURE;
    }

    print_tuple(tuple, count);
    free(tuple);
    tuple = NULL;

    return EXIT_SUCCESS;
}