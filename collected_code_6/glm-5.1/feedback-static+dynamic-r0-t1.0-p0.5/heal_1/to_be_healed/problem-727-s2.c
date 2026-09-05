#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_non_alnum(const char *input) {
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
        char *empty_result = malloc(1);
        if (empty_result == NULL) {
            return NULL;
        }
        empty_result[0] = '\0';
        return empty_result;
    }

    size_t max_matches = input_len;
    regmatch_t *matches = malloc(max_matches * sizeof(regmatch_t));
    if (matches == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t result_len = 0;
    size_t result_capacity = input_len + 1;
    char *result = malloc(result_capacity);
    if (result == NULL) {
        free(matches);
        regfree(&regex);
        return NULL;
    }

    const char *cursor = input;
    size_t offset = 0;

    while (offset < input_len) {
        ret = regexec(&regex, cursor, 1, matches, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining_len = input_len - offset;
            if (result_len + remaining_len >= result_capacity) {
                result_capacity = result_len + remaining_len + 1;
                char *temp = realloc(result, result_capacity);
                if (temp == NULL) {
                    free(result);
                    free(matches);
                    regfree(&regex);
                    return NULL;
                }
                result = temp;
            }
            memcpy(result + result_len, cursor, remaining_len);
            result_len += remaining_len;
            break;
        } else if (ret != 0) {
            free(result);
            free(matches);
            regfree(&regex);
            return NULL;
        }

        if (matches[0].rm_so > 0) {
            size_t copy_len = matches[0].rm_so;
            if (result_len + copy_len >= result_capacity) {
                result_capacity = (result_len + copy_len) * 2;
                char *temp = realloc(result, result_capacity);
                if (temp == NULL) {
                    free(result);
                    free(matches);
                    regfree(&regex);
                    return NULL;
                }
                result = temp;
            }
            memcpy(result + result_len, cursor, copy_len);
            result_len += copy_len;
        }

        if (matches[0].rm_eo == 0) {
            cursor++;
            offset++;
        } else {
            cursor += matches[0].rm_eo;
            offset += matches[0].rm_eo;
        }
    }

    result[result_len] = '\0';

    char *final_result = realloc(result, result_len + 1);
    if (final_result == NULL) {
        free(result);
        free(matches);
        regfree(&regex);
        return NULL;
    }

    free(matches);
    regfree(&regex);

    return final_result;
}

int main(void) {
    char *result1 = remove_non_alnum("Hello, World! 123");
    if (result1 != NULL) {
        printf("%s\n", result1);
        free(result1);
    }

    char *result2 = remove_non_alnum("___test___");
    if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }

    char *result3 = remove_non_alnum("");
    if (result3 != NULL) {
        printf("%s\n", result3);
        free(result3);
    }

    /* Possible weaknesses found:
     *  Assignment 'result4=remove_non_alnum(NULL)', assigned value is 0
     *  Calling function 'remove_non_alnum' returns 0
     *  Variable 'result4' can be declared as pointer to const [constVariablePointer]
     */
    char *result4 = remove_non_alnum(NULL);
    /* Possible weaknesses found:
     *  Condition 'result4==NULL' is always true [knownConditionTrueFalse]
     *  Condition 'result4==NULL' is always true
     */
    if (result4 == NULL) {
        printf("NULL\n");
    }

    return 0;
}