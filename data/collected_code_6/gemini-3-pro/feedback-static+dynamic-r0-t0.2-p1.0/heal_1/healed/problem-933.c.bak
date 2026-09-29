#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* camel_to_snake(const char* camel_case) {
    if (!camel_case) return NULL;

    size_t len = strlen(camel_case);
    size_t max_len = len * 2 + 1;
    char* snake_case = (char*)malloc(max_len);
    if (!snake_case) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)camel_case[i])) {
            if (i > 0 && camel_case[i - 1] != '_') {
                snake_case[j++] = '_';
            }
            snake_case[j++] = tolower((unsigned char)camel_case[i]);
        } else {
            snake_case[j++] = tolower((unsigned char)camel_case[i]);
        }
    }
    snake_case[j] = '\0';

    return snake_case;
}

int main(int argc, char **argv) {
    if (argc > 1) {
        char* snake = camel_to_snake(argv[1]);
        if (snake) {
            printf("%s\n", snake);
            free(snake);
        }
    }
    return 0;
}