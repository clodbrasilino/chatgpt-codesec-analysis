#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

long long count_substrings(const char *str)
{
    size_t len;
    long long result;
    long long *freq;
    long long prefix;
    size_t i;
    size_t range;
    size_t offset;

    if (str == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
    if (len == 0) {
        return 0;
    }

    for (i = 0; i < len; i++) {
        if (!isdigit((unsigned char)str[i])) {
            return -1;
        }
    }

    range = 10 * len + 1;
    offset = len;

    freq = calloc(range, sizeof(long long));
    if (freq == NULL) {
        return -1;
    }

    prefix = 0;
    result = 0;
    freq[offset] = 1;

    for (i = 0; i < len; i++) {
        prefix += (long long)(str[i] - '0') - 1;
        result += freq[(size_t)(prefix + (long long)offset)];
        freq[(size_t)(prefix + (long long)offset)] += 1;
    }

    free(freq);
    return result;
}

int main(void)
{
    const char *tests[] = { "112112", "111", "1101112", "0102" };
    size_t i;
    size_t n;
    /* Possible weaknesses found:
     *  The scope of the variable 'count' can be reduced. [variableScope]
     */
    long long count;

    n = sizeof(tests) / sizeof(tests[0]);

    for (i = 0; i < n; i++) {
        count = count_substrings(tests[i]);
        if (count < 0) {
            fprintf(stderr, "Error processing string: %s\n", tests[i]);
            return EXIT_FAILURE;
        }
        printf("String: %s -> Count: %lld\n", tests[i], count);
    }

    return EXIT_SUCCESS;
}