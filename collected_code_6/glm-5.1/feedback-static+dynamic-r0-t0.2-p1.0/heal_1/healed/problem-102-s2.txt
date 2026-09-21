#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *snake_to_camel(const char *snake_str) {
    if (snake_str == NULL || snake_str[0] == '\0') {
        return NULL;
    }

    size_t len = 0;
    while (snake_str[len] != '\0') {
        len++;
    }

    char *camel_str = (char *)malloc(len + 1);
    if (camel_str == NULL) {
        return NULL;
    }

    size_t j = 0;
    if (islower((unsigned char)snake_str[0])) {
        camel_str[j++] = (char)toupper((unsigned char)snake_str[0]);
    } else {
        camel_str[j++] = snake_str[0];
    }

    for (size_t i = 1; i < len; i++) {
        if (snake_str[i] == '_') {
            if (i + 1 < len && islower((unsigned char)snake_str[i + 1])) {
                camel_str[j++] = (char)toupper((unsigned char)snake_str[i + 1]);
                i++;
            } else {
                camel_str[j++] = snake_str[i];
            }
        } else {
            camel_str[j++] = snake_str[i];
        }
    }

    camel_str[j] = '\0';
    return camel_str;
}

int main(void) {
    const char *input = "convert_this_snake_case_string";
    char *output = snake_to_camel(input);

    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("%s\n", output);
    free(output);
    output = NULL;

    return 0;
}