#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_non_alphanumeric(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t input_len = strlen(input);
    if (input_len >= SIZE_MAX - 1) {
        regfree(&regex);
        return NULL;
    }

    char *result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t result_index = 0;
    regmatch_t match;
    const char *cursor = input;
    const char *input_end = input + input_len;

    while (cursor < input_end && regexec(&regex, cursor, 1, &match, 0) == 0) {
        size_t match_start = (size_t)match.rm_so;
        size_t match_end = (size_t)match.rm_eo;
        
        if (match_start > 0) {
            size_t copy_len = match_start;
            if (result_index + copy_len > input_len) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            memcpy(result + result_index, cursor, copy_len);
            result_index += copy_len;
        }
        
        cursor += match_end;
        if (cursor > input_end) {
            cursor = input_end;
            break;
        }
    }

    if (cursor < input_end) {
        size_t remaining_len = (size_t)(input_end - cursor);
        if (result_index + remaining_len > input_len) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        memcpy(result + result_index, cursor, remaining_len);
        result_index += remaining_len;
    }

    result[result_index] = '\0';
    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_string = "Hello, World! 123...";
    char *cleaned = remove_non_alphanumeric(test_string);
    
    if (cleaned != NULL) {
        printf("%s\n", cleaned);
        free(cleaned);
    }

    return 0;
}