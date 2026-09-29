#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_whitespace(const char *input, size_t max_len)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    char *result;
    size_t result_len;
    size_t input_len;
    size_t copy_len;
    size_t remaining;
    size_t buffer_size;
    int ret;

    if (input == NULL || max_len == 0) {
        return NULL;
    }

    ret = regcomp(&regex, "[[:space:]]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    input_len = strnlen(input, max_len);
    if (input_len == max_len && input[input_len] != '\0') {
        regfree(&regex);
        return NULL;
    }

    buffer_size = input_len + 1;
    result = malloc(buffer_size);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    cursor = input;
    result_len = 0;

    while (*cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            remaining = input_len - (size_t)(cursor - input);
            copy_len = strnlen(cursor, remaining);
            if (copy_len > buffer_size - result_len - 1) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            if (result_len + copy_len + 1 > buffer_size) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            if (result_len + copy_len > buffer_size - 1) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            memcpy(result + result_len, cursor, copy_len);
            result_len += copy_len;
            break;
        } else if (ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        copy_len = (size_t)match.rm_so;
        if (copy_len > buffer_size - result_len - 1) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        if (result_len + copy_len + 1 > buffer_size) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        if (result_len + copy_len > buffer_size - 1) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        memcpy(result + result_len, cursor, copy_len);
        result_len += copy_len;
        cursor += match.rm_eo;
    }

    result[result_len] = '\0';
    regfree(&regex);

    return result;
}

int main(void)
{
    const char *test_string = "Hello World \t This is a test \n string";
    char *cleaned;
    size_t test_len;

    test_len = strnlen(test_string, 1024);
    if (test_len == 1024) {
        fprintf(stderr, "Error: Invalid input string\n");
        return EXIT_FAILURE;
    }

    cleaned = remove_whitespace(test_string, test_len + 1);
    if (cleaned == NULL) {
        fprintf(stderr, "Error: Failed to process string\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", test_string);
    printf("Cleaned:  %s\n", cleaned);

    free(cleaned);

    return EXIT_SUCCESS;
}