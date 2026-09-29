#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LENGTH 4096

static int append_segment(char *result, size_t *result_len, size_t result_cap,
                          const char *src, size_t copy_len)
{
    size_t available;

    if (result == NULL || result_len == NULL)
    {
        return -1;
    }

    if (copy_len > 0 && src == NULL)
    {
        return -1;
    }

    if (result_cap == 0)
    {
        return -1;
    }

    if (*result_len >= result_cap)
    {
        return -1;
    }

    available = result_cap - *result_len;

    if (copy_len >= available)
    {
        return -1;
    }

    if (copy_len > 0)
    {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + *result_len, src, copy_len);
        *result_len += copy_len;
    }

    result[*result_len] = '\0';

    return 0;
}

char *remove_lowercase_substrings(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *work;
    char *result;
    size_t result_len;
    size_t input_len;
    size_t result_cap;
    size_t offset;

    if (input == NULL)
    {
        return NULL;
    }

    if (regcomp(&regex, "[a-z]+", REG_EXTENDED) != 0)
    {
        return NULL;
    }

    work = strndup(input, MAX_INPUT_LENGTH);
    if (work == NULL)
    {
        regfree(&regex);
        return NULL;
    }

    input_len = strnlen(work, MAX_INPUT_LENGTH);
    result_cap = input_len + 1;

    result = calloc(result_cap, sizeof(char));
    if (result == NULL)
    {
        free(work);
        regfree(&regex);
        return NULL;
    }

    result_len = 0;
    offset = 0;

    while (offset < input_len)
    {
        int ret = regexec(&regex, work + offset, 1, &match, 0);

        if (ret == 0)
        {
            if (match.rm_so < 0 || match.rm_eo < match.rm_so ||
                (size_t)match.rm_eo > input_len - offset)
            {
                free(result);
                free(work);
                regfree(&regex);
                return NULL;
            }

            if (match.rm_eo == 0)
            {
                break;
            }

            if (match.rm_so > 0 &&
                append_segment(result, &result_len, result_cap,
                               work + offset, (size_t)match.rm_so) != 0)
            {
                free(result);
                free(work);
                regfree(&regex);
                return NULL;
            }

            offset += (size_t)match.rm_eo;
        }
        else if (ret == REG_NOMATCH)
        {
            if (append_segment(result, &result_len, result_cap,
                               work + offset, input_len - offset) != 0)
            {
                free(result);
                free(work);
                regfree(&regex);
                return NULL;
            }
            break;
        }
        else
        {
            free(result);
            free(work);
            regfree(&regex);
            return NULL;
        }
    }

    result[result_len] = '\0';
    free(work);
    regfree(&regex);

    return result;
}

int main(void)
{
    const char *input = "Hello World ABCdef GHIjkl MNO";
    char *result = remove_lowercase_substrings(input);

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