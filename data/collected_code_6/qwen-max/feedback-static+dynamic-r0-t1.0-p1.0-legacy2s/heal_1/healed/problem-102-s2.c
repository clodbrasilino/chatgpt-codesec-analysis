#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* snake_to_camel(char *snake_str) {
    int i, capitalize_next = 1;
    char *src = snake_str;
    char *dst = src;
    while (*src) {
        if (*src == '_') {
            capitalize_next = 1;
        } else if (capitalize_next) {
            *dst++ = toupper(*src);
            capitalize_next = 0;
        } else {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
    return snake_str;
}

int main() {
    char snake_case[] = "this_is_a_test_string";
    char *camel_case = snake_to_camel(snake_case);
    printf("%s\n", camel_case);
    return 0;
}