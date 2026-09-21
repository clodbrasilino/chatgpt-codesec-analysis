#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* snake_to_camel(char *snake_str) {
    char *camel_str = snake_str;
    int capitalize_next = 0;

    while (*snake_str) {
        if (*snake_str == '_') {
            capitalize_next = 1;
            snake_str++;
            continue;
        }
        if (capitalize_next) {
            *camel_str = toupper((unsigned char)*snake_str);
            capitalize_next = 0;
        } else {
            *camel_str = *snake_str;
        }
        camel_str++;
        snake_str++;
    }
    *camel_str = '\0';
    /* Possible weaknesses found:
     *  use of undeclared identifier 'snake_case'
     *  each undeclared identifier is reported only once for each function it appears in
     *  'snake_case' undeclared (first use in this function)
     */
    return camel_str - (snake_str - snake_case);
}

int main() {
    char snake_case[] = "this_is_a_snake_case_string";
    printf("%s\n", snake_to_camel(snake_case));
    return 0;
}