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

    size_t max_result_size = input_len + 1;
    char *result = (char *)malloc(max_result_size);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t result_index = 0;
    regmatch_t match;
    const char *cursor = input;

    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        if (match.rm_so < 0) {
            break;
        }
        
        size_t match_start = (size_t)match.rm_so;
        size_t match_end = (size_t)match.rm_eo;

        if (match_start > input_len - (size_t)(cursor - input)) {
            match_start = input_len - (size_t)(cursor - input);
        }
        if (match_end > input_len - (size_t)(cursor - input)) {
            match_end = input_len - (size_t)(cursor - input);
        }

        if (match_start > 0) {
            size_t remaining_space = max_result_size - result_index;
            if (match_start > remaining_space) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            memcpy(result + result_index, cursor, match_start);
            result_index += match_start;
        }

        if (match_end <= match_start) {
            match_end = match_start + 1;
            if (match_end > input_len - (size_t)(cursor - input)) {
                break;
            }
        }
        cursor += match_end;
    }

    size_t remaining_len = input_len - (size_t)(cursor - input);
    if (remaining_len > 0) {
        size_t remaining_space = max_result_size - result_index;
        if (remaining_len > remaining_space) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        memcpy(result + result_index, cursor, remaining_len);
        result_index += remaining_len;
    }

    result[result_index] = '\0';
    regfree(&regex);

    char *shrunk = (char *)realloc(result, result_index + 1);
    return shrunk ? shrunk : result;
}

int main(void) {
    const char *test_string = "Hello, World! 123";
    char *cleaned = remove_non_alphanumeric(test_string);
    
    if (cleaned != NULL) {
        printf("Original: %s\n", test_string);
        printf("Cleaned:  %s\n", cleaned);
        free(cleaned);
    } else {
        printf("Error processing string\n");
    }

    return 0;
}