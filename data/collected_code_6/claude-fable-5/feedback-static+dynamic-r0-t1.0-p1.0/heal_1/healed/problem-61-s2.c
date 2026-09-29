#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LEN 4096

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

    len = strnlen(str, MAX_INPUT_LEN);
    if (len == MAX_INPUT_LEN && str[MAX_INPUT_LEN - 1] != '\0') {
        return -1;
    }
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
        long long idx;

        prefix += (long long)(str[i] - '0') - 1;
        idx = prefix + (long long)offset;
        if (idx < 0 || (size_t)idx >= range) {
            free(freq);
            return -1;
        }
        result += freq[(size_t)idx];
        freq[(size_t)idx] += 1;
    }

    free(freq);
    return result;
}

int main(void)
{
    const char *tests[] = { "112112", "111", "1101112", "0102" };
    size_t i;
    size_t n;

    n = sizeof(tests) / sizeof(tests[0]);

    for (i = 0; i < n; i++) {
        long long count = count_substrings(tests[i]);
        if (count < 0) {
            fprintf(stderr, "Error processing string: %s\n", tests[i]);
            return EXIT_FAILURE;
        }
        printf("String: %s -> Count: %lld\n", tests[i], count);
    }

    return EXIT_SUCCESS;
}