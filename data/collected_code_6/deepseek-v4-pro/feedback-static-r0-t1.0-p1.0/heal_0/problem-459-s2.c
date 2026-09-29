#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_uppercase_substrings(const char *input) {
    regex_t regex;
    regmatch_t match;
    const char *pattern = "[A-Z]+";
    size_t input_len = strlen(input);
    char *result = malloc(input_len + 1);
    if (!result) return NULL;
    result[0] = '\0';
    
    int ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        free(result);
        return NULL;
    }
    
    const char *cursor = input;
    size_t result_len = 0;
    
    while (cursor <= input + input_len) {
        if (regexec(&regex, cursor, 1, &match, 0) == 0 && match.rm_so != -1) {
            size_t prefix_len = match.rm_so;
            if (prefix_len > 0) {
                memcpy(result + result_len, cursor, prefix_len);
                result_len += prefix_len;
            }
            cursor += match.rm_eo;
        } else {
            size_t remaining = input + input_len - cursor;
            if (remaining > 0) {
                memcpy(result + result_len, cursor, remaining);
                result_len += remaining;
            }
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