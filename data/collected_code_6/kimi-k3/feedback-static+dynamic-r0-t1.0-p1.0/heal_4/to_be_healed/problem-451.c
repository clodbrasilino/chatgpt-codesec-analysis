#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <errno.h>

char *remove_whitespace(const char *input, size_t input_len)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    const char *input_end;
    char *result;
    size_t result_len;
    size_t copy_len;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[[:space:]]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    result = malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    cursor = input;
    input_end = input + input_len;
    result_len = 0;

    while (cursor < input_end && *cursor != '\0') {
        size_t remaining = (size_t)(input_end - cursor);
        
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            copy_len = remaining;
            if (copy_len > input_len - result_len) {
                copy_len = input_len - result_len;
            }
            if (copy_len > 0 && result_len + copy_len <= input_len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + result_len, cursor, copy_len);
                result_len += copy_len;
            }
            break;
        } else if (ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        copy_len = (size_t)match.rm_so;
        if (copy_len > remaining) {
            copy_len = remaining;
        }
        if (copy_len > input_len - result_len) {
            copy_len = input_len - result_len;
        }
        
        if (copy_len > 0 && result_len + copy_len <= input_len) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_len, cursor, copy_len);
            result_len += copy_len;
        }
        
        if ((size_t)match.rm_eo > remaining) {
            break;
        }
        cursor += match.rm_eo;
    }

    result[result_len] = '\0';
    regfree(&regex);

    return result;
}

int main(void)
{
    const char *test_string = "Hello World \t This is a test \n string";
    size_t test_len;
    char *cleaned;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    test_len = strlen(test_string);
    
    cleaned = remove_whitespace(test_string, test_len);
    if (cleaned == NULL) {
        fprintf(stderr, "Error: Failed to process string\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", test_string);
    printf("Cleaned:  %s\n", cleaned);

    free(cleaned);

    return EXIT_SUCCESS;
}