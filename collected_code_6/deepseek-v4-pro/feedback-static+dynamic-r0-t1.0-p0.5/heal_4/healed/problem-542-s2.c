#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_OUTPUT_SIZE 4096

char *replace_chars_with_colon(const char *input) {
    regex_t regex;
    regmatch_t match;
    const char *pattern = "[ ,.]";
    size_t input_len;
    size_t output_pos = 0;
    size_t input_pos = 0;
    int result;
    char *output;
    size_t output_capacity;

    if (input == NULL) {
        return NULL;
    }

    input_len = strnlen(input, MAX_OUTPUT_SIZE);
    if (input_len >= MAX_OUTPUT_SIZE) {
        return NULL;
    }

    output_capacity = input_len * 2 + 1;
    output = calloc(output_capacity, sizeof(char));
    if (output == NULL) {
        return NULL;
    }

    result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result != 0) {
        free(output);
        return NULL;
    }

    while (input_pos < input_len) {
        result = regexec(&regex, input + input_pos, 1, &match, 0);
        if (result == 0) {
            size_t match_start = match.rm_so;
            size_t match_end = match.rm_eo;
            size_t copy_len = match_start;
            size_t available_space = output_capacity - output_pos - 1;

            if (copy_len > available_space) {
                copy_len = available_space;
            }

            if (copy_len > 0) {
                if (output_pos + copy_len > output_capacity) {
                    free(output);
                    regfree(&regex);
                    return NULL;
                }
                memcpy(output + output_pos, input + input_pos, copy_len);
                output_pos += copy_len;
            }

            if (output_pos + 1 >= output_capacity) {
                free(output);
                regfree(&regex);
                return NULL;
            }
            output[output_pos++] = ':';

            input_pos += match_end;
        } else if (result == REG_NOMATCH) {
            size_t remaining = input_len - input_pos;
            size_t available_space = output_capacity - output_pos - 1;

            if (remaining > available_space) {
                remaining = available_space;
            }

            if (remaining > 0) {
                if (output_pos + remaining > output_capacity) {
                    free(output);
                    regfree(&regex);
                    return NULL;
                }
                memcpy(output + output_pos, input + input_pos, remaining);
                output_pos += remaining;
            }
            break;
        } else {
            free(output);
            regfree(&regex);
            return NULL;
        }
    }

    if (output_pos < output_capacity) {
        output[output_pos] = '\0';
    } else {
        output[output_capacity - 1] = '\0';
    }
    regfree(&regex);
    return output;
}

int main(void) {
    const char *test_string = "Hello, world. This is a test";
    char *result;

    result = replace_chars_with_colon(test_string);
    if (result != NULL) {
        printf("Original: %s\n", test_string);
        printf("Modified: %s\n", result);
        free(result);
    } else {
        printf("Error processing string\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}