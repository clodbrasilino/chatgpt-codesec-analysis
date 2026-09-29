#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* snake_to_camel(char *snake_case) {
    for (char *token = snake_case; *token; token++) {
        if (*token == '_') {
            *token = toupper(*(token + 1));
            memmove(token, token + 1, strlen(token));
        }
    }
    return snake_case;
}

int main() {
    char test0[] = "python_program";
    char test1[] = "python_language";
    char test2[] = "programming_language";

    printf("Original: %s\n", test0);
    printf("CamelCase: %s\n", snake_to_camel(test0));

    printf("Original: %s\n", test1);
    printf("CamelCase: %s\n", snake_to_camel(test1));

    printf("Original: %s\n", test2);
    printf("CamelCase: %s\n", snake_to_camel(test2));

    return 0;
}