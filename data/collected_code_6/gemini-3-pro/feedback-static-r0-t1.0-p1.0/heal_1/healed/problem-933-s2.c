#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char* camel_to_snake(const char* input) {
    if (!input) {
        return NULL;
    }

    size_t len = 0;
    while (input[len] != '\0') {
        len++;
    }

    char* output = malloc(len * 2 + 1);
    if (!output) {
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;

    while (input[i] != '\0') {
        if (i > 0 && islower((unsigned char)input[i - 1]) && isupper((unsigned char)input[i])) {
            output[j++] = '_';
        }
        output[j++] = tolower((unsigned char)input[i]);
        i++;
    }
    output[j] = '\0';

    return output;
}

int main(void) {
    const char* camel = "thisIsACamelCaseString";
    char* snake = camel_to_snake(camel);
    
    if (snake) {
        printf("Camel: %s\n", camel);
        printf("Snake: %s\n", snake);
        free(snake);
    } else {
        fprintf(stderr, "Failed to convert string.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}