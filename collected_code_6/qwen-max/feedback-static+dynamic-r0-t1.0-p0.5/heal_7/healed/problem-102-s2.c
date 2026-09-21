#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* snake_to_camel(char *snake_str) {
    char *camel_str = snake_str;
    int capitalize_next = 1;

    while (*snake_str) {
        if (*snake_str == '_') {
            capitalize_next = 1;
            snake_str++;
            continue;
        }
        if (capitalize_next) {
            *camel_str = toupper((unsigned char)*snake_str);
            capitalize_next = 0;
        } else if (islower((unsigned char)*snake_str)) {
            *camel_str = *snake_str;
        }
        camel_str++;
        snake_str++;
    }
    *camel_str = '\0';
    return camel_str - (camel_str - snake_str);
}

int main() {
    char snake_case[] = "this_is_a_snake_case_string";
    printf("%s\n", snake_to_camel(snake_case));

    char test0[] = "python_program";
    printf("%s\n", snake_to_camel(test0));

    char test1[] = "python_language";
    printf("%s\n", snake_to_camel(test1));

    char test2[] = "programming_language";
    printf("%s\n", snake_to_camel(test2));

    return 0;
}