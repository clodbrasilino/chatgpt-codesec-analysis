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

    size_t max_matches = strlen(input);
    if (max_matches == 0) {
        regfree(&regex);
        char *empty = malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    regmatch_t *matches = malloc(max_matches * sizeof(regmatch_t));
    if (matches == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t result_size = strlen(input) + 1;
    char *result = malloc(result_size);
    if (result == NULL) {
        regfree(&regex);
        free(matches);
        return NULL;
    }

    size_t result_idx = 0;
    size_t search_idx = 0;
    const char *str_ptr = input;

    while (1) {
        ret = regexec(&regex, str_ptr, max_matches, matches, 0);
        if (ret == REG_NOMATCH) {
            strcpy(&result[result_idx], str_ptr);
            result_idx += strlen(str_ptr);
            break;
        }

        if (ret != 0) {
            free(result);
            free(matches);
            regfree(&regex);
            return NULL;
        }

        if (matches[0].rm_so == -1) {
            break;
        }

        size_t match_len = matches[0].rm_eo - matches[0].rm_so;
        size_t copy_len = matches[0].rm_so;

        memcpy(&result[result_idx], str_ptr, copy_len);
        result_idx += copy_len;

        str_ptr += matches[0].rm_eo;
        search_idx += matches[0].rm_eo;

        if (search_idx >= strlen(input)) {
            break;
        }
    }

    result[result_idx] = '\0';

    char *final_result = realloc(result, result_idx + 1);
    if (final_result == NULL) {
        final_result = result;
    }

    regfree(&regex);
    free(matches);

    return final_result;
}

int main(void) {
    char *result1 = remove_non_alphanumeric("Hello, World! 123");
    if (result1 != NULL) {
        printf("%s\n", result1);
        free(result1);
    }

    char *result2 = remove_non_alphanumeric("Another@test*string");
    if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }

    char *result3 = remove_non_alphanumeric(NULL);
    if (result3 == NULL) {
        printf("Handled NULL input safely\n");
    }

    return 0;
}