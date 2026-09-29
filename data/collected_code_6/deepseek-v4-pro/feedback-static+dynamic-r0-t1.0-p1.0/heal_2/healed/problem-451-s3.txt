#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *remove_whitespaces(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = strnlen(input, SIZE_MAX);
    char *result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t dst_pos = 0;
    for (size_t src_pos = 0; src_pos < input_len; src_pos++) {
        if (!isspace((unsigned char)input[src_pos])) {
            if (dst_pos >= input_len) {
                free(result);
                return NULL;
            }
            result[dst_pos++] = input[src_pos];
        }
    }

    result[dst_pos] = '\0';

    char *final_result = (char *)realloc(result, dst_pos + 1);
    if (final_result == NULL) {
        free(result);
        return NULL;
    }

    return final_result;
}

int main(void) {
    const char *test_string = "Hello   World\t\n  from C!";
    char *cleaned = remove_whitespaces(test_string);

    if (cleaned == NULL) {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    printf("Original: '%s'\n", test_string);
    printf("Cleaned:  '%s'\n", cleaned);

    free(cleaned);
    return EXIT_SUCCESS;
}