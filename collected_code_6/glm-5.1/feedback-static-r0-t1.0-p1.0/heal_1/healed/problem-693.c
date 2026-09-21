#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_multiple_spaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t src_pos = 0;
    size_t dst_pos = 0;

    while (src_pos < len) {
        if (str[src_pos] == ' ') {
            result[dst_pos++] = ' ';
            while (src_pos < len && str[src_pos] == ' ') {
                src_pos++;
            }
        } else {
            result[dst_pos++] = str[src_pos++];
        }
    }

    result[dst_pos] = '\0';

    return result;
}

int main(void) {
    const char *input = "This   is  a    test   string.";
    char *output = remove_multiple_spaces(input);

    if (output != NULL) {
        printf("Original: '%s'\n", input);
        printf("Modified: '%s'\n", output);
        free(output);
    }

    return 0;
}