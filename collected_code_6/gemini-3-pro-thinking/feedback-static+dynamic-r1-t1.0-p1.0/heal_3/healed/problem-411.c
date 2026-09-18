#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *snake_to_camel(const char *snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    size_t len = strlen(snake_str);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    int capitalize_next = 1;

    for (size_t i = 0; i < len; i++) {
        if (snake_str[i] == '_') {
            capitalize_next = 1;
        } else {
            if (capitalize_next) {
                result[j++] = (char)toupper((unsigned char)snake_str[i]);
                capitalize_next = 0;
            } else {
                result[j++] = (char)tolower((unsigned char)snake_str[i]);
            }
        }
    }
    result[j] = '\0';

    return result;
}

int main(int argc, const char *argv[]) {
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            char *camel = snake_to_camel(argv[i]);
            if (camel != NULL) {
                printf("%s\n", camel);
                free(camel);
            }
        }
    } else {
        char buffer[2048];
        while (scanf("%2047s", buffer) == 1) {
            char *camel = snake_to_camel(buffer);
            if (camel != NULL) {
                printf("%s\n", camel);
                free(camel);
            }
        }
    }

    return EXIT_SUCCESS;
}