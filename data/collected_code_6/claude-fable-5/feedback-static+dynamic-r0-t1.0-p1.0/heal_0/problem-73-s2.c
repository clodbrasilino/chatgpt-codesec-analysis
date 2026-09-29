#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static char **split_string(const char *input, const char *pattern, size_t *count);
static void free_tokens(char **tokens, size_t count);

static char *duplicate_range(const char *start, size_t length)
{
    char *copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, start, length);
    copy[length] = '\0';
    return copy;
}

static char **append_token(char **tokens, size_t *count, char *token)
{
    char **resized = realloc(tokens, (*count + 1) * sizeof(char *));
    if (resized == NULL) {
        free(token);
        free_tokens(tokens, *count);
        return NULL;
    }
    resized[*count] = token;
    (*count)++;
    return resized;
}

static void free_tokens(char **tokens, size_t count)
{
    size_t i;
    if (tokens == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        free(tokens[i]);
    }
    free(tokens);
}

static char **split_string(const char *input, const char *pattern, size_t *count)
{
    regex_t regex;
    regmatch_t match;
    char **tokens = NULL;
    const char *cursor;
    int ret;

    if (input == NULL || pattern == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        char errbuf[256];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "regcomp failed: %s\n", errbuf);
        return NULL;
    }

    cursor = input;
    while (*cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            char errbuf[256];
            regerror(ret, &regex, errbuf, sizeof(errbuf));
            fprintf(stderr, "regexec failed: %s\n", errbuf);
            free_tokens(tokens, *count);
            *count = 0;
            regfree(&regex);
            return NULL;
        }
        if (match.rm_eo == match.rm_so) {
            break;
        }
        if (match.rm_so > 0) {
            char *token = duplicate_range(cursor, (size_t)match.rm_so);
            if (token == NULL) {
                free_tokens(tokens, *count);
                *count = 0;
                regfree(&regex);
                return NULL;
            }
            tokens = append_token(tokens, count, token);
            if (tokens == NULL) {
                *count = 0;
                regfree(&regex);
                return NULL;
            }
        }
        cursor += match.rm_eo;
    }

    if (*cursor != '\0') {
        char *token = duplicate_range(cursor, strlen(cursor));
        if (token == NULL) {
            free_tokens(tokens, *count);
            *count = 0;
            regfree(&regex);
            return NULL;
        }
        tokens = append_token(tokens, count, token);
        if (tokens == NULL) {
            *count = 0;
            regfree(&regex);
            return NULL;
        }
    }

    regfree(&regex);
    return tokens;
}

int main(void)
{
    const char *input = "apple,banana;cherry orange|grape,,melon";
    const char *pattern = "[,;| ]+";
    size_t count = 0;
    size_t i;
    char **tokens;

    tokens = split_string(input, pattern, &count);
    if (tokens == NULL && count == 0) {
        fprintf(stderr, "Failed to split string or no tokens found\n");
        return EXIT_FAILURE;
    }

    printf("Input: %s\n", input);
    printf("Tokens (%zu):\n", count);
    for (i = 0; i < count; i++) {
        printf("  [%zu] %s\n", i, tokens[i]);
    }

    free_tokens(tokens, count);
    return EXIT_SUCCESS;
}