#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char* snake_to_camel(const char *snake_str) {
    size_t len = strlen(snake_str);
    char *output = (char *)malloc(len + 1);
    if (output == NULL) {
        return NULL;
    }
    int index = 0, capitalize_next = 0;

    for (size_t i = 0; i <= len; ++i) {
        if (i < len && snake_str[i] == '_') {
            capitalize_next = 1;
        } else if (capitalize_next && isalpha(snake_str[i])) {
            output[index++] = toupper(snake_str[i]);
            capitalize_next = 0;
        } else {
            output[index++] = snake_str[i];
        }
    }
    output[len] = '\0';
    return output;
}

int main() {
    const char snake_case[] = "this_is_a_snake_case_string";
    char *camel_case = snake_to_camel(snake_case);

    if (camel_case != NULL) {
        printf("%s\n", camel_case);
        free(camel_case);
    }

    return 0;
}