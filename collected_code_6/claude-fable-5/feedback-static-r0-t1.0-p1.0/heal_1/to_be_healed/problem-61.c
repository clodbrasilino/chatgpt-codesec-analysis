#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

long long count_substrings(const char *str);

long long count_substrings(const char *str)
{
    size_t n;
    size_t i;
    size_t table_size;
    long long *freq;
    long long prefix;
    long long count;

    if (str == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    n = strlen(str);
    if (n == 0) {
        return 0;
    }

    for (i = 0; i < n; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return -1;
        }
    }

    if (n > (SIZE_MAX - 1u) / 9u) {
        return -1;
    }

    table_size = 9u * n + 1u;
    freq = calloc(table_size, sizeof *freq);
    if (freq == NULL) {
        return -1;
    }

    prefix = 0;
    count = 0;
    freq[n] = 1;

    for (i = 0; i < n; i++) {
        prefix += (long long)(str[i] - '0') - 1;
        count += freq[(size_t)(prefix + (long long)n)];
        freq[(size_t)(prefix + (long long)n)] += 1;
    }

    free(freq);
    return count;
}

int main(void)
{
    const char *tests[] = { "112112", "111", "0", "1101112", "9" };
    size_t num_tests = sizeof tests / sizeof tests[0];
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'result' can be reduced. [variableScope]
     */
    long long result;
    int status;

    status = EXIT_SUCCESS;

    for (i = 0; i < num_tests; i++) {
        result = count_substrings(tests[i]);
        if (result < 0) {
            if (fprintf(stderr, "Error processing input: %s\n", tests[i]) < 0) {
                /* Possible weaknesses found:
                 *  Value stored to 'status' is never read [deadcode.DeadStores]
                 *  status is assigned
                 */
                status = EXIT_FAILURE;
            }
            /* Possible weaknesses found:
             *  status is overwritten
             *  Variable 'status' is reassigned a value before the old one has been used. [redundantAssignment]
             */
            status = EXIT_FAILURE;
        } else {
            if (printf("Input: %s -> Count: %lld\n", tests[i], result) < 0) {
                status = EXIT_FAILURE;
            }
        }
    }

    return status;
}