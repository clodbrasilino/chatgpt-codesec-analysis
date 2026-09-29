#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* snake_to_camel(char *snake_case) {
    char *token = strstr(snake_case, "_");
    while (token != NULL) {
        token++;
        *token = toupper(*token);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        memmove(token, token + 1, strlen(token) + 1);
        token = strstr(token, "_");
    }
    return snake_case;
}

int main() {
    char snake_case[] = "this_is_a_snake_case_string";
    printf("Original: %s\n", snake_case);
    printf("CamelCase: %s\n", snake_to_camel(snake_case));
    return 0;
}