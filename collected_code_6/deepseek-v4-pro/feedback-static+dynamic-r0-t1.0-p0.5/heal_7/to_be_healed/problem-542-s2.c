#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_OUTPUT_SIZE 4096

static char *allocate_output_buffer(size_t input_len) {
    size_t output_capacity;
    char *output;
    
    output_capacity = (input_len * 2) + 1;
    if (output_capacity < input_len) {
        return NULL;
    }
    
    output = calloc(output_capacity, sizeof(char));
    return output;
}

static int is_safe_copy(size_t dest_offset, size_t src_offset, size_t copy_len,
                         size_t dest_size, size_t src_size) {
    if (dest_offset > dest_size - 1) return 0;
    if (src_offset > src_size) return 0;
    if (copy_len > dest_size - 1 - dest_offset) return 0;
    if (copy_len > src_size - src_offset) return 0;
    return 1;
}

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

    output = allocate_output_buffer(input_len);
    if (output == NULL) {
        return NULL;
    }
    output_capacity = (input_len * 2) + 1;

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

            if (copy_len > 0) {
                if (!is_safe_copy(output_pos, input_pos, copy_len, 
                                  output_capacity, input_len)) {
                    free(output);
                    regfree(&regex);
                    return NULL;
                }

                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
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

            if (remaining > 0) {
                if (!is_safe_copy(output_pos, input_pos, remaining,
                                  output_capacity, input_len)) {
                    free(output);
                    regfree(&regex);
                    return NULL;
                }

                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
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

    output[output_pos] = '\0';
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