#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static char **split_string_regex(const char *input, const char *delim_pattern, size_t *count)
{
    regex_t regex;
    regmatch_t match;
    char **tokens = NULL;
    char **new_tokens = NULL;
    char *token = NULL;
    size_t used = 0;
    size_t capacity = 8;
    size_t token_len = 0;
    size_t advance = 0;
    size_t i = 0;
    const char *cursor = NULL;
    int status = 0;

    if (input == NULL || delim_pattern == NULL || count == NULL)
    {
        return NULL;
    }

    *count = 0;

    status = regcomp(&regex, delim_pattern, REG_EXTENDED);
    if (status != 0)
    {
        return NULL;
    }

    tokens = malloc(capacity * sizeof(*tokens));
    if (tokens == NULL)
    {
        regfree(&regex);
        return NULL;
    }

    cursor = input;

    while (*cursor != '\0')
    {
        status = regexec(&regex, cursor, 1, &match, 0);
        if (status == REG_NOMATCH)
        {
            break;
        }
        if (status != 0)
        {
            goto fail;
        }

        token_len = (size_t)match.rm_so;
        advance = (size_t)match.rm_eo;
        if (advance == 0)
        {
            advance = 1;
        }

        if (used == capacity)
        {
            capacity *= 2;
            new_tokens = realloc(tokens, capacity * sizeof(*new_tokens));
            if (new_tokens == NULL)
            {
                goto fail;
            }
            tokens = new_tokens;
        }

        token = malloc(token_len + 1);
        if (token == NULL)
        {
            goto fail;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(token, cursor, token_len);
        token[token_len] = '\0';
        tokens[used] = token;
        used++;

        cursor += advance;
    }

    if (*cursor != '\0')
    {
        if (used == capacity)
        {
            capacity += 1;
            new_tokens = realloc(tokens, capacity * sizeof(*new_tokens));
            if (new_tokens == NULL)
            {
                goto fail;
            }
            tokens = new_tokens;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        token_len = strlen(cursor);
        token = malloc(token_len + 1);
        if (token == NULL)
        {
            goto fail;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(token, cursor, token_len + 1);
        tokens[used] = token;
        used++;
    }

    regfree(&regex);
    *count = used;
    return tokens;

fail:
    for (i = 0; i < used; i++)
    {
        free(tokens[i]);
    }
    free(tokens);
    regfree(&regex);
    return NULL;
}

static void free_tokens(char **tokens, size_t count)
{
    size_t i = 0;

    if (tokens == NULL)
    {
        return;
    }

    for (i = 0; i < count; i++)
    {
        free(tokens[i]);
    }
    free(tokens);
}

int main(void)
{
    const char *input = "apple,banana;cherry|grape orange";
    const char *delim_pattern = "[,;| ]+";
    char **tokens = NULL;
    size_t count = 0;
    size_t i = 0;

    tokens = split_string_regex(input, delim_pattern, &count);
    if (tokens == NULL)
    {
        fprintf(stderr, "Error: failed to split the string\n");
        return EXIT_FAILURE;
    }

    printf("Input: \"%s\"\n", input);
    printf("Delimiter regex: \"%s\"\n", delim_pattern);
    printf("Tokens: %zu\n", count);

    for (i = 0; i < count; i++)
    {
        printf("  [%zu] \"%s\"\n", i, tokens[i]);
    }

    free_tokens(tokens, count);
    return EXIT_SUCCESS;
}