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
    return line;
}

static int parse_long_full(const char *s, long *out)
{
    if (s == NULL || *s == '\0') {
        return -1;
    }
    errno = 0;
    char *end = NULL;
    long parsed = strtol(s, &end, 10);
    if (errno == ERANGE || end == s) {
        return -1;
    }
    while (*end != '\0') {
        if (!isspace((unsigned char)*end)) {
            return -1;
        }
        end++;
    }
    *out = parsed;
    return 0;
}

static int is_delim(char c)
{
    return isspace((unsigned char)c) || c == '[' || c == ']' ||
           c == ',' || c == '\'' || c == '"';
}

static int token_is_number(const char *tok)
{
    size_t i = 0;
    if (tok[0] == '-' || tok[0] == '+') {
        i = 1;
    }
    if (tok[i] == '\0') {
        return 0;
    }
    for (; tok[i] != '\0'; i++) {
        if (!isdigit((unsigned char)tok[i])) {
            return 0;
        }
    }
    return 1;
}

static char *process_token(const char *tok, long k)
{
    if (token_is_number(tok)) {
        errno = 0;
        char *end = NULL;
        long long value = strtoll(tok, &end, 10);
        if (errno == ERANGE || end == tok || *end != '\0') {
            return NULL;
        }
        if ((k > 0 && value > LLONG_MAX - k) ||
            (k < 0 && value < LLONG_MIN - k)) {
            return NULL;
        }
        value += k;
        char numbuf[32];
        int written = snprintf(numbuf, sizeof numbuf, "%lld", value);
        if (written < 0 || (size_t)written >= sizeof numbuf) {
            return NULL;
        }
        char *res = malloc((size_t)written + 1);
        if (res == NULL) {
            return NULL;
        }
        memcpy(res, numbuf, (size_t)written + 1);
        return res;
    }
    size_t n = strlen(tok);
    char *res = malloc(n + 1);
    if (res == NULL) {
        return NULL;
    }
    memcpy(res, tok, n + 1);
    return res;
}

static char *increment_and_format(const char *input, long k)
{
    if (input == NULL) {
        return NULL;
    }
    char *out = NULL;
    size_t len = 0;
    size_t cap = 0;
    size_t i = 0;
    int first = 1;

    if (buf_append(&out, &len, &cap, "[", 1) != 0) {
        free(out);
        return NULL;
    }

    while (input[i] != '\0') {
        while (input[i] != '\0' && is_delim(input[i])) {
            i++;
        }
        if (input[i] == '\0') {
            break;
        }
        size_t start = i;
        while (input[i] != '\0' && !is_delim(input[i])) {
            i++;
        }
        size_t tlen = i - start;
        char *tok = malloc(tlen + 1);
        if (tok == NULL) {
            free(out);
            return NULL;
        }
        memcpy(tok, input + start, tlen);
        tok[tlen] = '\0';

        char *processed = process_token(tok, k);
        free(tok);
        if (processed == NULL) {
            free(out);
            return NULL;
        }

        if (!first) {
            if (buf_append(&out, &len, &cap, ", ", 2) != 0) {
                free(processed);
                free(out);
                return NULL;
            }
        }
        first = 0;

        if (buf_append(&out, &len, &cap, "'", 1) != 0 ||
            buf_append(&out, &len, &cap, processed, strlen(processed)) != 0 ||
            buf_append(&out, &len, &cap, "'", 1) != 0) {
            free(processed);
            free(out);
            return NULL;
        }
        free(processed);
    }

    if (buf_append(&out, &len, &cap, "]", 1) != 0) {
        free(out);
        return NULL;
    }
    return out;
}

int main(int argc, char **argv)
{
    char *line = NULL;
    long k = 0;

    if (argc >= 2) {
        size_t slen = strlen(argv[1]);
        line = malloc(slen + 1);
        if (line == NULL) {
            fprintf(stderr, "Error: memory allocation failed\n");
            return EXIT_FAILURE;
        }
        memcpy(line, argv[1], slen + 1);
    } else {
        line = read_line(stdin);
        if (line == NULL) {
            fprintf(stderr, "Error: failed to read input line\n");
            return EXIT_FAILURE;
        }
    }

    if (argc >= 3) {
        if (parse_long_full(argv[2], &k) != 0) {
            fprintf(stderr, "Error: invalid increment value '%s'\n", argv[2]);
            free(line);
            return EXIT_FAILURE;
        }
    } else {
        char *kline = read_line(stdin);
        if (kline == NULL || parse_long_full(kline, &k) != 0) {
            fprintf(stderr, "Error: failed to read increment value\n");
            free(kline);
            free(line);
            return EXIT_FAILURE;
        }
        free(kline);
    }

    char *result = increment_and_format(line, k);
    free(line);
    if (result == NULL) {
        fprintf(stderr, "Error: failed to process input\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", result);
    free(result);
    return EXIT_SUCCESS;
}