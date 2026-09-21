#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
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

static int append_token(char ***tokens, size_t *n, const char *start, size_t len)
{
    if (tokens == NULL || n == NULL || start == NULL) {
        return -1;
    }
    if (len >= SIZE_MAX) {
        return -1;
    }

    char *tok = malloc(len + 1);
    if (tok == NULL) {
        return -1;
    }
    if (len > 0) {
        memcpy(tok, start, len);
    }
    tok[len] = '\0';

    if (*n >= SIZE_MAX / sizeof(**tokens) - 1) {
        free(tok);
        return -1;
    }

    char **tmp = realloc(*tokens, (*n + 1) * sizeof(**tokens));
    if (tmp == NULL) {
        free(tok);
        return -1;
    }
    *tokens = tmp;
    (*tokens)[*n] = tok;
    (*n)++;
    return 0;
}

static char **split_at_uppercase(const char *input, size_t *count)
{
    regex_t re;
    regmatch_t match;
    char **tokens = NULL;
    size_t n = 0;
    const char *cursor;
    const char *end;

    if (input == NULL || count == NULL) {
        return NULL;
    }

    cursor = input;
    end = input + strlen(input);

    if (regcomp(&re, "[A-Z]", REG_EXTENDED) != 0) {
        return NULL;
    }

    while (regexec(&re, cursor, 1, &match, 0) == 0) {
        if (match.rm_so < 0 || match.rm_eo < match.rm_so) {
            goto error;
        }

        size_t len = (size_t)match.rm_so;
        if (len > (size_t)(end - cursor)) {
            goto error;
        }

        if (append_token(&tokens, &n, cursor, len) != 0) {
            goto error;
        }

        if ((size_t)match.rm_eo > (size_t)(end - cursor)) {
            goto error;
        }
        cursor += match.rm_eo;
    }

    {
        size_t len = (size_t)(end - cursor);
        if (append_token(&tokens, &n, cursor, len) != 0) {
            goto error;
        }
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