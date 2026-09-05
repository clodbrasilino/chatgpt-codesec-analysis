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

    size_t src_idx = 0;
    size_t dest_idx = 0;
    int capitalize_next = 1;

    while (src_idx < len) {
        if (snake_str[src_idx] == '_') {
            if (src_idx + 1 < len && islower(snake_str[src_idx + 1])) {
                camel_str[dest_idx++] = toupper(snake_str[src_idx + 1]);
                src_idx += 2;
            } else {
                src_idx++;
            }
        } else {
            if (capitalize_next && islower(snake_str[src_idx])) {
                camel_str[dest_idx++] = toupper(snake_str[src_idx]);
            } else {
                camel_str[dest_idx++] = snake_str[src_idx];
            }
            capitalize_next = 0;
            src_idx++;
        }
    }

    camel_str[dest_idx] = '\0';
    return camel_str;
}

int main(void) {
    const char *input1 = "android_tv";
    char *output1 = snake_to_camel(input1);
    if (output1 != NULL) {
        printf("%s\n", output1);
        free(output1);
    }

    const char *input2 = "google_pixel";
    char *output2 = snake_to_camel(input2);
    if (output2 != NULL) {
        printf("%s\n", output2);
        free(output2);
    }

    const char *input3 = "apple_watch";
    char *output3 = snake_to_camel(input3);
    if (output3 != NULL) {
        printf("%s\n", output3);
        free(output3);
    }

    const char *input4 = "convert_this_snake_case_string";
    char *output4 = snake_to_camel(input4);
    if (output4 != NULL) {
        printf("%s\n", output4);
        free(output4);
    }

    return 0;
}