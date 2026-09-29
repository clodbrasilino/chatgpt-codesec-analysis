#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>

#define ERRBUF_SIZE 256

static char **split_string(const char *input, const char *pattern, size_t *count);
static void free_tokens(char **tokens, size_t count);

static char *duplicate_range(const char *start, size_t length)
{
    char *copy;

    if (start == NULL) {
        return NULL;
    }

    if (length == (size_t)-1 || length >= SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, start, length);
    copy[length] = '\0';
    return copy;
}

static char **append_token(char **tokens, size_t *count, char *token)
{
    char **resized;

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
    }
    free(tokens);
}

static void report_regex_error(int ret, const regex_t *regex, const char *context)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char errbuf[ERRBUF_SIZE];

    memset(errbuf, 0, sizeof(errbuf));
    regerror(ret, regex, errbuf, sizeof(errbuf) - 1);
    errbuf[sizeof(errbuf) - 1] = '\0';
    fprintf(stderr, "%s failed: %s\n", context, errbuf);
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