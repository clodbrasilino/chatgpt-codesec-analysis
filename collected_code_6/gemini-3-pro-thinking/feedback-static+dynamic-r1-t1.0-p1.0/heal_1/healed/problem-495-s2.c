#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_SIZE 65536

char *remove_lowercase_substrings(const char *input);

char *remove_lowercase_substrings(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = strnlen(input, MAX_INPUT_SIZE);
    
    char *safe_input = (char *)malloc(input_len + 1);
    if (safe_input == NULL) {
        return NULL;
    }
    
    memcpy(safe_input, input, input_len);
    safe_input[input_len] = '\0';

    regex_t regex;
    if (regcomp(&regex, "[a-z]+", REG_EXTENDED) != 0) {
        free(safe_input);
        return NULL;
    }

    char *result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        free(safe_input);
        return NULL;
    }

    const char *cursor = safe_input;
    char *out_cursor = result;
    size_t remaining_capacity = input_len;
    regmatch_t pmatch[1];

    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        size_t prefix_len = (size_t)pmatch[0].rm_so;
        
        if (prefix_len > 0) {
            size_t copy_len = (prefix_len < remaining_capacity) ? prefix_len : remaining_capacity;
            memcpy(out_cursor, cursor, copy_len);
            out_cursor += copy_len;
            remaining_capacity -= copy_len;
        }
        cursor += pmatch[0].rm_eo;
    }

    size_t cursor_offset = (size_t)(cursor - safe_input);
    if (cursor_offset < input_len) {
        size_t remaining_len = input_len - cursor_offset;
        size_t copy_len = (remaining_len < remaining_capacity) ? remaining_len : remaining_capacity;
        memcpy(out_cursor, cursor, copy_len);
        out_cursor += copy_len;
    }
    
    *out_cursor = '\0';

    regfree(&regex);
    free(safe_input);

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