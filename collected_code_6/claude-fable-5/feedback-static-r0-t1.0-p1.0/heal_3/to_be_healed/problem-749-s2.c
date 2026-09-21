#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#define MAX_NUM_STR_LEN 32U

static int parse_number(const char *str, long *result)
{
    char *endptr = NULL;
    long value;

    if (str == NULL || result == NULL) {
        return -1;
    }

    errno = 0;
    value = strtol(str, &endptr, 10);

    if (errno == ERANGE) {
        return -1;
    }
    if (endptr == str || *endptr != '\0') {
        return -1;
    }

    *result = value;
    return 0;
}

static int compare_numeric(const void *a, const void *b)
{
    const char *const *sa = (const char *const *)a;
    const char *const *sb = (const char *const *)b;
    long va = 0;
    long vb = 0;

    if (parse_number(*sa, &va) != 0) {
        va = 0;
    }
    if (parse_number(*sb, &vb) != 0) {
        vb = 0;
    }

    if (va < vb) {
        return -1;
    }
    if (va > vb) {
        return 1;
    }
    return 0;
}

static int sort_number_strings(char **strings, size_t count)
{
    size_t i;
    long dummy;

    if (strings == NULL || count == 0U) {
        return -1;
    }

    for (i = 0U; i < count; i++) {
        if (parse_number(strings[i], &dummy) != 0) {
            return -1;
        }
    }

    qsort(strings, count, sizeof(char *), compare_numeric);
    return 0;
}

static size_t bounded_length(const char *str, size_t max_len)
{
    const char *terminator;

    if (str == NULL) {
        return max_len;
    }

    terminator = (const char *)memchr(str, '\0', max_len);
    if (terminator == NULL) {
        return max_len;
    }

    return (size_t)(terminator - str);
}

static char *duplicate_string(const char *str, size_t max_len)
{
    size_t len;
    char *copy;

    if (str == NULL || max_len == 0U || max_len > (SIZE_MAX - 1U)) {
        return NULL;
    }

    len = bounded_length(str, max_len);
    if (len >= max_len) {
        return NULL;
    }

    copy = (char *)malloc(len + 1U);
    if (copy == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    (void)memcpy(copy, str, len);
    copy[len] = '\0';

    return copy;
}

int main(void)
{
    const char *source[] = { "42", "-7", "1000", "3", "0", "-250", "17" };
    size_t count = sizeof(source) / sizeof(source[0]);
    char **list;
    size_t i;
    int status = EXIT_SUCCESS;

    list = (char **)calloc(count, sizeof(char *));
    if (list == NULL) {
        (void)fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; i++) {
        list[i] = duplicate_string(source[i], MAX_NUM_STR_LEN);
        if (list[i] == NULL) {
            size_t j;
            for (j = 0U; j < i; j++) {
                free(list[j]);
            }
            free(list);
            (void)fprintf(stderr, "String duplication failed\n");
            return EXIT_FAILURE;
        }
    }

    if (sort_number_strings(list, count) != 0) {
        (void)fprintf(stderr, "Sorting failed: invalid numeric string\n");
        status = EXIT_FAILURE;
    } else {
        for (i = 0U; i < count; i++) {
            if (printf("%s\n", list[i]) < 0) {
                status = EXIT_FAILURE;
                break;
            }
        }
    }

    for (i = 0U; i < count; i++) {
        free(list[i]);
    }
    free(list);

    return status;
}