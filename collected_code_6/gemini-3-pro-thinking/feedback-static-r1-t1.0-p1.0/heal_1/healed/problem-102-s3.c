#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *snake_to_camel(const char *snake_str, size_t max_len) {
    size_t len = 0;
    char *camel_str;
    size_t i;
    size_t j = 0;
    int capitalize_next = 0;

    if (snake_str == NULL) {
        return NULL;
    }

    while (len < max_len && snake_str[len] != '\0') {
        len++;
    }

    camel_str = (char *)malloc(len + 1);
    
    if (camel_str == NULL) {
        return NULL;
    }

    for (i = 0; i < len; i++) {
        if (snake_str[i] == '_') {
            if (j > 0) {
                capitalize_next = 1;
            }
        } else {
            if (capitalize_next != 0) {
                camel_str[j++] = (char)toupper((unsigned char)snake_str[i]);
                capitalize_next = 0;
            } else {
                camel_str[j++] = (char)tolower((unsigned char)snake_str[i]);
            }
        }
    }
    
    camel_str[j] = '\0';

    return camel_str;
}

int main(void) {
    const char input_string[] = "convert_this_snake_case_string";
    char *camel_case_string = snake_to_camel(input_string, sizeof(input_string));

    if (camel_case_string != NULL) {
        printf("%s\n", camel_case_string);
        free(camel_case_string);
        camel_case_string = NULL;
    } else {
        fprintf(stderr, "Memory allocation failed or invalid input.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}