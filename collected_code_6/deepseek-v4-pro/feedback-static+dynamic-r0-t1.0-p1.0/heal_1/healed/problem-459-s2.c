#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_uppercase_substrings(const char *input) {
    if (!input) return NULL;
    
    regex_t regex;
    regmatch_t match;
    const char *pattern = "[A-Z]+";
    size_t input_len = strlen(input);
    size_t buffer_size = input_len + 1;
    char *result = malloc(buffer_size);
    if (!result) return NULL;
    result[0] = '\0';
    
    int ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        free(result);
        return NULL;
    }
    
    const char *cursor = input;
    size_t result_len = 0;
    size_t remaining_input = input_len;
    
    while (remaining_input > 0) {
        if (regexec(&regex, cursor, 1, &match, 0) == 0 && match.rm_so != -1) {
            size_t prefix_len = match.rm_so;
            if (prefix_len > 0) {
                if (result_len + prefix_len >= buffer_size) {
                    buffer_size = result_len + prefix_len + 1;
                    char *temp = realloc(result, buffer_size);
                    if (!temp) {
                        free(result);
                        regfree(&regex);
                        return NULL;
                    }
                    result = temp;
                }
                memcpy(result + result_len, cursor, prefix_len);
                result_len += prefix_len;
            }
            size_t match_len = match.rm_eo - match.rm_so;
            cursor += match.rm_eo;
            remaining_input -= match.rm_eo;
        } else {
            if (result_len + remaining_input >= buffer_size) {
                buffer_size = result_len + remaining_input + 1;
                char *temp = realloc(result, buffer_size);
                if (!temp) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result = temp;
            }
            memcpy(result + result_len, cursor, remaining_input);
            result_len += remaining_input;
            break;
        }
    }
    
    result[result_len] = '\0';
    regfree(&regex);
    
    char *shrunk = realloc(result, result_len + 1);
    return shrunk ? shrunk : result;
}

int main(void) {
    const char *test_string = "abcDEFghIJKlmnoP";
    char *cleaned = remove_uppercase_substrings(test_string);
    
    if (cleaned) {
        printf("Original: %s\n", test_string);
        printf("Cleaned: %s\n", cleaned);
        free(cleaned);
    } else {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}