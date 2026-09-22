#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <limits.h>
#include <string.h>

char *minimize_length(char *str) {
    size_t freq[UCHAR_MAX + 1] = {0};
    const unsigned char *p;
    unsigned char max_char = 0;
    size_t max_freq = 0;
    size_t i;
    char *src;
    char *dst;

    if (str == NULL) {
        return NULL;
    }

    p = (const unsigned char *)str;
    while (*p != '\0') {
        freq[*p]++;
        ++p;
    }

    for (i = 0; i <= UCHAR_MAX; ++i) {
        if (freq[i] > max_freq) {
            max_freq = freq[i];
            max_char = (unsigned char)i;
        }
    }

    src = str;
    dst = str;

    while (*src != '\0') {
        if ((unsigned char)*src != max_char) {
            *dst = *src;
            ++dst;
        }
        ++src;
    }
    *dst = '\0';

    return str;
}

int main(void) {
    char *line = NULL;
    size_t n = 0;
    ssize_t len;

    len = getline(&line, &n, stdin);
    if (len == -1) {
        free(line);
        return 1;
    }

    line[strcspn(line, "\n")] = '\0';

    minimize_length(line);
    printf("%s\n", line);

    free(line);
    return 0;
}