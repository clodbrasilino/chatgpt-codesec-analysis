#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* snake_to_camel(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '_') {
            memmove(&str[i], &str[i + 1], strlen(&str[i]));
            str[i] = toupper(str[i]);
            i--; // Adjust index after removing underscore
        } else if (i == 0 || (i > 0 && str[i - 1] == '_')) {
            str[i] = toupper(str[i]);
        }
    }
    return str;
}

int main() {
    char input[] = "example_snake_case_string";
    char *result = snake_to_camel(input);
    printf("%s\n", result);
    return 0;
}