#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* snake_to_camel(const char *snake_str, char *camel_str) {
    int capitalize_next = 0;
    int i = 0;

    while (*snake_str) {
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
    /* Possible weaknesses found:
     *  Variable 'snake_case' can be declared as const array [constVariable]
     */
    char snake_case[] = "this_is_a_snake_case_string";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char camel_case[256];
    snake_to_camel(snake_case, camel_case);

    printf("%s\n", camel_case);

    return 0;
}