#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

static int append_chunk(char **buf, size_t *len, size_t *cap, const char *src, size_t n)
{
    if (*len > SIZE_MAX - n - 1) {
        return -1;
    }
    if (*len + n + 1 > *cap) {
        size_t newcap = *cap;
        while (newcap < *len + n + 1) {
            if (newcap > SIZE_MAX / 2) {
                return -1;
            }
            newcap *= 2;
        }
        char *tmp = realloc(*buf, newcap);
        if (tmp == NULL) {
            return -1;
        }
        *buf = tmp;
        *cap = newcap;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(*buf + *len, src, n);
    *len += n;
    (*buf)[*len] = '\0';
    return 0;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['MSM', '240', 'is', '104', '129', 'best', '10'], got <no output>
  *  test case 2 failed: expected ['Flutter', '484', 'is', '77', '129', 'Magnificent', '45'], got <no output>
  *  test case 1 failed: expected ['Dart', '368', 'is', '100', '181', 'Super', '18'], got <no output>
  */

char *increment_numbers(const char *input, long k)
{
    size_t cap = 64;
    size_t len = 0;
    size_t i = 0;
    char *out;

    if (input == NULL) {
        return NULL;
    }

    out = malloc(cap);
    if (out == NULL) {
        return NULL;
    }
    out[0] = '\0';

    while (input[i] != '\0') {
        if (isdigit((unsigned char)input[i])) {
            char *end = NULL;
            long val;
            long newval;
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char numbuf[32];
            int written;

            errno = 0;
            val = strtol(&input[i], &end, 10);
            if (errno == ERANGE || end == &input[i]) {
                free(out);
                return NULL;
            }
            if ((k > 0 && val > LONG_MAX - k) || (k < 0 && val < LONG_MIN - k)) {
                free(out);
                return NULL;
            }
            newval = val + k;

            written = snprintf(numbuf, sizeof numbuf, "%ld", newval);
            if (written < 0 || (size_t)written >= sizeof numbuf) {
                free(out);
                return NULL;
            }
            if (append_chunk(&out, &len, &cap, numbuf, (size_t)written) != 0) {
                free(out);
                return NULL;
            }
            i = (size_t)(end - input);
        } else {
            if (append_chunk(&out, &len, &cap, &input[i], 1) != 0) {
                free(out);
                return NULL;
            }
            i++;
        }
    }
    return out;
}

static char *read_line(FILE *fp)
{
    size_t cap = 128;
    size_t len = 0;
    char *buf = malloc(cap);
    int ch;

    if (buf == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(fp)) != EOF && ch != '\n') {
        if (len + 2 > cap) {
            size_t newcap;
            char *tmp;
            if (cap > SIZE_MAX / 2) {
                free(buf);
                return NULL;
            }
            newcap = cap * 2;
            tmp = realloc(buf, newcap);
            if (tmp == NULL) {
                free(buf);
                return NULL;
            }
            buf = tmp;
            cap = newcap;
        }
        buf[len++] = (char)ch;
    }

    if (len == 0 && ch == EOF) {
        free(buf);
        return NULL;
    }

    buf[len] = '\0';
    return buf;
}

int main(void)
{
    char *line;
    char *kline;
    char *end = NULL;
    long k;
    char *result;

    line = read_line(stdin);
    if (line == NULL) {
        fprintf(stderr, "Failed to read input string\n");
        return EXIT_FAILURE;
    }

    kline = read_line(stdin);
    if (kline == NULL) {
        free(line);
        fprintf(stderr, "Failed to read increment value\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    k = strtol(kline, &end, 10);
    if (errno == ERANGE || end == kline) {
        free(line);
        free(kline);
        fprintf(stderr, "Invalid increment value\n");
        return EXIT_FAILURE;
    }
    free(kline);

    result = increment_numbers(line, k);
    if (result == NULL) {
        free(line);
        fprintf(stderr, "Failed to process string\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(line);
        free(result);
        return EXIT_FAILURE;
    }

    free(line);
    free(result);
    return EXIT_SUCCESS;
}