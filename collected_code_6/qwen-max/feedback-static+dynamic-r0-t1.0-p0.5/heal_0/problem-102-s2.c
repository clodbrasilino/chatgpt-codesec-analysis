#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* snake_to_camel(char *snake_str) {
    char *camel_str = snake_str;
    int capitalize_next = 0;

    while (*snake_str) {
        if (*snake_str == '_') {
            capitalize_next = 1;
            *snake_str = '\0';
            snake_str++;
            continue;
        }
        if (capitalize_next) {
            *snake_str = toupper((unsigned char)*snake_str);
            capitalize_next = 0;
        }
        *camel_str++ = *snake_str++;
    }
    *camel_str = '\0';
    return camel_str - strlen(snake_str);
}

int main() {
    char snake_case[] = "this_is_a_snake_case_string";
    snake_to_camel(snake_case);
    printf("%s\n", snake_case);
    return 0;
}