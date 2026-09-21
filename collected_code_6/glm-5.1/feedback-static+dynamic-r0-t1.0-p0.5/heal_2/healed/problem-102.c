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
        if (snake_str[i - 1] == '_') {
            if (snake_str[i] >= 'a' && snake_str[i] <= 'z') {
                camel_str[j++] = snake_str[i] - 32;
            } else {
                camel_str[j++] = snake_str[i];
            }
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
    const char *input1 = "python_program";
    char *output1 = snake_to_camel(input1);
    if (output1 != NULL) {
        printf("%s\n", output1);
        free(output1);
    }

    const char *input2 = "python_language";
    char *output2 = snake_to_camel(input2);
    if (output2 != NULL) {
        printf("%s\n", output2);
        free(output2);
    }

    const char *input3 = "programming_language";
    char *output3 = snake_to_camel(input3);
    if (output3 != NULL) {
        printf("%s\n", output3);
        free(output3);
    }

    return 0;
}