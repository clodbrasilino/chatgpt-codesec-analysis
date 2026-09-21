#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace_whitespace_underscore(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = strlen(input);
    
    char *output = (char *)malloc(input_len + 1);
    if (output == NULL) {
        return NULL;
    }

    size_t output_pos = 0;

    for (size_t i = 0; i < input_len; i++) {
        if (input[i] == ' ') {
            output[output_pos++] = '_';
        } else if (input[i] == '_') {
            output[output_pos++] = ' ';
        } else {
            output[output_pos++] = input[i];
        }
    }

    output[output_pos] = '\0';

    char *final_result = (char *)realloc(output, output_pos + 1);
    if (final_result == NULL) {
        free(output);
        return NULL;
    }

    return final_result;
}

int main(void) {
    const char *test_string = "hello world_this_is_a test";
    
    char *result = replace_whitespace_underscore(test_string);
    if (result == NULL) {
        fprintf(stderr, "Error: memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", test_string);
    printf("Modified: %s\n", result);

    free(result);
    return EXIT_SUCCESS;
}