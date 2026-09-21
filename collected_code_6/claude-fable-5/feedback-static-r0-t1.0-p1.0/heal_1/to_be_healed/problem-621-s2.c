#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

static int buf_append(char **buf, size_t *len, size_t *cap, const char *src, size_t n)
{
    if (n > SIZE_MAX - *len - 1) {
        return -1;
    }
    if (*len + n + 1 > *cap) {
        size_t ncap = (*cap == 0) ? 64 : *cap;
        while (*len + n + 1 > ncap) {
            if (ncap > SIZE_MAX / 2) {
                return -1;
            }
            ncap *= 2;
        }
        char *tmp = realloc(*buf, ncap);
        if (tmp == NULL) {
            return -1;
        }
        *buf = tmp;
        *cap = ncap;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(*buf + *len, src, n);
    *len += n;
    (*buf)[*len] = '\0';
    return 0;
}

char *increment_numerics(const char *input, long k)
{
    if (input == NULL) {
        return NULL;
    }
    char *out = NULL;
    size_t len = 0;
    size_t cap = 0;
    size_t i = 0;
    while (input[i] != '\0') {
        if (isdigit((unsigned char)input[i])) {
            size_t start = i;
            while (isdigit((unsigned char)input[i])) {
                i++;
            }
            size_t nlen = i - start;
            char *numstr = malloc(nlen + 1);
            if (numstr == NULL) {
                free(out);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(numstr, input + start, nlen);
            numstr[nlen] = '\0';
            errno = 0;
            char *end = NULL;
            long long value = strtoll(numstr, &end, 10);
            if (errno == ERANGE || end == numstr || *end != '\0') {
                free(numstr);
                free(out);
                return NULL;
            }
            free(numstr);
            if ((k > 0 && value > LLONG_MAX - k) ||
                (k < 0 && value < LLONG_MIN - k)) {
                free(out);
                return NULL;
            }
            value += k;
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char numbuf[32];
            int written = snprintf(numbuf, sizeof numbuf, "%lld", value);
            if (written < 0 || (size_t)written >= sizeof numbuf) {
                free(out);
                return NULL;
            }
            if (buf_append(&out, &len, &cap, numbuf, (size_t)written) != 0) {
                free(out);
                return NULL;
            }
        } else {
            if (buf_append(&out, &len, &cap, &input[i], 1) != 0) {
                free(out);
                return NULL;
            }
            i++;
        }
    }
    if (out == NULL) {
        out = malloc(1);
        if (out == NULL) {
            return NULL;
        }
        out[0] = '\0';
    }
    return out;
}

int main(void)
{
    const char *tests[] = {
        "item 12 costs 45 dollars",
        "abc100def200",
        "no numbers here",
        "0 boundary 999"
    };
    long k = 5;
    size_t count = sizeof tests / sizeof tests[0];
    size_t i;

    for (i = 0; i < count; i++) {
        char *result = increment_numerics(tests[i], k);
        if (result == NULL) {
            if (fprintf(stderr, "Failed to process: %s\n", tests[i]) < 0) {
                return EXIT_FAILURE;
            }
            return EXIT_FAILURE;
        }
        if (printf("Input : %s\nOutput: %s\n\n", tests[i], result) < 0) {
            free(result);
            return EXIT_FAILURE;
        }
        free(result);
    }
    return EXIT_SUCCESS;
}