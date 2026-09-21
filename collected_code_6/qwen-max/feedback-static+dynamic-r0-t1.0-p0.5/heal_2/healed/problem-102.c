#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* snake_to_camel(const char *snake_str, char *camel_str, size_t size) {
    int capitalize_next = 0;
    int i = 0;

    while (*snake_str && i < (size - 1)) {
        if (*snake_str == '_') {
            capitalize_next = 1;
        } else if (capitalize_next) {
            camel_str[i++] = toupper((unsigned char)*snake_str);
            capitalize_next = 0;
        } else if (i == 0) {
            camel_str[i++] = toupper((unsigned char)*snake_str);
        } else {
            camel_str[i++] = *snake_str;
        }
        snake_str++;
    }
    camel_str[i] = '\0';

    return camel_str;
}

int main() {
    const char snake_case[] = "this_is_a_snake_case_string";
    char camel_case[256];
    snake_to_camel(snake_case, camel_case, sizeof(camel_case));

    printf("%s\n", camel_case);

    return 0;
}