#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

long long minimum_swaps(const char *first, const char *second)
{
    size_t length;
    size_t mismatches_01 = 0;
    size_t mismatches_10 = 0;

    if (first == NULL || second == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(first);

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (length != strlen(second)) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if ((first[i] != '0' && first[i] != '1') ||
            (second[i] != '0' && second[i] != '1')) {
            return -1;
        }

        if (first[i] == '0' && second[i] == '1') {
            ++mismatches_01;
        } else if (first[i] == '1' && second[i] == '0') {
            ++mismatches_10;
        }
    }

    if (mismatches_01 != mismatches_10 || mismatches_01 > LLONG_MAX) {
        return -1;
    }

    return (long long)mismatches_01;
}

int main(void)
{
    char *first = NULL;
    char *second = NULL;
    size_t first_capacity = 0;
    size_t second_capacity = 0;
    ssize_t first_length;
    ssize_t second_length;
    long long result;

    first_length = getline(&first, &first_capacity, stdin);
    if (first_length < 0) {
        free(first);
        free(second);
        return EXIT_FAILURE;
    }

    second_length = getline(&second, &second_capacity, stdin);
    if (second_length < 0) {
        free(first);
        free(second);
        return EXIT_FAILURE;
    }

    if (first_length > 0 && first[first_length - 1] == '\n') {
        first[--first_length] = '\0';
    }

    if (second_length > 0 && second[second_length - 1] == '\n') {
        second[--second_length] = '\0';
    }

    if (first_length > 0 && first[first_length - 1] == '\r') {
        first[--first_length] = '\0';
    }

    if (second_length > 0 && second[second_length - 1] == '\r') {
        second[--second_length] = '\0';
    }

    result = minimum_swaps(first, second);
    printf("%lld\n", result);

    free(first);
    free(second);

    return result < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}