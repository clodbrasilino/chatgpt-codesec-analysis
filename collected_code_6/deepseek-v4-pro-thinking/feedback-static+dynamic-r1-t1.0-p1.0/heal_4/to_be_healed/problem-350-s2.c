#include <stdio.h>
#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>

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
    size_t cap = 1024;
    size_t len = 0;
    int ch;
    char *buffer = malloc(cap);
    char *new_buf;

    if (buffer == NULL) {
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (cap - len < 2) {
            if (cap > SIZE_MAX / 2) {
                free(buffer);
                return 1;
            }
            cap *= 2;
            new_buf = realloc(buffer, cap);
            if (new_buf == NULL) {
                free(buffer);
                return 1;
            }
            buffer = new_buf;
        }
        buffer[len++] = (char)ch;
    }
    buffer[len] = '\0';

    minimize_length(buffer);
    printf("%s\n", buffer);

    free(buffer);
    return 0;
}