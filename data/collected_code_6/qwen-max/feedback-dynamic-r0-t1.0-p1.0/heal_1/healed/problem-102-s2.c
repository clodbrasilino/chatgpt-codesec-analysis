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
    char snake_case[] = "this_is_a_snake_case_string";
    printf("Original: %s\n", snake_case);
    printf("CamelCase: %s\n", snake_to_camel(snake_case));
    return 0;
}