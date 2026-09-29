#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *snake_to_camel(const char *snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    size_t len = strlen(snake_str);
    char *camel_str = (char *)malloc(len + 1);
    if (camel_str == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (snake_str[i] == '_') {
            if (i + 1 < len && snake_str[i + 1] >= 'a' && snake_str[i + 1] <= 'z') {
                camel_str[j++] = snake_str[i + 1] - 32;
                i++;
            }
        } else {
            camel_str[j++] = snake_str[i];
        }
    }
    camel_str[j] = '\0';

    char *shrunk_str = (char *)realloc(camel_str, j + 1);
    if (shrunk_str != NULL) {
        camel_str = shrunk_str;
    }

    return camel_str;
}

int main(void) {
    const char *input = "convert_this_snake_case_string";
    char *output = snake_to_camel(input);

    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }

    return 0;
}