#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *safe_concat(const char *a, const char *b)
{
    size_t len_a;
    size_t len_b;
    char *result;

    if (a == NULL || b == NULL) {
        return NULL;
    }

    len_a = strlen(a);
    len_b = strlen(b);

    if (len_b > SIZE_MAX - 1U || len_a > SIZE_MAX - len_b - 1U) {
        return NULL;
    }

    result = malloc(len_a + len_b + 1U);
    if (result == NULL) {
        return NULL;
    }

    memcpy(result, a, len_a);
    memcpy(result + len_a, b, len_b);
    result[len_a + len_b] = '\0';

    return result;
}

int main(void)
{
    const char *first = "Hello, ";
    const char *second = "world!";
    char *combined;

    combined = safe_concat(first, second);
    if (combined == NULL) {
        fprintf(stderr, "Concatenation failed\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", combined);
    free(combined);

    return EXIT_SUCCESS;
}