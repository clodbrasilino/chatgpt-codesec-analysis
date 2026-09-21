#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_non_alnum(const char *input, size_t input_size)
{
    regex_t regex;
    regmatch_t match;
    char *result;
    char *work;
    size_t len;
    size_t i = 0;
    size_t j = 0;
    int ret;

    if (input == NULL || input_size == 0)
    {
        return NULL;
    }

    len = strnlen(input, input_size);

    work = malloc(len + 1);
    if (work == NULL)
    {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(work, input, len);
    work[len] = '\0';

    ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret != 0)
    {
        free(work);
        return NULL;
    }

    result = malloc(len + 1);
    if (result == NULL)
    {
        regfree(&regex);
        free(work);
        return NULL;
    }

    while (i < len)
    {
        size_t match_start;
        size_t match_end;

        ret = regexec(&regex, work + i, 1, &match, 0);
        if (ret == REG_NOMATCH)
        {
            while (i < len)
            {
                result[j++] = work[i++];
            }
            break;
        }
        else if (ret != 0)
        {
            free(result);
            regfree(&regex);
            free(work);
            return NULL;
        }

        match_start = i + (size_t)match.rm_so;
        match_end = i + (size_t)match.rm_eo;

        while (i < match_start)
        {
            result[j++] = work[i++];
        }
        i = match_end;
    }

    result[j] = '\0';
    regfree(&regex);
    free(work);

    return result;
}

int main(void)
{
    const char *input = "Hello, World! 123 @#$%^&*()";
    char *cleaned;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    cleaned = remove_non_alnum(input, strlen(input) + 1);
    if (cleaned == NULL)
    {
        fprintf(stderr, "Error: failed to process input string\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", input);
    printf("Cleaned:  %s\n", cleaned);

    free(cleaned);

    return EXIT_SUCCESS;
}