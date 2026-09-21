#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 65536

char *remove_lowercase_substrings(const char *input);

char *remove_lowercase_substrings(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    if (regcomp(&regex, "[a-z]+", REG_EXTENDED) != 0) {
        return NULL;
    }

    size_t input_len = strnlen(input, MAX_INPUT_LEN);
    if (input_len == MAX_INPUT_LEN) {
        regfree(&regex);
        return NULL;
    }

    char *result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    const char *cursor = input;
    char *out_cursor = result;
    size_t dest_capacity = input_len + 1;
    size_t dest_used = 0;
    regmatch_t pmatch[1];

    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        size_t prefix_len = (size_t)pmatch[0].rm_so;
        if (prefix_len > 0) {
            if (dest_used + prefix_len < dest_capacity) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(out_cursor, cursor, prefix_len);
                out_cursor += prefix_len;
                dest_used += prefix_len;
            } else {
                break;
            }
        }
        cursor += pmatch[0].rm_eo;
    }

    size_t cursor_offset = (size_t)(cursor - input);
    if (cursor_offset < input_len) {
        size_t remaining_max = input_len - cursor_offset;
        size_t remaining_len = strnlen(cursor, remaining_max);
        
        if (remaining_len > 0) {
            if (dest_used + remaining_len < dest_capacity) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(out_cursor, cursor, remaining_len);
                out_cursor += remaining_len;
            }
        }
    }
    
    *out_cursor = '\0';
    regfree(&regex);

    return result;
}

int main(void) {
    const char *test_input = "Helloworld! This IS A test123String.";
    char *processed_output = remove_lowercase_substrings(test_input);

    if (processed_output != NULL) {
        printf("%s\n", processed_output);
        free(processed_output);
    } else {
        fprintf(stderr, "Error processing string or memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}