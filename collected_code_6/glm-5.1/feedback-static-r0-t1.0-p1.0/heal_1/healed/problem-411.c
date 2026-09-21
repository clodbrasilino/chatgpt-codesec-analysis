#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *snake_to_camel(const char *snake_str) {
    if (!snake_str) {
        return NULL;
    }

    const char *p = snake_str;
    size_t len = 0;
    size_t underscores = 0;
    while (*p) {
        if (*p == '_' && *(p + 1) >= 'a' && *(p + 1) <= 'z') {
            underscores++;
            p++;
        }
        len++;
        p++;
    }

    if (len == 0) {
        char *empty = malloc(1);
        if (!empty) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    char *result = malloc(len - underscores + 1);
    if (!result) {
        return NULL;
    }

    size_t dst_idx = 0;
    p = snake_str;

    while (*p) {
        if (*p == '_' && *(p + 1) >= 'a' && *(p + 1) <= 'z') {
            result[dst_idx++] = *(p + 1) - 32;
            p += 2;
        } else {
            result[dst_idx++] = *p++;
        }
    }

    result[dst_idx] = '\0';

    return result;
}

int main(void) {
    const char *input = "this_is_a_snake_case_string";
    char *output = snake_to_camel(input);
    
    if (output) {
        printf("%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Conversion failed\n");
        return 1;
    }
    
    return 0;
}