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
    char *buffer = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    while ((ch = getchar()) != EOF && ch != '\n') {
        if (length + 1 >= capacity) {
            size_t new_capacity;
            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(buffer);
                    return 1;
                }
                new_capacity = capacity * 2;
            }
            char *new_ptr = realloc(buffer, new_capacity);
            if (new_ptr == NULL) {
                free(buffer);
                return 1;
            }
            buffer = new_ptr;
            capacity = new_capacity;
        }
        buffer[length++] = (char)ch;
    }

    if (length == 0 && ch == EOF) {
        free(buffer);
        return 1;
    }

    if (length == SIZE_MAX) {
        free(buffer);
        return 1;
    }
    {
        char *new_ptr = realloc(buffer, length + 1);
        if (new_ptr == NULL) {
            free(buffer);
            return 1;
        }
        buffer = new_ptr;
    }
    buffer[length] = '\0';

    minimize_length(buffer);
    printf("%s\n", buffer);
    free(buffer);

    return 0;
}