#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char* camel_to_snake(const char* input) {
    if (!input) return NULL;

    size_t len = 0;
    size_t underscores = 0;
    
    for (size_t i = 0; input[i] != '\0'; i++) {
        len++;
        if (i > 0 && isupper((unsigned char)input[i])) {
            underscores++;
        }
    }

    char* output = malloc(len + underscores + 1);
    if (!output) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (i > 0 && isupper((unsigned char)input[i])) {
            output[j++] = '_';
        }
        output[j++] = tolower((unsigned char)input[i]);
    }
    output[j] = '\0';

    return output;
}

int main(void) {
    size_t capacity = 256;
    size_t length = 0;
    char *buffer = malloc(capacity);
    
    if (!buffer) {
        return 1;
    }

    int ch;
    
    while ((ch = fgetc(stdin)) != EOF && !isspace(ch)) {
        if (length + 1 >= capacity) {
            if (capacity > ((size_t)-1) / 2) {
                free(buffer);
                return 1;
            }
            size_t new_capacity = capacity * 2;
            char *temp = realloc(buffer, new_capacity);
            if (!temp) {
                free(buffer);
                return 1;
            }
            capacity = new_capacity;
            buffer = temp;
        }
        buffer[length++] = (char)ch;
    }
    buffer[length] = '\0';

    if (length > 0) {
        char* snake = camel_to_snake(buffer);
        if (snake) {
            printf("%s\n", snake);
            free(snake);
        }
    }

    free(buffer);
    return 0;
}