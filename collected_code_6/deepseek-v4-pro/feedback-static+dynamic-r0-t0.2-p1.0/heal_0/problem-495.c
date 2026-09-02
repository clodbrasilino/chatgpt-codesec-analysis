#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_lowercase_substrings(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int reti = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (reti) {
        return NULL;
    }

    size_t input_len = strlen(input);
    char *result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t result_pos = 0;
    size_t search_pos = 0;
    regmatch_t match;

    while (search_pos < input_len) {
        int match_result = regexec(&regex, input + search_pos, 1, &match, 0);
        
        if (match_result == REG_NOMATCH) {
            strcpy(result + result_pos, input + search_pos);
            result_pos += input_len - search_pos;
            break;
        } else if (match_result == 0) {
            if (match.rm_so > 0) {
                memcpy(result + result_pos, input + search_pos, match.rm_so);
                result_pos += match.rm_so;
            }
            search_pos += match.rm_eo;
        } else {
            free(result);
            regfree(&regex);
            return NULL;
        }
    }

    result[result_pos] = '\0';
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