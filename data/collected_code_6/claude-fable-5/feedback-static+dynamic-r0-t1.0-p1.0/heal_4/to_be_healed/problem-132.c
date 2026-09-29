#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TUPLE_STR_MAX 64

typedef struct {
    int first;
    double second;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char third[TUPLE_STR_MAX];
} Tuple;

int tuple_set_third(Tuple *t, const char *value)
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

char *tuple_to_string(const Tuple *t)
{
    char *result;
    int needed;
    size_t size;

    if (t == NULL) {
        return NULL;
    }

    if (memchr(t->third, '\0', sizeof(t->third)) == NULL) {
        return NULL;
    }

    needed = snprintf(NULL, 0, "(%d, %.2f, %s)", t->first, t->second, t->third);
    if (needed < 0) {
        return NULL;
    }

    size = (size_t)needed + 1U;
    result = malloc(size);
    if (result == NULL) {
        return NULL;
    }

    needed = snprintf(result, size, "(%d, %.2f, %s)", t->first, t->second, t->third);
    if (needed < 0 || (size_t)needed >= size) {
        free(result);
        return NULL;
    }

    return result;
}

int main(void)
{
    Tuple t;
    char *str;

    memset(&t, 0, sizeof(t));

    t.first = 42;
    t.second = 3.14;

    if (tuple_set_third(&t, "hello") != 0) {
        fprintf(stderr, "Failed to initialize tuple\n");
        return EXIT_FAILURE;
    }

    str = tuple_to_string(&t);
    if (str == NULL) {
        fprintf(stderr, "Failed to convert tuple to string\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", str) < 0) {
        free(str);
        return EXIT_FAILURE;
    }

    free(str);
    return EXIT_SUCCESS;
}