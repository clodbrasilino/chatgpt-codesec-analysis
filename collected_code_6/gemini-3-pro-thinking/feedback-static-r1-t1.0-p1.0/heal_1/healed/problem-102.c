#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *snake_to_camel(const char *snake, size_t max_len);

char *snake_to_camel(const char *snake, size_t max_len) {
    if (snake == NULL || max_len == 0) {
        return NULL;
    }

    size_t len = 0;
    while (len < max_len && snake[len] != '\0') {
        len++;
    }

    char *camel = (char *)malloc(len + 1);
    
    if (camel == NULL) {
        return NULL;
    }

    size_t j = 0;
    int capitalize_next = 0;

    for (size_t i = 0; i < len; i++) {
        if (snake[i] == '_') {
            if (j > 0) {
                capitalize_next = 1;
            }
        } else {
            if (capitalize_next && j > 0) {
                camel[j++] = (char)toupper((unsigned char)snake[i]);
                capitalize_next = 0;
            } else {
                camel[j++] = (char)tolower((unsigned char)snake[i]);
            }
        }
    }
    
    camel[j] = '\0';
    return camel;
}

int main(void) {
    const char input[] = "example_snake_case_string";
    char *output = snake_to_camel(input, sizeof(input));

    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Memory allocation or invalid input error.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}