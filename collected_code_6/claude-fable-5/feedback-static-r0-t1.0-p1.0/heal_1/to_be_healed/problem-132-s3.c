#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tuple {
    int first;
    double second;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char third[32];
};

char *tuple_to_string(const struct Tuple *t)
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
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
     */
    (void)strncpy(t.third, "hello", sizeof(t.third) - 1U);
    t.third[sizeof(t.third) - 1U] = '\0';

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