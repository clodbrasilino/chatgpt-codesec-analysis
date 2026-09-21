#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LENGTH 65536

static size_t safe_strlen(const char *s, size_t max_len)
{
    size_t len = 0;

    if (s == NULL)
    {
        return 0;
    }

    while (len < max_len && s[len] != '\0')
    {
        len++;
    }

    return len;
}

static void safe_copy(char *dest, size_t dest_size, const char *src)
{
    size_t i = 0;

    if (dest == NULL || dest_size == 0 || src == NULL)
    {
        return;
    }

    while (i + 1 < dest_size && src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }

    dest[i] = '\0';
}

char *remove_non_alnum(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *work;
    char *result;
    size_t len;
    size_t i = 0;
    size_t j = 0;
    int ret;

    if (input == NULL)
    {
        return NULL;
    }

    ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret != 0)
    {
        return NULL;
    }

    len = safe_strlen(input, MAX_INPUT_LENGTH);

    work = malloc(len + 1);
    if (work == NULL)
    {
        regfree(&regex);
        return NULL;
    }

    safe_copy(work, len + 1, input);

    result = malloc(len + 1);
    if (result == NULL)
    {
        free(work);
        regfree(&regex);
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
            free(work);
            regfree(&regex);
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

    free(work);
    regfree(&regex);

    return result;
}

int main(void)
{
    const char *input = "Hello, World! 123 @#$%^&*()";
    char *cleaned;

    cleaned = remove_non_alnum(input);
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