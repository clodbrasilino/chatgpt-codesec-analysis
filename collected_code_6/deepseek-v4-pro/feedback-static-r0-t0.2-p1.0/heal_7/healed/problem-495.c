#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_lowercase_substrings(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = strnlen(input, 65536);
    
    regex_t regex;
    int reti = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (reti) {
        return NULL;
    }

    size_t max_output_size = input_len + 1;
    char *result = (char *)malloc(max_output_size);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t result_pos = 0;
    size_t search_pos = 0;
    regmatch_t match;

    while (search_pos < input_len && result_pos < max_output_size) {
        int match_result = regexec(&regex, input + search_pos, 1, &match, 0);
        
        if (match_result == REG_NOMATCH) {
            size_t remaining = input_len - search_pos;
            if (remaining > 0) {
                size_t space_left = max_output_size - result_pos;
                size_t bytes_to_copy = remaining < space_left ? remaining : space_left;
                if (bytes_to_copy > 0) {
                    memcpy(result + result_pos, input + search_pos, bytes_to_copy);
                    result_pos += bytes_to_copy;
                }
            }
            break;
        } else if (match_result == 0) {
            if (match.rm_so > 0) {
                size_t copy_size = (size_t)match.rm_so;
                size_t space_left = max_output_size - result_pos;
                if (copy_size > space_left) {
                    copy_size = space_left;
                }
                if (copy_size > 0) {
                    memcpy(result + result_pos, input + search_pos, copy_size);
                    result_pos += copy_size;
                }
            }
            search_pos += match.rm_eo;
            if (search_pos > input_len) {
                search_pos = input_len;
            }
        } else {
            free(result);
            regfree(&regex);
            return NULL;
        }
    }

    if (result_pos < max_output_size) {
        result[result_pos] = '\0';
    } else {
        result[max_output_size - 1] = '\0';
    }

    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_strings[] = {
        "HelloWorld",
        "abcDEFghiJKL",
        "NoLowercase",
        "123abc456def789",
        "MixedCaseABCdefGHI",
        "",
        "alllowercase",
        NULL
    };

    for (int i = 0; test_strings[i] != NULL; i++) {
        char *result = remove_lowercase_substrings(test_strings[i]);
        if (result != NULL) {
            printf("Input: '%s' -> Output: '%s'\n", test_strings[i], result);
            free(result);
        } else {
            printf("Input: '%s' -> Error processing\n", test_strings[i]);
        }
    }

    return 0;
}