#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *snake_to_camel(const char *snake_case) {
    if (snake_case == NULL) {
        return NULL;
    }

    size_t len = strlen(snake_case);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    char *dest = result;
    const char *src = snake_case;
    int capitalize_next = 1;

    while (*src != '\0') {
        if (*src == '_') {
            capitalize_next = 1;
        } else {
            if (capitalize_next) {
                *dest++ = toupper((unsigned char)*src);
                capitalize_next = 0;
            } else {
                *dest++ = tolower((unsigned char)*src);
            }
        }
        src++;
    }
    *dest = '\0';

    return result;
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            char *camel_str = snake_to_camel(argv[i]);
            if (camel_str != NULL) {
                printf("%s\n", camel_str);
                free(camel_str);
            }
        }
    } else {
        char buffer[2048];
        while (scanf("%2047s", buffer) == 1) {
            char *camel_str = snake_to_camel(buffer);
            if (camel_str != NULL) {
                printf("%s\n", camel_str);
                free(camel_str);
            }
        }
    }
    return 0;
}