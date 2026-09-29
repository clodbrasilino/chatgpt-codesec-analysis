#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH (1024u * 1024u)

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

char *read_input(void) {
    size_t size = 128;
    size_t len = 0;
    char *buffer = malloc(size);
    int c;

    if (!buffer) {
        return NULL;
    }

    while ((c = getchar()) != EOF && c != '\n') {
        if (len + 1 >= size) {
            if (size > MAX_INPUT_LENGTH / 2 || size > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }
            size *= 2;
            char *newbuf = realloc(buffer, size);
            if (!newbuf) {
                free(buffer);
                return NULL;
            }
            buffer = newbuf;
        }
        buffer[len++] = (char)c;
    }

    if (len == 0 && c == EOF) {
        free(buffer);
        return NULL;
    }

    buffer[len] = '\0';
    return buffer;
}

int main(void) {
    char *input = read_input();
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