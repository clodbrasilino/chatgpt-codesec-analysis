#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_whitespace(const char *input, size_t input_len) {
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    char *result;
    size_t result_len;
    size_t copy_len;
    size_t remaining;
    int ret;

    if (input == NULL) {
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
    remaining = input_len;

    while (remaining > 0) {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            copy_len = remaining;
            if (result_len + copy_len > input_len) {
                regfree(&regex);
                free(result);
                return NULL;
            }
            memcpy(result + result_len, cursor, copy_len);
            result_len += copy_len;
            break;
        } else if (ret != 0) {
            regfree(&regex);
            free(result);
            return NULL;
        }

        copy_len = (size_t)match.rm_so;
        if (result_len + copy_len > input_len || copy_len > remaining) {
            regfree(&regex);
            free(result);
            return NULL;
        }
        if (copy_len > 0) {
            memcpy(result + result_len, cursor, copy_len);
            result_len += copy_len;
        }
        
        if ((size_t)match.rm_eo > remaining) {
            regfree(&regex);
            free(result);
            return NULL;
        }
        cursor += match.rm_eo;
        remaining -= (size_t)match.rm_eo;
    }

    result[result_len] = '\0';
    regfree(&regex);

    return result;
}

int main(void) {
    const char *test_string = "Hello World \t This is a test \n string";
    char *cleaned;
    size_t test_len;

    test_len = strlen(test_string);
    cleaned = remove_whitespace(test_string, test_len);
    if (cleaned == NULL) {
        fprintf(stderr, "Error: failed to process string\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", test_string);
    printf("Cleaned:  %s\n", cleaned);

    free(cleaned);

    return EXIT_SUCCESS;
}