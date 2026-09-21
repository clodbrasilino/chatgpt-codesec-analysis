#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_whitespace(const char *input) {
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    char *result;
    size_t result_len;
    size_t input_len;
    size_t copy_len;
    size_t remaining;
    size_t available;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    input_len = strnlen(input, 1024);
    if (input_len == 1024 && input[input_len] != '\0') {
        return NULL;
    }

    result = malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[[:space:]]", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    cursor = input;
    result_len = 0;

    while (*cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            remaining = input_len - (size_t)(cursor - input);
            copy_len = strnlen(cursor, remaining);
            available = input_len - result_len;
            if (copy_len > available) {
                regfree(&regex);
                free(result);
                return NULL;
            }
            if (copy_len > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + result_len, cursor, copy_len);
            }
            result_len += copy_len;
            break;
        } else if (ret != 0) {
            regfree(&regex);
            free(result);
            return NULL;
        }

        if (match.rm_so < 0 || match.rm_eo < 0 || match.rm_eo < match.rm_so) {
            regfree(&regex);
            free(result);
            return NULL;
        }

        copy_len = (size_t)match.rm_so;
        available = input_len - result_len;
        if (copy_len > available) {
            regfree(&regex);
            free(result);
            return NULL;
        }
        if (copy_len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_len, cursor, copy_len);
        }
        result_len += copy_len;
        cursor += match.rm_eo;
    }

    result[result_len] = '\0';
    regfree(&regex);

    return result;
}

int main(void) {
    const char *test_string = "Hello World \t This is a test \n string";
    char *cleaned;

    cleaned = remove_whitespace(test_string);
    if (cleaned == NULL) {
        fprintf(stderr, "Error: failed to process string\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", test_string);
    printf("Cleaned:  %s\n", cleaned);

    free(cleaned);

    return EXIT_SUCCESS;
}