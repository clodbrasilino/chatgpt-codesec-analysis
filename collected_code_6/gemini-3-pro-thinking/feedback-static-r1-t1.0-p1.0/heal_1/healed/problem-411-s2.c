#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char* snake_to_camel(const char *snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    size_t len = 0;
    const char *p = snake_str;
    while (*p != '\0') {
        len++;
        p++;
    }

    char *camel_str = (char *)malloc(len + 1);
    if (camel_str == NULL) {
        return NULL;
    }

    const char *src = snake_str;
    char *dst = camel_str;

    while (*src != '\0') {
        if (*src == '_' && *(src + 1) >= 'a' && *(src + 1) <= 'z') {
            *dst = toupper((unsigned char)*(src + 1));
            dst++;
            src += 2;
        } else {
            *dst = *src;
            dst++;
            src++;
        }
    }
    *dst = '\0';

    return camel_str;
}

int main(void) {
    const char *snake = "this_is_a_snake_case_string";
    char *camel = snake_to_camel(snake);

    if (camel != NULL) {
        printf("%s\n", camel);
        free(camel);
    } else {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}