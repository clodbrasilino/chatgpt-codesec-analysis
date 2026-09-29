#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

static int append_chunk(char **buf, size_t *len, size_t *cap, const char *src, size_t n)
{
    if (buf == NULL || *buf == NULL || src == NULL) {
        return -1;
    }
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
    memcpy(*buf + *len, src, n);
    *len += n;
    (*buf)[*len] = '\0';
    return 0;
}

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
    char *buf;
    int ch;

    if (fp == NULL) {
        return NULL;
    }

    buf = malloc(cap);
    if (buf == NULL) {
        return NULL;
    }

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

int main(int argc, char *argv[])
{
    long k = 1;
    char *line;
    char *result;

    if (argc > 1) {
        char *end = NULL;
        errno = 0;
        k = strtol(argv[1], &end, 10);
        if (errno == ERANGE || end == argv[1] || *end != '\0') {
            fprintf(stderr, "Invalid increment value: %s\n", argv[1]);
            return EXIT_FAILURE;
        }
    }

    while ((line = read_line(stdin)) != NULL) {
        result = increment_numbers(line, k);
        if (result == NULL) {
            fprintf(stderr, "Failed to process line\n");
            free(line);
            return EXIT_FAILURE;
        }
        printf("%s\n", result);
        free(result);
        free(line);
    }

    return EXIT_SUCCESS;
}