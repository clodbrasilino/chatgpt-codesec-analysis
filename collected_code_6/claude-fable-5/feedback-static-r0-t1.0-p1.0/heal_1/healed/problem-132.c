#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int first;
    double second;
    char *third;
} Tuple;

int tuple_set_third(Tuple *t, const char *value)
{
    char *copy;
    size_t len;

    if (t == NULL || value == NULL) {
        return -1;
    }

    len = strlen(value);
    copy = malloc(len + 1U);
    if (copy == NULL) {
        return -1;
    }

    memcpy(copy, value, len + 1U);
    free(t->third);
    t->third = copy;
    return 0;
}

void tuple_destroy(Tuple *t)
{
    if (t != NULL) {
        free(t->third);
        t->third = NULL;
    }
}

char *tuple_to_string(const Tuple *t)
{
    char *result;
    int needed;
    size_t size;

    if (t == NULL || t->third == NULL) {
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

    t.first = 42;
    t.second = 3.14;
    t.third = NULL;

    if (tuple_set_third(&t, "hello") != 0) {
        fprintf(stderr, "Failed to initialize tuple\n");
        return EXIT_FAILURE;
    }

    str = tuple_to_string(&t);
    if (str == NULL) {
        fprintf(stderr, "Failed to convert tuple to string\n");
        tuple_destroy(&t);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", str) < 0) {
        free(str);
        tuple_destroy(&t);
        return EXIT_FAILURE;
    }

    free(str);
    tuple_destroy(&t);
    return EXIT_SUCCESS;
}