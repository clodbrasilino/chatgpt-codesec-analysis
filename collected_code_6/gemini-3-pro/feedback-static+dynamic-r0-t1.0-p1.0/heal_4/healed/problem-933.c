#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_INPUT 1024

char* camel_to_snake(const char* input) {
    if (!input) return NULL;

    size_t len = 0;
    while (len < MAX_INPUT && input[len] != '\0') {
        len++;
    }

    char* output = malloc(len * 2 + 1);
    if (!output) return NULL;

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)input[i])) {
            if (i > 0) {
                output[j++] = '_';
            }
            output[j++] = tolower((unsigned char)input[i]);
        } else {
            output[j++] = input[i];
        }
    }
    output[j] = '\0';

    return output;
}

int main(void) {
    char* input = malloc(MAX_INPUT);
    if (!input) {
        return 1;
    }

    if (fgets(input, MAX_INPUT, stdin) != NULL) {
        size_t len = 0;
        while (len < MAX_INPUT && input[len] != '\0') {
            if (input[len] == '\n' || input[len] == '\r') {
                input[len] = '\0';
                break;
            }
            len++;
        }

        char* snake = camel_to_snake(input);
        if (snake) {
            printf("%s\n", snake);
            free(snake);
        }
    }
    
    free(input);
    return 0;
}