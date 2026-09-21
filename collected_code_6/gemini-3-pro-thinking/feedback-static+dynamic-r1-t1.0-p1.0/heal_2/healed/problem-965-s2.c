#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *camel_to_snake(const char *camel_case) {
    if (camel_case == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (camel_case[len] != '\0') {
        len++;
    }

    char *snake_case = malloc((len * 2) + 1);
    
    if (snake_case == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)camel_case[i])) {
            if (i > 0) {
                snake_case[j++] = '_';
            }
            snake_case[j++] = tolower((unsigned char)camel_case[i]);
        } else {
            snake_case[j++] = camel_case[i];
        }
    }
    snake_case[j] = '\0';

    return snake_case;
}

int main(void) {
    int ch;
    size_t capacity = 256;
    size_t length = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    while ((ch = fgetc(stdin)) != EOF) {
        if (isspace(ch)) {
            if (length > 0) {
                buffer[length] = '\0';
                char *result = camel_to_snake(buffer);
                if (result != NULL) {
                    printf("%s\n", result);
                    free(result);
                } else {
                    fprintf(stderr, "Memory allocation failed.\n");
                    free(buffer);
                    return EXIT_FAILURE;
                }
                length = 0;
            }
        } else {
            buffer[length++] = (char)ch;
            if (length >= capacity - 1) {
                size_t new_capacity = capacity * 2;
                char *new_buffer = realloc(buffer, new_capacity);
                if (new_buffer == NULL) {
                    fprintf(stderr, "Memory allocation failed.\n");
                    free(buffer);
                    return EXIT_FAILURE;
                }
                buffer = new_buffer;
                capacity = new_capacity;
            }
        }
    }

    if (length > 0) {
        buffer[length] = '\0';
        char *result = camel_to_snake(buffer);
        if (result != NULL) {
            printf("%s\n", result);
            free(result);
        } else {
            fprintf(stderr, "Memory allocation failed.\n");
            free(buffer);
            return EXIT_FAILURE;
        }
    }

    free(buffer);
    return EXIT_SUCCESS;
}