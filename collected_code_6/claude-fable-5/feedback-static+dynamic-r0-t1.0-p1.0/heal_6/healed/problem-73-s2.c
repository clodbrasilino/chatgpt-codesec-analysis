#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>

static char **split_string(const char *input, const char *pattern, size_t *count);
static void free_tokens(char **tokens, size_t count);

static char *duplicate_range(const char *start, size_t length)
{
    char *copy;

    if (start == NULL) {
        return NULL;
    }

    if (length >= SIZE_MAX - 1) {
        return NULL;
    }

    copy = calloc(length + 1, sizeof(char));
    if (copy == NULL) {
        return NULL;
    }

    if (length > 0) {
        size_t i;
        for (i = 0; i < length; i++) {
            copy[i] = start[i];
        }
    }
    copy[length] = '\0';
    return copy;
}

static char **append_token(char **tokens, size_t *count, char *token)
{
    char **resized;

    if (token == NULL || count == NULL) {
        free(token);
        free_tokens(tokens, count != NULL ? *count : 0);
        return NULL;
    }

    if (*count >= SIZE_MAX / sizeof(char *) - 1) {
        free(token);
        free_tokens(tokens, *count);
        return NULL;
    }

    resized = realloc(tokens, (*count + 1) * sizeof(char *));
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
        tokens[i] = NULL;
    }
    free(tokens);
}

static void report_regex_error(int ret, const regex_t *regex, const char *context)
{
    size_t needed;
    char *errbuf;

    needed = regerror(ret, regex, NULL, 0);
    if (needed == 0 || needed >= SIZE_MAX - 1) {
        fprintf(stderr, "%s failed: unknown regex error\n",
                context != NULL ? context : "regex");
        return;
    }

    errbuf = calloc(needed + 1, sizeof(char));
    if (errbuf == NULL) {
        fprintf(stderr, "%s failed: unable to allocate error buffer\n",
                context != NULL ? context : "regex");
        return;
    }

    regerror(ret, regex, errbuf, needed);
    errbuf[needed] = '\0';
    fprintf(stderr, "%s failed: %s\n", context != NULL ? context : "regex", errbuf);
    free(errbuf);
}

static char **split_string(const char *input, const char *pattern, size_t *count)
{
    regex_t regex;
    regmatch_t match;
    char **tokens = NULL;
    const char *cursor;
    const char *input_end;
    size_t input_len;
    int ret;

    if (input == NULL || pattern == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;

    input_len = strnlen(input, SIZE_MAX - 1);
    input_end = input + input_len;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        report_regex_error(ret, &regex, "regcomp");
        return NULL;
    }

    cursor = input;
    while (cursor < input_end && *cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            report_regex_error(ret, &regex, "regexec");
            free_tokens(tokens, *count);
            *count = 0;
            regfree(&regex);
            return NULL;
        }
        if (match.rm_eo == match.rm_so) {
            break;
        }
        if (match.rm_so < 0 || match.rm_eo < 0 ||
            (size_t)match.rm_so > (size_t)(input_end - cursor) ||
            (size_t)match.rm_eo > (size_t)(input_end - cursor)) {
            free_tokens(tokens, *count);
            *count = 0;
            regfree(&regex);
            return NULL;
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

    if (cursor < input_end && *cursor != '\0') {
        size_t remaining = (size_t)(input_end - cursor);
        char *token = duplicate_range(cursor, remaining);
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