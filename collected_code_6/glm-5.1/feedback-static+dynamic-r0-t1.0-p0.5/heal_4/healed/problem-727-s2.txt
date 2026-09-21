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

    size_t result_capacity = input_len + 1;
    char *result = malloc(result_capacity);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t result_len = 0;
    const char *cursor = input;
    size_t offset = 0;
    regmatch_t match;

    while (offset < input_len) {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining_len = input_len - offset;
            if (result_len + remaining_len + 1 > result_capacity) {
                result_capacity = result_len + remaining_len + 1;
                char *temp = realloc(result, result_capacity);
                if (temp == NULL) {
                    free(result);
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
            regfree(&regex);
            return NULL;
        }

        if (match.rm_so > 0) {
            size_t copy_len = match.rm_so;
            if (result_len + copy_len + 1 > result_capacity) {
                result_capacity = (result_len + copy_len + 1) * 2;
                char *temp = realloc(result, result_capacity);
                if (temp == NULL) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result = temp;
            }
            memcpy(result + result_len, cursor, copy_len);
            result_len += copy_len;
        }

        if (match.rm_eo == 0) {
            cursor++;
            offset++;
        } else {
            cursor += match.rm_eo;
            offset += match.rm_eo;
        }
    }

    result[result_len] = '\0';

    regfree(&regex);

    if (result_len + 1 < result_capacity) {
        char *final_result = realloc(result, result_len + 1);
        if (final_result != NULL) {
            return final_result;
        }
    }

    return result;
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

    const char *result4 = remove_non_alnum(NULL);
    if (result4 == NULL) {
        printf("NULL\n");
    } else {
        free((void *)result4);
    }

    return 0;
}