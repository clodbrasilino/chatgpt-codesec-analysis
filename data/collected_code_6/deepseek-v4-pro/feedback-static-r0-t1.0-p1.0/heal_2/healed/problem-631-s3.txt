#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace_whitespace_underscore(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = strlen(input);
    size_t output_size = input_len + 1;
    char *output = (char *)malloc(output_size);
    if (output == NULL) {
        return NULL;
    }

    size_t output_pos = 0;
    size_t input_pos = 0;

    while (input_pos < input_len) {
        if (input[input_pos] == ' ') {
            if (output_pos + 1 >= output_size) {
                size_t new_size = output_size * 2;
                char *temp = (char *)realloc(output, new_size);
                if (temp == NULL) {
                    free(output);
                    return NULL;
                }
                output = temp;
                output_size = new_size;
            }
            output[output_pos++] = '_';
            input_pos++;
        } else if (input[input_pos] == '_') {
            if (output_pos + 1 >= output_size) {
                size_t new_size = output_size * 2;
                char *temp = (char *)realloc(output, new_size);
                if (temp == NULL) {
                    free(output);
                    return NULL;
                }
                output = temp;
                output_size = new_size;
            }
            output[output_pos++] = ' ';
            input_pos++;
        } else {
            if (output_pos + 1 >= output_size) {
                size_t new_size = output_size * 2;
                char *temp = (char *)realloc(output, new_size);
                if (temp == NULL) {
                    free(output);
                    return NULL;
                }
                output = temp;
                output_size = new_size;
            }
            output[output_pos++] = input[input_pos++];
        }
    }

    if (output_pos >= output_size) {
        size_t new_size = output_size + 1;
        char *temp = (char *)realloc(output, new_size);
        if (temp == NULL) {
            free(output);
            return NULL;
        }
        output = temp;
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