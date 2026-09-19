#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char* snake_to_camel(char *snake_str) {
    char *result = malloc(strlen(snake_str) + 1);
    char *p = snake_str;
    char *new_p = result;
    int capitalize_next = 1;

    while (*p) {
        if (*p == '_') {
            p++;
            capitalize_next = 1;
        } else {
            if (capitalize_next || new_p == result) {
                *new_p = toupper((unsigned char)*p);
                capitalize_next = 0;
            } else {
                *new_p = *p;
            }
            new_p++;
            p++;
        }
    }
    *new_p = '\0';

    return result;
}

int main() {
    char *snake_case1 = "python_program";
    char *snake_case2 = "python_language";
    char *snake_case3 = "programming_language";

    printf("%s\n", snake_to_camel(strdup(snake_case1)));
    printf("%s\n", snake_to_camel(strdup(snake_case2)));
    printf("%s\n", snake_to_camel(strdup(snake_case3)));

    free(snake_case1);
    free(snake_case2);
    free(snake_case3);

    return 0;
}