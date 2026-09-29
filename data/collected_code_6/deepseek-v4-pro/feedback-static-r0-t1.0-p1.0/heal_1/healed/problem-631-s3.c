#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *replace_whitespace_underscore(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t whitespace_regex;
    regex_t underscore_regex;
    int ret;

    ret = regcomp(&whitespace_regex, "[ ]", REG_EXTENDED);
    if (ret) {
        return NULL;
    }

    ret = regcomp(&underscore_regex, "_", REG_EXTENDED);
    if (ret) {
        regfree(&whitespace_regex);
        return NULL;
    }

    size_t input_len = strlen(input);
    size_t output_size = input_len + 1;
    char *output = (char *)malloc(output_size);
    if (output == NULL) {
        regfree(&whitespace_regex);
        regfree(&underscore_regex);
        return NULL;
    }

    size_t output_pos = 0;
    size_t input_pos = 0;

    while (input_pos < input_len && input[input_pos] != '\0') {
        regmatch_t match;
        const char *current = input + input_pos;
        int ws_match = regexec(&whitespace_regex, current, 1, &match, 0);
        int us_match = regexec(&underscore_regex, current, 1, &match, 0);

        if (ws_match == 0 && match.rm_so == 0) {
            if (output_pos + 1 >= output_size) {
                size_t new_size = output_size * 2;
                char *temp = (char *)realloc(output, new_size);
                if (temp == NULL) {
                    free(output);
                    regfree(&whitespace_regex);
                    regfree(&underscore_regex);
                    return NULL;
                }
                output = temp;
                output_size = new_size;
            }
            output[output_pos++] = '_';
            input_pos += 1;
        } else if (us_match == 0 && match.rm_so == 0) {
            if (output_pos + 1 >= output_size) {
                size_t new_size = output_size * 2;
                char *temp = (char *)realloc(output, new_size);
                if (temp == NULL) {
                    free(output);
                    regfree(&whitespace_regex);
                    regfree(&underscore_regex);
                    return NULL;
                }
                output = temp;
                output_size = new_size;
            }
            output[output_pos++] = ' ';
            input_pos += 1;
        } else {
            if (output_pos + 1 >= output_size) {
                size_t new_size = output_size * 2;
                char *temp = (char *)realloc(output, new_size);
                if (temp == NULL) {
                    free(output);
                    regfree(&whitespace_regex);
                    regfree(&underscore_regex);
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
            regfree(&whitespace_regex);
            regfree(&underscore_regex);
            return NULL;
        }
        output = temp;
    }
    output[output_pos] = '\0';

    regfree(&whitespace_regex);
    regfree(&underscore_regex);

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
        fprintf(stderr, "Error: memory allocation or regex compilation failed\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", test_string);
    printf("Modified: %s\n", result);

    free(result);
    return EXIT_SUCCESS;
}