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
    memcpy(*buf + *len, src, n);
    *len += n;
    (*buf)[*len] = '\0';
    return 0;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['MSM', '240', 'is', '104', '129', 'best', '10'], got <no output>
  *  test case 1 failed: expected ['Dart', '368', 'is', '100', '181', 'Super', '18'], got <no output>
  *  test case 2 failed: expected ['Flutter', '484', 'is', '77', '129', 'Magnificent', '45'], got <no output>
  */

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
{
    char *line = NULL;
    size_t len = 0;
    size_t cap = 0;
    char chunk[256];

    while (fgets(chunk, sizeof chunk, fp) != NULL) {
        size_t n = strlen(chunk);
        if (buf_append(&line, &len, &cap, chunk, n) != 0) {
            free(line);
            return NULL;
        }
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
            len--;
            if (len > 0 && line[len - 1] == '\r') {
                line[len - 1] = '\0';
            }
            return line;
        }
    }
    if (line == NULL) {
        return NULL;
    }
    return line;
}

int main(void)
{
    char *line = read_line(stdin);
    if (line == NULL) {
        fprintf(stderr, "Failed to read input string\n");
        return EXIT_FAILURE;
    }

    long k = 0;
    char *kline = read_line(stdin);
    if (kline != NULL) {
        errno = 0;
        char *end = NULL;
        long parsed = strtol(kline, &end, 10);
        if (errno != ERANGE && end != kline) {
            k = parsed;
        } else {
            fprintf(stderr, "Failed to parse k\n");
            free(kline);
            free(line);
            return EXIT_FAILURE;
        }
        free(kline);
    }

    char *result = increment_numerics(line, k);
    if (result == NULL) {
        fprintf(stderr, "Failed to process: %s\n", line);
        free(line);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        free(line);
        return EXIT_FAILURE;
    }

    free(result);
    free(line);
    return EXIT_SUCCESS;
}