#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
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

int split_string(const char *input, const char *delimiter_regex,
                 char ***tokens_out, size_t *count_out)
{
    if (input == NULL || delimiter_regex == NULL ||
        tokens_out == NULL || count_out == NULL) {
        return -1;
    }

    *tokens_out = NULL;
    *count_out = 0;

    regex_t regex;
    int ret = regcomp(&regex, delimiter_regex, REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    const char *current = input;
    char **tokens = NULL;
    size_t count = 0;
    regmatch_t match;

    while (*current != '\0') {
        ret = regexec(&regex, current, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            regfree(&regex);
            free_tokens(tokens, count);
            return -1;
        }

        if (match.rm_so < 0 || match.rm_eo < match.rm_so) {
            regfree(&regex);
            free_tokens(tokens, count);
            return -1;
        }

        size_t token_len = (size_t)match.rm_so;
        if (token_len > 0) {
            char *token = malloc(token_len + 1);
            if (token == NULL) {
                regfree(&regex);
                free_tokens(tokens, count);
                return -1;
            }
            memcpy(token, current, token_len);
            token[token_len] = '\0';

            char **new_tokens = realloc(tokens, (count + 1) * sizeof(*tokens));
            if (new_tokens == NULL) {
                free(token);
                regfree(&regex);
                free_tokens(tokens, count);
                return -1;
            }
            tokens = new_tokens;
            tokens[count++] = token;
        }

        size_t match_len = (size_t)match.rm_eo;
        if (match_len == 0) {
            match_len = 1;
        }
        current += match_len;
    }

    if (*current != '\0') {
        size_t token_len = strlen(current);
        char *token = malloc(token_len + 1);
        if (token == NULL) {
            regfree(&regex);
            free_tokens(tokens, count);
            return -1;
        }
        memcpy(token, current, token_len + 1);

        char **new_tokens = realloc(tokens, (count + 1) * sizeof(*tokens));
        if (new_tokens == NULL) {
            free(token);
            regfree(&regex);
            free_tokens(tokens, count);
            return -1;
        }
        tokens = new_tokens;
        tokens[count++] = token;
    }

    regfree(&regex);
    *tokens_out = tokens;
    *count_out = count;
    return 0;
}

int main(void)
{
    const char *text = "apple,banana;cherry grape";
    const char *delimiters = "[,; ]+";
    char **tokens = NULL;
    size_t count = 0;

    if (split_string(text, delimiters, &tokens, &count) != 0) {
        fprintf(stderr, "Failed to split string\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", tokens[i]);
    }

    free_tokens(tokens, count);
    return EXIT_SUCCESS;
}