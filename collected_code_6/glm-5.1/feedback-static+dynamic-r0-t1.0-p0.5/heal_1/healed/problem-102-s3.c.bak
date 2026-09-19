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
            i++;
            if (i < len && snake_str[i] >= 'a' && snake_str[i] <= 'z') {
                camel_str[j++] = snake_str[i] - 32;
            } else if (i < len) {
                camel_str[j++] = snake_str[i];
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

    if (camel_str[0] >= 'a' && camel_str[0] <= 'z') {
        camel_str[0] = camel_str[0] - 32;
    }

    return camel_str;
}

int main(void) {
    const char *input0 = "python_program";
    char *output0 = snake_to_camel(input0);
    if (output0 != NULL) {
        printf("%s\n", output0);
        free(output0);
    }

    const char *input1 = "python_language";
    char *output1 = snake_to_camel(input1);
    if (output1 != NULL) {
        printf("%s\n", output1);
        free(output1);
    }

    const char *input2 = "programming_language";
    char *output2 = snake_to_camel(input2);
    if (output2 != NULL) {
        printf("%s\n", output2);
        free(output2);
    }

    return 0;
}