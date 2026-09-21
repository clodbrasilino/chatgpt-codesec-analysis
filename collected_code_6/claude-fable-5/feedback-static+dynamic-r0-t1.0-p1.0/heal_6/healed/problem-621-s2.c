#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

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
    if (fp == NULL) {
        return NULL;
    }
    char *line = NULL;
    size_t len = 0;
    size_t cap = 0;
    int c;

    while ((c = fgetc(fp)) != EOF && c != '\n') {
        char ch = (char)c;
        if (buf_append(&line, &len, &cap, &ch, 1) != 0) {
            free(line);
            return NULL;
        }
    }
    if (c == EOF && len == 0) {
        free(line);
        return NULL;
    }
    if (line != NULL && len > 0 && line[len - 1] == '\r') {
        line[len - 1] = '\0';
        len--;
    }
    if (line == NULL) {
        line = malloc(1);
        if (line == NULL) {
            return NULL;
        }
        line[0] = '\0';
    }
    return line;
}

static int parse_k_from_line(const char *kline, long *k)
{
    if (kline == NULL || k == NULL) {
        return -1;
    }
    const char *p = kline;
    while (*p != '\0' && isspace((unsigned char)*p)) {
        p++;
    }
    if (*p == '\0') {
        return -1;
    }
    errno = 0;
    char *end = NULL;
    long value = strtol(p, &end, 10);
    if (errno == ERANGE || end == p) {
        return -1;
    }
    while (*end != '\0' && isspace((unsigned char)*end)) {
        end++;
    }
    if (*end != '\0') {
        return -1;
    }
    *k = value;
    return 0;
}

static int parse_k_from_input(char *input, long *k)
{
    if (input == NULL || k == NULL) {
        return -1;
    }
    size_t pos = strlen(input);
    while (pos > 0 && isspace((unsigned char)input[pos - 1])) {
        pos--;
    }
    size_t numend = pos;
    while (pos > 0 && isdigit((unsigned char)input[pos - 1])) {
        pos--;
    }
    if (pos == numend) {
        return -1;
    }
    if (pos > 0 && (input[pos - 1] == '-' || input[pos - 1] == '+')) {
        pos--;
    }
    errno = 0;
    char *end = NULL;
    long value = strtol(input + pos, &end, 10);
    if (errno == ERANGE || end == input + pos) {
        return -1;
    }
    while