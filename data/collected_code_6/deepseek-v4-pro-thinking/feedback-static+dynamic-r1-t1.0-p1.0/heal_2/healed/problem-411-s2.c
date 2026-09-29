#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

char *snake_to_camel(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t capacity = 16;
    char *output = malloc(capacity);
    if (output == NULL) {
        return NULL;
    }

    size_t dst = 0;
    int capitalize = 1;

    for (size_t i = 0; ; i++) {
        unsigned char c = (unsigned char)input[i];
        if (c == '\0') {
            break;
        }
        if (c == '_') {
            capitalize = 1;
        } else {
            if (dst + 2 > capacity) {
                capacity *= 2;
                char *new_output = realloc(output, capacity);
                if (new_output == NULL) {
                    free(output);
                    return NULL;
                }
                output = new_output;
            }
            if (capitalize) {
                output[dst++] = (char)toupper(c);
                capitalize = 0;
            } else {
                output[dst++] = (char)c;
            }
        }
    }
    output[dst] = '\0';

    return output;
}

int main(void) {
    const char *snake = "hello_world_from_regex";
    char *camel = snake_to_camel(snake);

    if (camel == NULL) {
        return 1;
    }

    printf("%s\n", camel);
    free(camel);

    return 0;
}