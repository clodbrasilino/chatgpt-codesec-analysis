#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *concat_tuple(const char *tuple[], size_t count, const char *delimiter) {
    if (delimiter == NULL) {
        return NULL;
    }
    if (count == 0) {
        char *empty = malloc(1);
        if (empty == NULL) return NULL;
        empty[0] = '\0';
        return empty;
    }
    if (tuple == NULL) {
        return NULL;
    }

    size_t delim_len = 0;
    const char *d = delimiter;
    while (d[delim_len] != '\0') delim_len++;

    size_t total_len = 0;

    for (size_t i = 0; i < count; i++) {
        if (tuple[i] == NULL) {
            return NULL;
        }
        size_t remaining = SIZE_MAX - total_len;
        if (remaining == 0) {
            return NULL;
        }
        const char *s = tuple[i];
        size_t len = 0;
        while (len < remaining && s[len] != '\0') len++;
        if (len == remaining && s[remaining] != '\0') {
            return NULL;
        }
        total_len += len;
    }

    if (count > 1 && delim_len > 0) {
        if (delim_len > SIZE_MAX / (count - 1)) {
            return NULL;
        }
        size_t delim_total = delim_len * (count - 1);
        if (total_len > SIZE_MAX - delim_total) {
            return NULL;
        }
        total_len += delim_total;
    }

    if (total_len == SIZE_MAX) {
        return NULL;
    }

    char *result = malloc(total_len + 1);
    if (result == NULL) {
        return NULL;
    }

    char *p = result;
    const char *end = result + total_len;

    for (size_t i = 0; i < count; i++) {
        if (i > 0) {
            if (p + delim_len > end) {
                free(result);
                return NULL;
            }
            for (size_t k = 0; k < delim_len; k++) {
                p[k] = delimiter[k];
            }
            p += delim_len;
        }

        size_t len = 0;
        const char *s = tuple[i];
        while (s[len] != '\0') len++;

        if (p + len > end) {
            free(result);
            return NULL;
        }
        for (size_t k = 0; k < len; k++) {
            p[k] = s[k];
        }
        p += len;
    }
    *p = '\0';

    return result;
}

int main(void) {
    const char *tuple[] = {"apple", "banana", "cherry"};
    char *result = concat_tuple(tuple, sizeof(tuple) / sizeof(tuple[0]), ", ");
    if (result == NULL) {
        return 1;
    }
    printf("%s\n", result);
    free(result);
    return 0;
}