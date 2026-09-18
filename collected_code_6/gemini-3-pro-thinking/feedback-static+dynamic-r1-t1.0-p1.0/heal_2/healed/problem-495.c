#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *remove_lowercase(const char *input) {
    size_t input_len;
    char *result;
    size_t j = 0;

    if (input == NULL) {
        return NULL;
    }

    input_len = strlen(input);
    result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < input_len; i++) {
        if (!islower((unsigned char)input[i])) {
            result[j++] = input[i];
        }
    }
    result[j] = '\0';

    return result;
}

int main(void) {
    size_t capacity = 1024;
    size_t len = 0;
    char *buffer = (char *)malloc(capacity);
    int c;

    if (buffer == NULL) {
        return EXIT_FAILURE;
    }

    while ((c = fgetc(stdin)) != EOF && c != '\n') {
        if (c == '\r') {
            continue;
        }
        buffer[len++] = (char)c;
        if (len == capacity) {
            capacity *= 2;
            char *new_buffer = (char *)realloc(buffer, capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return EXIT_FAILURE;
            }
            buffer = new_buffer;
        }
    }
    buffer[len] = '\0';

    if (len > 0 || c != EOF) {
        char *processed_str = remove_lowercase(buffer);
        if (processed_str != NULL) {
            printf("%s\n", processed_str);
            free(processed_str);
        }
    }

    free(buffer);
    return EXIT_SUCCESS;
}