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
    if (len > 0 && snake_str[0] >= 'a' && snake_str[0] <= 'z') {
        camel_str[j++] = snake_str[0] - 32;
    }

    for (size_t i = 1; i < len; i++) {
        if (snake_str[i - 1] == '_' && snake_str[i] >= 'a' && snake_str[i] <= 'z') {
            camel_str[j++] = snake_str[i] - 32;
        } else if (snake_str[i] != '_') {
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
    const char *test_cases[] = {
        "python_program",
        "python_language",
        "programming_language"
    };
    
    for (int i = 0; i < 3; i++) {
        char *output = snake_to_camel(test_cases[i]);
        if (output != NULL) {
            printf("%s\n", output);
            free(output);
        }
    }

    return 0;
}