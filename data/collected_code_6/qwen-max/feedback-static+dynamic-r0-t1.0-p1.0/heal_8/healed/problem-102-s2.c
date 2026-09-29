#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* snake_to_camel(char *snake_case) {
    char *src = snake_case;
    char *dest = snake_case;

    while (*src) {
        if (*src == '_') {
            if (*(src + 1)) {
                *dest++ = toupper(*(src + 1));
                src++;
            } else {
                *dest = '\0';
                break;
            }
        } else {
            *dest++ = *src;
        }
        src++;
    }
    *dest = '\0';
    return snake_case;
}

int main() {
    char snake_case[] = "this_is_a_snake_case_string";
    printf("Original: %s\n", snake_case);
    printf("CamelCase: %s\n", snake_to_camel(snake_case));
    return 0;
}