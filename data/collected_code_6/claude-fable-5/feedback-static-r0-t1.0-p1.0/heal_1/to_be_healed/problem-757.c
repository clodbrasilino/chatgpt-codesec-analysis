#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int is_reverse_pair(const char *a, const char *b)
{
    size_t len_a;
    size_t len_b;
    size_t i;

    if (a == NULL || b == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len_a = strlen(a);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len_b = strlen(b);

    if (len_a != len_b) {
        return 0;
    }

    for (i = 0; i < len_a; i++) {
        if (a[i] != b[len_a - 1U - i]) {
            return 0;
        }
    }

    return 1;
}

static long count_reverse_pairs(const char *const *list, size_t count)
{
    long pairs = 0;
    size_t i;
    size_t j;

    if (list == NULL || count < 2U) {
        return 0;
    }

    for (i = 0; i < count - 1U; i++) {
        for (j = i + 1U; j < count; j++) {
            if (is_reverse_pair(list[i], list[j]) != 0) {
                pairs++;
            }
        }
    }

    return pairs;
}

int main(void)
{
    const char *strings[] = {
        "abc",
        "cba",
        "hello",
        "olleh",
        "world",
        "abc",
        "cba"
    };
    size_t count = sizeof(strings) / sizeof(strings[0]);
    long result;

    result = count_reverse_pairs(strings, count);

    if (printf("Number of reverse string pairs: %ld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}