#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* snake_to_camel(const char* snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    size_t len = strlen(snake_str);
    char* camel_str = (char*)malloc(len + 1);
    if (camel_str == NULL) {
        return NULL;
    }

    int capitalize_next = 1;
    char* dest = camel_str;

    for (const char* src = snake_str; *src != '\0'; src++) {
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
    }
    
    *dest = '\0';
    return camel_str;
}

int main(void) {
    const char* snake = "this_is_a_snake_case_string";
    char* camel = snake_to_camel(snake);

    if (camel != NULL) {
        printf("%s\n", camel);
        free(camel);
    } else {
        fprintf(stderr, "Error converting string.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}