#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *snake_to_camel(const char *snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    size_t len = strlen(snake_str);
    char *camel_str = malloc(len + 1);
    if (camel_str == NULL) {
        return NULL;
    }

    size_t camel_idx = 0;
    for (size_t i = 0; i < len; i++) {
        if (snake_str[i] == '_') {
            i++;
            if (i < len) {
                camel_str[camel_idx++] = toupper((unsigned char)snake_str[i]);
            } else {
                camel_str[camel_idx++] = '_';
            }
        } else {
            camel_str[camel_idx++] = snake_str[i];
        }
    }
    camel_str[camel_idx] = '\0';

    if (camel_idx > 0) {
        camel_str[0] = toupper((unsigned char)camel_str[0]);
    }

    return camel_str;
}

int main(void) {
    const char *input0 = "android_tv";
    char *output0 = snake_to_camel(input0);
    if (output0 != NULL) {
        printf("%s\n", output0);
        free(output0);
    }

    const char *input1 = "google_pixel";
    char *output1 = snake_to_camel(input1);
    if (output1 != NULL) {
        printf("%s\n", output1);
        free(output1);
    }

    const char *input2 = "apple_watch";
    char *output2 = snake_to_camel(input2);
    if (output2 != NULL) {
        printf("%s\n", output2);
        free(output2);
    }

    const char *input = "convert_this_snake_case_string";
    char *output = snake_to_camel(input);
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }
    return 0;
}