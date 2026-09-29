#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>

char *camel_to_snake(const char *camel_str);

char *camel_to_snake(const char *camel_str) {
    if (camel_str == NULL) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; camel_str[i] != '\0'; i++) {
        if (isupper((unsigned char)camel_str[i]) && i > 0) {
            count += 2;
        } else {
            count += 1;
        }
    }

    char *snake_str = malloc(count + 1);
    if (snake_str == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; camel_str[i] != '\0'; i++) {
        if (isupper((unsigned char)camel_str[i])) {
            if (i > 0) {
                snake_str[j++] = '_';
            }
            snake_str[j++] = (char)tolower((unsigned char)camel_str[i]);
        } else {
            snake_str[j++] = camel_str[i];
        }
    }
    snake_str[j] = '\0';

    return snake_str;
}

int main(int argc, const char *argv[]) {
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            char *snake = camel_to_snake(argv[i]);
            if (snake != NULL) {
                printf("%s\n", snake);
                free(snake);
            }
        }
    } else {
        size_t capacity = 1024;
        size_t length = 0;
        char *buffer = malloc(capacity);
        
        if (buffer == NULL) {
            return EXIT_FAILURE;
        }

        int ch;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = fgetc(stdin)) != EOF) {
            if (isspace(ch)) {
                if (length > 0) {
                    buffer[length] = '\0';
                    char *snake_case = camel_to_snake(buffer);
                    if (snake_case != NULL) {
                        printf("%s\n", snake_case);
                        free(snake_case);
                    }
                    length = 0;
                }
            } else {
                if (length + 1 >= capacity) {
                    if (capacity > SIZE_MAX / 2) {
                        free(buffer);
                        return EXIT_FAILURE;
                    }
                    capacity *= 2;
                    char *new_buffer = realloc(buffer, capacity);
                    if (new_buffer == NULL) {
                        free(buffer);
                        return EXIT_FAILURE;
                    }
                    buffer = new_buffer;
                }
                buffer[length++] = (char)ch;
            }
        }
        if (length > 0) {
            buffer[length] = '\0';
            char *snake_case = camel_to_snake(buffer);
            if (snake_case != NULL) {
                printf("%s\n", snake_case);
                free(snake_case);
            }
        }
        free(buffer);
    }
    return EXIT_SUCCESS;
}