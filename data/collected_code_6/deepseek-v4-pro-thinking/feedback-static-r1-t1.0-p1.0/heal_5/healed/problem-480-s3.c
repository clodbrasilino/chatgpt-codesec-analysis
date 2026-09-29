#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

int main(void) {
    size_t capacity = 128;
    size_t length = 0;
    char *input = malloc(capacity);
    if (input == NULL) {
        return 1;
    }

    int c;
    while ((c = getchar()) != EOF && c != '\n') {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity * 2;
            if (new_capacity < capacity) {
                new_capacity = SIZE_MAX;
            }
            char *new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return 1;
            }
            input = new_input;
            capacity = new_capacity;
        }
        input[length++] = (char)c;
    }
    input[length] = '\0';

    char result = max_occurring_char(input);

    if (result != '\0') {
        printf("%c\n", result);
    } else {
        printf("No character found\n");
    }

    free(input);
    return 0;
}