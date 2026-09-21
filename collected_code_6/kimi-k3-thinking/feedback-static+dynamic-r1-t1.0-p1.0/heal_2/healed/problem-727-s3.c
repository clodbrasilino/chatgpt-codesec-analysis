#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>

char *remove_non_alnum(const char *input, size_t input_size)
{
    regex_t regex;
    regmatch_t match;
    char *result;
    char *work;
    size_t len;
    size_t work_capacity;
    size_t i = 0;
    size_t j = 0;
    size_t k;
    int ret;

    if (input == NULL || input_size == 0)
    {
        return NULL;
    }

    len = strnlen(input, input_size);

    if (len == SIZE_MAX)
    {
        return NULL;
    }

    work_capacity = len + 1;

    work = malloc(work_capacity);
    if (work == NULL)
    {
        return NULL;
    }

    for (k = 0; k < len && k < work_capacity - 1; k++)
    {
        work[k] = input[k];
    }
    work[k] = '\0';

    ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret != 0)
    {
        free(work);
        return NULL;
    }

    result = malloc(work_capacity);
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
            while (i < len && j < work_capacity - 1)
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

        if (match.rm_so < 0 || match.rm_eo < 0)
        {
            free(result);
            regfree(&regex);
            free(work);
            return NULL;
        }

        match_start = i + (size_t)match.rm_so;
        match_end = i + (size_t)match.rm_eo;

        if (match_start > len || match_end > len || match_end < match_start)
        {
            free(result);
            regfree(&regex);
            free(work);
            return NULL;
        }

        while (i < match_start && j < work_capacity - 1)
        {
            result[j++] = work[i++];
        }

        i = (match_end > i) ? match_end : i + 1;
    }

    result[j] = '\0';
    regfree(&regex);
    free(work);

    return result;
}

int main(void)
{
    static const char input[] = "Hello, World! 123 @#$%^&*()";
    char *cleaned;

    cleaned = remove_non_alnum(input, sizeof(input));
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