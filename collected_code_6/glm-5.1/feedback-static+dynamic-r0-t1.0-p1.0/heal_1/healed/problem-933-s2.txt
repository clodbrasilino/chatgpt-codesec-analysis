#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *camel_to_snake(const char *camel_str) {
    if (camel_str == NULL) {
        return NULL;
    }

    size_t len = strlen(camel_str);
    if (len == 0) {
        char *empty = malloc(1);
        if (empty != NULL) {
            empty[0] = '\0';
        }
        return empty;
    }

    char *snake_str = malloc(len * 2 + 1);
    if (snake_str == NULL) {
        return NULL;
    }

    size_t src_offset = 0;
    size_t dest_offset = 0;

    while (src_offset < len) {
        if (isupper((unsigned char)camel_str[src_offset])) {
            if (src_offset > 0) {
                snake_str[dest_offset++] = '_';
            }
            snake_str[dest_offset++] = tolower((unsigned char)camel_str[src_offset++]);
        } else {
            snake_str[dest_offset++] = tolower((unsigned char)camel_str[src_offset++]);
        }
    }

    snake_str[dest_offset] = '\0';

    char *final_str = realloc(snake_str, dest_offset + 1);
    if (final_str == NULL) {
        free(snake_str);
        return NULL;
    }

    return final_str;
}

int main(void) {
    const char *inputs[] = {
        "camelCaseString",
        "AnotherExample",
        "single",
        "XMLHttpRequest",
        "A",
        "",
        "google_assistant",
        "chrome_cast",
        "quad_core"
    };
    size_t count = sizeof(inputs) / sizeof(inputs[0]);

    for (size_t i = 0; i < count; i++) {
        char *result = camel_to_snake(inputs[i]);
        if (result == NULL) {
            printf("Input: %s\nOutput: [Allocation error]\n\n", inputs[i]);
        } else {
            printf("Input: %s\nOutput: %s\n\n", inputs[i], result);
            free(result);
        }
    }

    return 0;
}