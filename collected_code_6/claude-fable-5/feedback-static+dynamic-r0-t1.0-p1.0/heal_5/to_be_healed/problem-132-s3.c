#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TUPLE_STR_LEN 32

struct Tuple {
    int first;
    double second;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char third[TUPLE_STR_LEN];
};

static int tuple_set_third(struct Tuple *t, const char *value)
{
    size_t len;

    if (t == NULL || value == NULL) {
        return -1;
    }

    len = strnlen(value, sizeof(t->third));
    if (len >= sizeof(t->third)) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(t->third, value, len);
    t->third[len] = '\0';

    return 0;
}

static char *tuple_to_string(const struct Tuple *t)
{
    char *result;
    int needed;

    if (t == NULL) {
        return NULL;
    }

    needed = snprintf(NULL, 0, "(%d, %.2f, %s)", t->first, t->second, t->third);
    if (needed < 0) {
        return NULL;
    }

    result = malloc((size_t)needed + 1U);
    if (result == NULL) {
        return NULL;
    }

    if (snprintf(result, (size_t)needed + 1U, "(%d, %.2f, %s)", t->first, t->second, t->third) < 0) {
        free(result);
        return NULL;
    }

    return result;
}

int main(void)
{
    struct Tuple t;
    char *str;

    t.first = 42;
    t.second = 3.14;

    if (tuple_set_third(&t, "hello") != 0) {
        (void)fprintf(stderr, "Failed to set tuple string field\n");
        return EXIT_FAILURE;
    }

    str = tuple_to_string(&t);
    if (str == NULL) {
        (void)fprintf(stderr, "Failed to convert tuple to string\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", str) < 0) {
        free(str);
        return EXIT_FAILURE;
    }

    free(str);
    return EXIT_SUCCESS;
}