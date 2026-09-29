#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static void free_tokens(char **tokens)
{
    if (tokens != NULL) {
        for (int i = 0; tokens[i] != NULL; ++i) {
            free(tokens[i]);
        }
        free(tokens);
    }
}

char **split_regex(const char *str, const char *pattern, int *count)
{
    if (str == NULL || pattern == NULL) {
        if (count != NULL) *count = -1;
        return NULL;
    }

    regex_t regex;
    int reg_status = regcomp(&regex, pattern, REG_EXTENDED);
    if (reg_status != 0) {
        if (count != NULL) *count = -1;
        return NULL;
    }

    char **tokens = NULL;
    int token_count = 0;
    size_t pos = 0;
    regmatch_t match;

    while (str[pos] != '\0') {
        int exec_status = regexec(&regex, str + pos, 1, &match, 0);

        if (exec_status == REG_NOMATCH) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t token_len = strlen(str + pos);
            char *token = strndup(str + pos, token_len);
            if (token == NULL) {
                regfree(&regex);
                free_tokens(tokens);
                if (count != NULL) *count = -1;
                return NULL;
            }
            char **new_tokens = realloc(tokens, (size_t)(token_count + 2) * sizeof(char *));
            if (new_tokens == NULL) {
                free(token);
                regfree(&regex);
                free_tokens(tokens);
                if (count != NULL) *count = -1;
                return NULL;
            }
            tokens = new_tokens;
            tokens[token_count] = token;
            tokens[token_count + 1] = NULL;
            token_count++;
            break;
        }

        if (exec_status != 0) {
            regfree(&regex);
            free_tokens(tokens);
            if (count != NULL) *count = -1;
            return NULL;
        }

        if (match.rm_so < 0 || match.rm_eo < match.rm_so) {
            regfree(&regex);
            free_tokens(tokens);
            if (count != NULL) *count = -1;
            return NULL;
        }

        size_t delim_start = pos + (size_t)match.rm_so;
        size_t delim_end = pos + (size_t)match.rm_eo;
        size_t token_len = delim_start - pos;

        if (match.rm_so == 0 && match.rm_eo == 0) {
            char *token = strndup(str + pos, 1);
            if (token == NULL) {
                regfree(&regex);
                free_tokens(tokens);
                if (count != NULL) *count = -1;
                return NULL;
            }
            char **new_tokens = realloc(tokens, (size_t)(token_count + 2) * sizeof(char *));
            if (new_tokens == NULL) {
                free(token);
                regfree(&regex);
                free_tokens(tokens);
                if (count != NULL) *count = -1;
                return NULL;
            }
            tokens = new_tokens;
            tokens[token_count] = token;
            tokens[token_count + 1] = NULL;
            token_count++;
            pos++;
        } else {
            char *token = strndup(str + pos, token_len);
            if (token == NULL) {
                regfree(&regex);
                free_tokens(tokens);
                if (count != NULL) *count = -1;
                return NULL;
            }
            char **new_tokens = realloc(tokens, (size_t)(token_count + 2) * sizeof(char *));
            if (new_tokens == NULL) {
                free(token);
                regfree(&regex);
                free_tokens(tokens);
                if (count != NULL) *count = -1;
                return NULL;
            }
            tokens = new_tokens;
            tokens[token_count] = token;
            tokens[token_count + 1] = NULL;
            token_count++;
            pos = delim_end;
        }
    }

    if (tokens == NULL) {
        tokens = malloc(sizeof(char *));
        if (tokens == NULL) {
            regfree(&regex);
            if (count != NULL) *count = -1;
            return NULL;
        }
        tokens[0] = NULL;
    }

    regfree(&regex);
    if (count != NULL) *count = token_count;
    return tokens;
}

int main(void)
{
    const char *text = "one, two; three:four";
    const char *pattern = "[,;: ]+";
    int count = 0;
    char **tokens = split_regex(text, pattern, &count);

    if (tokens == NULL) {
        fprintf(stderr, "split failed\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < count; ++i) {
        printf("%s\n", tokens[i]);
    }

    free_tokens(tokens);
    return EXIT_SUCCESS;
}