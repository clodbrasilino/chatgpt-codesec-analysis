#include <stdio.h>
#include <limits.h>
#include <stddef.h>

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
    char buffer[1024];
    char *p;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }

    p = buffer;
    while (*p != '\0') {
        if (*p == '\n') {
            *p = '\0';
            break;
        }
        ++p;
    }

    minimize_length(buffer);
    printf("%s\n", buffer);

    return 0;
}