#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

/* Possible weaknesses found:
 *  declared here
 */
static int buf_append(char **buf, size_t *len, size_t *cap, const char *src, size_t n)
{
    if (buf == NULL || len == NULL || cap == NULL || src == NULL) {
        return -1;
    }
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
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char numstr[64];
            if (nlen >= sizeof numstr) {
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
                free(out);
                return NULL;
            }

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

static char *read_line(FILE *fp)
/* Possible weaknesses found:
 *  to match this '{'
 */
{
    if (fp == NULL) {
        return NULL;
    }
    char *line = NULL;
    size_t len = 0;
    size_t cap = 0;
    int c;

    /* Possible weaknesses found:
     *  Unmatched '{'. Configuration: ''. [syntaxError]
     *  to match this '{'
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = fgetc(fp)) != EOF && c != '\n') {
        char ch = (char)c;
        /* Possible weaknesses found:
         *  expected ')' at end of input
         *  expected ')'
         *  to match this '('
         *  expected declaration or statement at end of input
         *  too few arguments to function 'buf_append'; expected 5, have 4
         *  expected '}'
         */
        if (buf_append(&line, &len, &cap, &ch