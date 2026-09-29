#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

static int parse_number(const char *str, long *value)
{
    char *end;
    long result;

    if (str == NULL || value == NULL) {
        return -1;
    }

    errno = 0;
    result = strtol(str, &end, 10);

    if (errno == ERANGE) {
        return -1;
    }
    if (end == str || *end != '\0') {
        return -1;
    }

    *value = result;
    return 0;
}

static int compare_numeric(const void *a, const void *b)
{
    const char *sa = *(const char *const *)a;
    const char *sb = *(const char *const *)b;
    long va = 0;
    long vb = 0;

    (void)parse_number(sa, &va);
    (void)parse_number(sb, &vb);

    if (va < vb) {
        return -1;
    }
    if (va > vb) {
        return 1;
    }
    return 0;
}

int sort_numeric_strings(char **strings, size_t count)
{
    size_t i;
    long value;

    if (strings == NULL) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        if (strings[i] == NULL) {
            return -1;
        }
        if (parse_number(strings[i], &value) != 0) {
            return -1;
        }
    }

    if (count > 1) {
        qsort(strings, count, sizeof(char *), compare_numeric);
    }

    return 0;
}

int main(void)
{
    char *numbers[] = { "42", "7", "-13", "1000", "0", "256", "-99" };
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    size_t i;

    if (sort_numeric_strings(numbers, count) != 0) {
        if (fprintf(stderr, "Error: invalid numeric string in input\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        if (printf("%s\n", numbers[i]) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}