#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *snake_to_camel(const char *snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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
            capitalize_next = 1;
            src_idx++;
        } else {
            if (capitalize_next) {
                camel_str[dest_idx++] = toupper((unsigned char)snake_str[src_idx++]);
                capitalize_next = 0;
            } else {
                camel_str[dest_idx++] = snake_str[src_idx++];
            }
        }
    }

    camel_str[dest_idx] = '\0';
    return camel_str;
}

int main(void) {
    const char *inputs[] = {"android_tv", "google_pixel", "apple_watch", "convert_this_snake_case_string"};
    size_t num_inputs = sizeof(inputs) / sizeof(inputs[0]);

    for (size_t i = 0; i < num_inputs; i++) {
        char *output = snake_to_camel(inputs[i]);
        if (output != NULL) {
            printf("%s\n", output);
            free(output);
        }
    }

    return 0;
}