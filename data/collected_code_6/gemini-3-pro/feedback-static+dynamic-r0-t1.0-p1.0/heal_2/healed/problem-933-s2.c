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
    char buffer[2048];
    if (scanf("%2047s", buffer) == 1) {
        char* snake = camel_to_snake(buffer);
        if (snake) {
            printf("%s\n", snake);
            free(snake);
        }
    }
    return 0;
}