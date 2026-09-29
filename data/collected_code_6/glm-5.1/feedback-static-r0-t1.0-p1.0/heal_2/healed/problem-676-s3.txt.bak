#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_non_alphanumeric(const char *input) {
    if (input == NULL) {
        return malloc(1);
    }

    regex_t regex;
    int ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret != 0) {
        return malloc(1);
    }

    size_t input_len = strlen(input);
    if (input_len == 0) {
        regfree(&regex);
        char *empty = malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    size_t max_matches = 1;
    regmatch_t match;

    size_t result_size = input_len + 1;
    char *result = malloc(result_size);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t result_idx = 0;
    const char *str_ptr = input;

    while (1) {
        ret = regexec(&regex, str_ptr, max_matches, &match, 0);
        if (ret == REG_NOMATCH) {
            strcpy(&result[result_idx], str_ptr);
            result_idx += strlen(str_ptr);
            break;
        }

        if (ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        if (match.rm_so == -1) {
            break;
        }

        size_t copy_len = match.rm_so;

        memcpy(&result[result_idx], str_ptr, copy_len);
        result_idx += copy_len;

        str_ptr += match.rm_eo;

        if (*str_ptr == '\0') {
            break;
        }
    }

    result[result_idx] = '\0';

    char *final_result = realloc(result, result_idx + 1);
    if (final_result == NULL) {
        final_result = result;
    }

    regfree(&regex);

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

    const char *result3 = remove_non_alphanumeric(NULL);
    if (result3 == NULL) {
        printf("Handled NULL input safely\n");
    } else {
        printf("%s\n", result3);
        free((void *)result3);
    }

    return 0;
}