#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_lowercase_substrings(const char *input);

char *remove_lowercase_substrings(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int comp_res = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (comp_res != 0) {
        return NULL;
    }

    size_t input_len = strlen(input);
    char *result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    const char *cursor = input;
    char *out_cursor = result;
    regmatch_t pmatch[1];

    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        size_t prefix_len = pmatch[0].rm_so;
        if (prefix_len > 0) {
            memcpy(out_cursor, cursor, prefix_len);
            out_cursor += prefix_len;
        }
        cursor += pmatch[0].rm_eo;
    }

    size_t remaining_len = strlen(cursor);
    if (remaining_len > 0) {
        memcpy(out_cursor, cursor, remaining_len);
        out_cursor += remaining_len;
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