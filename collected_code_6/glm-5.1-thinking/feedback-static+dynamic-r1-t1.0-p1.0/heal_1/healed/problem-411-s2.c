#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *snake_to_camel(const char *snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (snake_str[len] != '\0') {
        len++;
    }

    char *camel_str = malloc(len + 1);
    if (camel_str == NULL) {
        return NULL;
    }

    size_t dst_idx = 0;
    size_t src_idx = 0;

    if (len > 0 && islower((unsigned char)snake_str[0])) {
        camel_str[dst_idx++] = toupper((unsigned char)snake_str[0]);
        src_idx = 1;
    }

    while (src_idx < len) {
        if (snake_str[src_idx] == '_') {
            src_idx++;
            if (src_idx < len && islower((unsigned char)snake_str[src_idx])) {
                camel_str[dst_idx++] = toupper((unsigned char)snake_str[src_idx]);
                src_idx++;
            }
        } else {
            camel_str[dst_idx++] = snake_str[src_idx++];
        }
    }

    camel_str[dst_idx] = '\0';
    return camel_str;
}

int main(void) {
    const char *input1 = "convert_this_snake_case_string";
    char *output1 = snake_to_camel(input1);
    if (output1 != NULL) {
        printf("Input: %s\nOutput: %s\n", input1, output1);
        free(output1);
    }

    const char *input2 = "alreadycamelcase";
    char *output2 = snake_to_camel(input2);
    if (output2 != NULL) {
        printf("Input: %s\nOutput: %s\n", input2, output2);
        free(output2);
    }

    const char *input3 = "apple_watch";
    char *output3 = snake_to_camel(input3);
    if (output3 != NULL) {
        printf("Input: %s\nOutput: %s\n", input3, output3);
        free(output3);
    }

    return 0;
}