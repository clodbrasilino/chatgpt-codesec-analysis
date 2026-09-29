#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *camel_to_snake(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strlen(input);
    size_t max_len = (len * 2) + 1;
    char *result = (char *)malloc(max_len);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)input[i])) {
            if (i > 0 && (islower((unsigned char)input[i - 1]) || isdigit((unsigned char)input[i - 1]))) {
                result[j++] = '_';
            }
            result[j++] = tolower((unsigned char)input[i]);
        } else {
            result[j++] = tolower((unsigned char)input[i]);
        }
    }
    result[j] = '\0';

    return result;
}

int main(void) {
    char buffer[4096];

    while (scanf("%4095s", buffer) == 1) {
        char *snake = camel_to_snake(buffer);
        if (snake != NULL) {
            printf("%s\n", snake);
            free(snake);
        }
    }

    return 0;
}