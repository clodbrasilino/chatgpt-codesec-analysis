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
                *dest++ = *src;
            }
        }
        src++;
    }
    *dest = '\0';

    return result;
}

int main(void) {
    const char *snake_str = "this_is_a_snake_case_string";
    
    char *camel_str = snake_to_camel(snake_str);
    
    if (camel_str != NULL) {
        printf("%s\n", camel_str);
        free(camel_str);
    } else {
        fprintf(stderr, "Error during conversion\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}