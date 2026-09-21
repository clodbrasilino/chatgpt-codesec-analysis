#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

char max_occurring_char(const char *str) {
    if (str == NULL || *str == '\0') {
        return '\0';
    }

    unsigned long count[UCHAR_MAX + 1] = {0};
    const unsigned char *s = (const unsigned char *)str;
    size_t max_count = 0;
    char max_char = '\0';

    while (*s != '\0') {
        unsigned char uc = *s;
        count[uc]++;

        if (count[uc] > max_count) {
            max_count = count[uc];
            max_char = (char)uc;
        }

        s++;
    }

    return max_char;
}

static size_t safe_strnlen(const char *s, size_t maxlen) {
    size_t i;
    for (i = 0; i < maxlen; i++) {
        if (s[i] == '\0') {
            return i;
        }
    }
    return maxlen;
}

int main(void) {
    size_t capacity = 128;
    size_t length = 0;
    char *input = malloc(capacity);
    if (input == NULL) {
        return 1;
    }

    while (1) {
        const char *ret = fgets(input + length, capacity - length, stdin);
        if (ret == NULL) {
            if (ferror(stdin)) {
                free(input);
                return 1;
            }
            break;
        }

        size_t added = safe_strnlen(input + length, capacity - length - 1);
        size_t new_len = length + added;
        if (new_len > 0 && input[new_len - 1] == '\n') {
            input[new_len - 1] = '\0';
            break;
        }

        length = new_len;
        if (capacity - length <= 1) {
            size_t new_capacity = capacity * 2;
            if (new_capacity < capacity) {
                free(input);
                return 1;
            }
            char *new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return 1;
            }
            input = new_input;
            capacity = new_capacity;
        }
    }

    char result = max_occurring_char(input);

    if (result != '\0') {
        printf("%c\n", result);
    } else {
        printf("No character found\n");
    }

    free(input);
    return 0;
}