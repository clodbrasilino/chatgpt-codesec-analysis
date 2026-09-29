#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <errno.h>
#include <stdint.h>

char *remove_lowercase_substrings(const char *input, size_t max_len)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    const char *end;
    char *result;
    size_t result_len;
    size_t input_len;
    size_t copy_len;
    size_t remaining;
    size_t available;
    int ret;

    if (input == NULL || max_len == 0) {
        return NULL;
    }

    input_len = strnlen(input, max_len);
    if (input_len == max_len && input[input_len] != '\0') {
        return NULL;
    }

    ret = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    if (input_len == SIZE_MAX) {
        regfree(&regex);
        return NULL;
    }

    result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    cursor = input;
    end = input + input_len;
    result_len = 0;

    while (cursor < end && *cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            remaining = (size_t)(end - cursor);
            copy_len = strnlen(cursor, remaining);
            
            available = input_len - result_len;
            if (copy_len > available) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            
            if (copy_len > 0) {
                memcpy(result + result_len, cursor, copy_len);
                result_len += copy_len;
            }
            break;
        } else if (ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        if (match.rm_so < 0 || match.rm_eo < 0 || 
            match.rm_so > match.rm_eo ||
            (size_t)match.rm_eo > (size_t)(end - cursor)) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        copy_len = (size_t)match.rm_so;
        
        available = input_len - result_len;
        if (copy_len > available) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        
        if (copy_len > 0) {
            memcpy(result + result_len, cursor, copy_len);
            result_len += copy_len;
        }
        cursor += match.rm_eo;
    }

    result[result_len] = '\0';
    regfree(&regex);
    return result;
}

int main(void)
{
    const char *test_string = "HelloWorldTESTString123abcXYZ";
    char *processed;
    size_t max_input_len = 1024;

    processed = remove_lowercase_substrings(test_string, max_input_len);
    if (processed == NULL) {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", test_string);
    printf("Processed: %s\n", processed);

    free(processed);
    return EXIT_SUCCESS;
}