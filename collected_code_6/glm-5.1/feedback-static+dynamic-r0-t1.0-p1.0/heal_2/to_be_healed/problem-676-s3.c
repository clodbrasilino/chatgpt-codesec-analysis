#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

const char *remove_non_alphanumeric(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
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

    regmatch_t *matches = malloc(input_len * sizeof(regmatch_t));
    if (matches == NULL) {
        regfree(&regex);
        return NULL;
    }

    char *result = malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        free(matches);
        return NULL;
    }

    size_t result_idx = 0;
    const char *str_ptr = input;

    while (1) {
        ret = regexec(&regex, str_ptr, 1, matches, 0);
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

        size_t copy_len = matches[0].rm_so;

        memcpy(&result[result_idx], str_ptr, copy_len);
        result_idx += copy_len;

        str_ptr += matches[0].rm_eo;
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
    const char *result1 = remove_non_alphanumeric("Hello, World! 123");
    if (result1 != NULL) {
        printf("%s\n", result1);
        free((void *)result1);
    }

    const char *result2 = remove_non_alphanumeric("Another@test*string");
    if (result2 != NULL) {
        printf("%s\n", result2);
        free((void *)result2);
    }

    /* Possible weaknesses found:
     *  Calling function 'remove_non_alphanumeric' returns 0
     *  Assignment 'result3=remove_non_alphanumeric(NULL)', assigned value is 0
     */
    const char *result3 = remove_non_alphanumeric(NULL);
    /* Possible weaknesses found:
     *  Condition 'result3==NULL' is always true
     *  Condition 'result3==NULL' is always true [knownConditionTrueFalse]
     */
    if (result3 == NULL) {
        printf("Handled NULL input safely\n");
    }

    return 0;
}