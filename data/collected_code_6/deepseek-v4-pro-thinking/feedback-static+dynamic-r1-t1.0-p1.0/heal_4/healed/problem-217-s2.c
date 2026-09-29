#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

int first_repeated_character(const char *str) {
    size_t char_count[UCHAR_MAX + 1] = {0};
    const unsigned char *ptr;
    size_t i = 0;

    if (str == NULL) {
        return -1;
    }

    ptr = (const unsigned char *)str;

    while (ptr[i] != '\0') {
        char_count[ptr[i]]++;
        i++;
    }

    i = 0;
    while (ptr[i] != '\0') {
        if (char_count[ptr[i]] > 1) {
            return ptr[i];
        }
        i++;
    }

    return -1;
}

char *read_line_dynamic(void) {
    size_t capacity = 256;
    size_t length = 0;
    char *buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    int c;

    while ((c = getchar()) != EOF && c != '\n') {
        if (length >= capacity - 1) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }
            size_t new_capacity = capacity * 2;
            char *new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = new_buffer;
            capacity = new_capacity;
        }
        buffer[length++] = (char)c;
    }

    if (length == 0 && c == EOF) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void) {
    char *input = read_line_dynamic();
    int result;

    if (input == NULL) {
        return 1;
    }

    result = first_repeated_character(input);

    if (result != -1) {
        printf("%c\n", result);
    } else {
        printf("No repeated character\n");
    }

    free(input);
    return 0;
}