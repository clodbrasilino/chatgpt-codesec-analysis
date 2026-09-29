#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 4096u

typedef struct {
    char *first;
    char *second;
} StringTuple;

static char *concat_strings(const char *a, const char *b)
{
    size_t len_a;
    size_t len_b;
    char *result;

    if (a == NULL || b == NULL) {
        return NULL;
    }

    len_a = strnlen(a, MAX_STRING_LENGTH);
    len_b = strnlen(b, MAX_STRING_LENGTH);

    if (len_a >= MAX_STRING_LENGTH || len_b >= MAX_STRING_LENGTH) {
        return NULL;
    }

    if (len_a > SIZE_MAX - len_b - 1u) {
        return NULL;
    }

    result = malloc(len_a + len_b + 1u);
    if (result == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, a, len_a);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result + len_a, b, len_b);
    result[len_a + len_b] = '\0';

    return result;
}

static int concat_tuples(const StringTuple *t1, const StringTuple *t2, StringTuple *out)
{
    if (t1 == NULL || t2 == NULL || out == NULL) {
        return -1;
    }

    out->first = concat_strings(t1->first, t2->first);
    if (out->first == NULL) {
        return -1;
    }

    out->second = concat_strings(t1->second, t2->second);
    if (out->second == NULL) {
        free(out->first);
        out->first = NULL;
        return -1;
    }

    return 0;
}

static void free_tuple(StringTuple *t)
{
    if (t != NULL) {
        free(t->first);
        free(t->second);
        t->first = NULL;
        t->second = NULL;
    }
}

int main(void)
{
    StringTuple a;
    StringTuple b;
    StringTuple result;

    a.first = "Hello, ";
    a.second = "Good ";
    b.first = "World";
    b.second = "Morning";

    result.first = NULL;
    result.second = NULL;

    if (concat_tuples(&a, &b, &result) != 0) {
        fprintf(stderr, "Error: tuple concatenation failed\n");
        return EXIT_FAILURE;
    }

    if (printf("(%s, %s)\n", result.first, result.second) < 0) {
        free_tuple(&result);
        return EXIT_FAILURE;
    }

    free_tuple(&result);

    return EXIT_SUCCESS;
}