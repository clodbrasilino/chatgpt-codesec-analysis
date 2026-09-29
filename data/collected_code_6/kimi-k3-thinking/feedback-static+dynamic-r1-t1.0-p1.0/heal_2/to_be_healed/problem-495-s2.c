#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 65536

char *remove_lowercase_substrings(const char *input, size_t max_len)
{
    regex_t regex;
    regmatch_t match;
    char *result;
    size_t result_len;
    size_t input_len;
    size_t offset;
    size_t copy_len;
    int ret;

    if (input == NULL || max_len == 0)
    {
        return NULL;
    }

    input_len = strnlen(input, max_len);

    ret = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (ret != 0)
    {
        return NULL;
    }

    result = malloc(input_len + 1);
    if (result == NULL)
    {
        regfree(&regex);
        return NULL;
    }

    result_len = 0;
    offset = 0;

    while (offset < input_len)
    {
        ret = regexec(&regex, input + offset, 1, &match, 0);

        if (ret == 0)
        {
            if (match.rm_so < 0 || match.rm_eo < 0 || match.rm_eo < match.rm_so)
            {
                free(result);
                regfree(&regex);
                return NULL;
            }

            if (match.rm_so > 0)
            {
                copy_len = (size_t)match.rm_so;
                if (copy_len > input_len - result_len)
                {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + result_len, input + offset, copy_len);
                result_len += copy_len;
            }

            if (match.rm_eo == 0)
            {
                break;
            }

            offset += (size_t)match.rm_eo;
        }
        else if (ret == REG_NOMATCH)
        {
            copy_len = input_len - offset;
            if (copy_len > input_len - result_len)
            {
                free(result);
                regfree(&regex);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_len, input + offset, copy_len);
            result_len += copy_len;
            break;
        }
        else
        {
            free(result);
            regfree(&regex);
            return NULL;
        }
    }

    result[result_len] = '\0';
    regfree(&regex);

    return result;
}

int main(void)
{
    const char *input = "Hello World ABCdef GHIjkl MNO";
    char *result = remove_lowercase_substrings(input, MAX_INPUT_LEN);

    if (result == NULL)
    {
        fprintf(stderr, "Error: failed to process the input string\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", input);
    printf("Result:   %s\n", result);

    free(result);

    return EXIT_SUCCESS;
}