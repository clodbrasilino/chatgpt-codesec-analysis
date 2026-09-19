#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *camel_to_snake(const char *camel_str) {
    if (camel_str == NULL) {
        return NULL;
    }

    size_t len = strlen(camel_str);
    char *snake_str = (char *)malloc((len * 2) + 1);
    if (snake_str == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)camel_str[i])) {
            if (i > 0 && camel_str[i - 1] != '_') {
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

int main(int argc, const char *const argv[]) {
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            char *snake_case = camel_to_snake(argv[i]);
            if (snake_case != NULL) {
                printf("%s\n", snake_case);
                free(snake_case);
            }
        }
    } else {
        char buffer[4096];
        while (scanf("%4095s", buffer) == 1) {
            char *snake_case = camel_to_snake(buffer);
            if (snake_case != NULL) {
                printf("%s\n", snake_case);
                free(snake_case);
                fflush(stdout);
            }
        }
    }
    
    return 0;
}