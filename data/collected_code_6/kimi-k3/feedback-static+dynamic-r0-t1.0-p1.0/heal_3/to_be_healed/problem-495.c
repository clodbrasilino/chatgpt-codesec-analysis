#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int remove_lowercase_substrings(const char *input, size_t input_len, char **output)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    const char *end;
    char *result;
    size_t result_len;
    size_t remaining;
    int ret;

    if (input == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;

    result = malloc(input_len + 1);
    if (result == NULL) {
        return -1;
    }

    ret = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return -1;
    }

    cursor = input;
    end = input + input_len;
    result_len = 0;

    while (cursor < end && *cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);

        if (ret == REG_NOMATCH) {
            remaining = (size_t)(end - cursor);
            if (result_len + remaining > input_len) {
                regfree(&regex);
                free(result);
                return -1;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_len, cursor, remaining);
            result_len += remaining;
            break;
        }

        if (ret != 0) {
            regfree(&regex);
            free(result);
            return -1;
        }

        {
            size_t copy_len = (size_t)match.rm_so;
            if (result_len + copy_len > input_len) {
                regfree(&regex);
                free(result);
                return -1;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_len, cursor, copy_len);
            result_len += copy_len;
        }
        cursor += match.rm_eo;
    }

    result[result_len] = '\0';
    regfree(&regex);
    *output = result;

    return 0;
}

int main(void)
{
    const char *input = "HelloWorldABCdefGHIjklMNOP";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    char *output = NULL;

    if (remove_lowercase_substrings(input, input_len, &output) != 0) {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    printf("Input:  %s\n", input);
    printf("Output: %s\n", output);

    free(output);

    return EXIT_SUCCESS;
}