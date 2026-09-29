#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static void free_tokens(char **tokens, size_t count)
{
    if (tokens == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(tokens[i]);
    }
    free(tokens);
}

static char **split_at_uppercase(const char *input, size_t *count)
{
    regex_t re;
    regmatch_t match;
    char **tokens = NULL;
    size_t n = 0;
    const char *cursor = input;

    if (input == NULL || count == NULL) {
        return NULL;
    }

    if (regcomp(&re, "[A-Z]", REG_EXTENDED) != 0) {
        return NULL;
    }

    while (regexec(&re, cursor, 1, &match, 0) == 0) {
        size_t len = (size_t)match.rm_so;
        char *tok = malloc(len + 1);
        if (tok == NULL) {
            goto error;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(tok, cursor, len);
        tok[len] = '\0';

        char **tmp = realloc(tokens, (n + 1) * sizeof(*tokens));
        if (tmp == NULL) {
            free(tok);
            goto error;
        }
        tokens = tmp;
        tokens[n] = tok;
        n++;
        cursor += match.rm_eo;
    }

    {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(cursor);
        char *tok = malloc(len + 1);
        if (tok == NULL) {
            goto error;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(tok, cursor, len + 1);

        char **tmp = realloc(tokens, (n + 1) * sizeof(*tokens));
        if (tmp == NULL) {
            free(tok);
            goto error;
        }
        tokens = tmp;
        tokens[n] = tok;
        n++;
    }

    regfree(&re);
    *count = n;
    return tokens;

error:
    free_tokens(tokens, n);
    regfree(&re);
    return NULL;
}

int main(void)
{
    const char *text = "helloWorldThisIsRegexSplit";
    size_t count = 0;
    char **tokens = split_at_uppercase(text, &count);

    if (tokens == NULL) {
        if (fprintf(stderr, "Failed to split string\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        if (printf("Token %zu: \"%s\"\n", i, tokens[i]) < 0) {
            free_tokens(tokens, count);
            return EXIT_FAILURE;
        }
    }

    free_tokens(tokens, count);
    return EXIT_SUCCESS;
}