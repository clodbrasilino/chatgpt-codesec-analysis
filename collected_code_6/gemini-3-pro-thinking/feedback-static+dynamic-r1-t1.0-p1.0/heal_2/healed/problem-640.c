#include <stdio.h>
#include <stdlib.h>

char *remove_parentheses(const char *input);

char *remove_parentheses(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (input[len] != '\0') {
        len++;
    }

    char *output = (char *)malloc(len + 1);
    
    if (output == NULL) {
        return NULL;
    }

    size_t j = 0;
    int depth = 0;

    for (size_t i = 0; i < len; i++) {
        if (input[i] == '(') {
            depth++;
        } else if (input[i] == ')') {
            if (depth > 0) {
                depth--;
            }
        } else if (depth == 0) {
            output[j++] = input[i];
        }
    }
    
    output[j] = '\0';

    char *resized_output = (char *)realloc(output, j + 1);
    if (resized_output != NULL) {
        return resized_output;
    }

    return output;
}

int main(void) {
    size_t capacity = 4096;
    char *buffer = (char *)malloc(capacity);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    int c;
    size_t len = 0;

    while ((c = fgetc(stdin)) != EOF) {
        if (c == '\n' || c == '\r') {
            if (c == '\r') {
                int next_c = fgetc(stdin);
                if (next_c != '\n' && next_c != EOF) {
                    ungetc(next_c, stdin);
                }
            }
            
            buffer[len] = '\0';
            char *result = remove_parentheses(buffer);

            if (result != NULL) {
                printf("%s\n", result);
                free(result);
            } else {
                fprintf(stderr, "Memory allocation failed or invalid input.\n");
            }
            
            len = 0;
        } else {
            buffer[len++] = (char)c;
            
            if (len >= capacity - 1) {
                size_t new_capacity = capacity * 2;
                char *new_buffer = (char *)realloc(buffer, new_capacity);
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

    if (len > 0) {
        buffer[len] = '\0';
        char *result = remove_parentheses(buffer);

        if (result != NULL) {
            printf("%s\n", result);
            free(result);
        } else {
            fprintf(stderr, "Memory allocation failed or invalid input.\n");
        }
    }

    free(buffer);
    return EXIT_SUCCESS;
}