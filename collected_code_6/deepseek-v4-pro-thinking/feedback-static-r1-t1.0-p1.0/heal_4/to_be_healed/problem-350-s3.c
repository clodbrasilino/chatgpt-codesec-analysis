#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static size_t safe_strnlen(const char *s, size_t maxlen) {
    size_t len = 0;
    while (len < maxlen && s[len] != '\0') {
        ++len;
    }
    return len;
}

size_t minimizeLength(char *str, size_t size) {
    if (str == NULL || size == 0) {
        return (size_t)-1;
    }

    size_t len = safe_strnlen(str, size);
    if (len == size) {
        return (size_t)-1;
    }

    if (len == 0) {
        return 0;
    }

    size_t frequency[256] = {0};
    unsigned char maxChar = 0;
    size_t maxFrequency = 0;

    for (size_t i = 0; i < len; ++i) {
        unsigned char ch = (unsigned char)str[i];
        ++frequency[ch];
        if (frequency[ch] > maxFrequency) {
            maxFrequency = frequency[ch];
            maxChar = ch;
        }
    }

    size_t writeIndex = 0;
    for (size_t i = 0; i < len; ++i) {
        if ((unsigned char)str[i] != maxChar) {
            str[writeIndex++] = str[i];
        }
    }
    str[writeIndex] = '\0';

    return writeIndex;
}

char* read_line(size_t *capacity_out) {
    size_t capacity = 128;
    char *buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    size_t len = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != EOF && ch != '\n') {
        if (len + 1 >= capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }
            capacity *= 2;
            char *newbuf = realloc(buffer, capacity);
            if (newbuf == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = newbuf;
        }
        buffer[len++] = (char)ch;
    }

    if (ch == EOF && len == 0) {
        free(buffer);
        return NULL;
    }

    buffer[len] = '\0';
    *capacity_out = capacity;
    return buffer;
}

int main(void) {
    size_t capacity;
    char *input = read_line(&capacity);
    if (input == NULL) {
        return 1;
    }

    size_t result = minimizeLength(input, capacity);
    free(input);

    if (result == (size_t)-1) {
        return 1;
    }

    printf("%zu\n", result);
    return 0;
}