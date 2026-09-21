#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* snake_to_camel(char *snake_case) {
    char *token = strtok(snake_case, "_");
    while (token != NULL) {
        size_t i = 0;
        while (token[i] != '\0') {
            if (i > 0 && token[i-1] == '_') {
                token[i-1] = '_';
                token[i] = toupper(token[i]);
            }
            i++;
        }
        token = strtok(NULL, "_");
    }
    return snake_case;
}

int main() {
    char snake_case[] = "this_is_a_snake_case_string";
    printf("Original: %s\n", snake_case);
    printf("CamelCase: %s\n", snake_to_camel(snake_case));
    return 0;
}