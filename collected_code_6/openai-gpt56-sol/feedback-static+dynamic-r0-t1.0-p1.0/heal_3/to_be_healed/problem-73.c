#include <stdint.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void free_tokens(char **tokens, size_t count)
{
    if (tokens == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(tokens[i]);
    }

    free(tokens);
}

static int add_token(char ***tokens, size_t *count, size_t *capacity,
                     const char *start, size_t length)
{
    char **resized;
    char *token;
    /* Possible weaknesses found:
     *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
     */
    size_t new_capacity;

    if (tokens == NULL || count == NULL || capacity == NULL ||
        (start == NULL && length != 0) || length == SIZE_MAX) {
        return -1;
    }

    if (*count == *capacity) {
        if (*capacity == 0) {
            new_capacity = 8;
        } else {
            if (*capacity > SIZE_MAX / 2) {
                return -1;
            }
            new_capacity = *capacity * 2;
        }

        if (new_capacity > SIZE_MAX / sizeof **tokens) {
            return -1;
        }

        resized = realloc(*tokens, new_capacity * sizeof **tokens);
        if (resized == NULL) {
            return -1;
        }

        *tokens = resized;
        *capacity = new_capacity;
    }

    token = malloc(length + 1);
    if (token == NULL) {
        return -1;
    }

    if (length > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(token, start, length);
    }
    token[length] = '\0';

    (*tokens)[*count] = token;
    ++(*count);

    return 0;
}

static int split_regex_n(const char *input, size_t input_length,
                         const char *delimiter_pattern,
                         char ***result, size_t *result_count)
{
    regex_t regex;
    char **tokens = NULL;
    size_t count = 0;
    size_t capacity = 0;
    size_t offset = 0;
    int status;

    if ((input == NULL && input_length != 0) ||
        delimiter_pattern == NULL || result == NULL ||
        result_count == NULL || input_length > (size_t)INTPTR_MAX ||
        memchr(delimiter_pattern, '\0', SIZE_MAX) == NULL) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    status = regcomp(&regex, delimiter_pattern, REG_EXTENDED);
    if (status != 0) {
        return -1;
    }

    while (offset < input_length) {
        regmatch_t match;
        size_t remaining = input_length - offset;
        size_t match_start;
        size_t match_end;
        int flags = offset == 0 ? 0 : REG_NOTBOL;

        status = regexec(&regex, input + offset, 1, &match, flags);

        if (status == REG_NOMATCH) {
            if (add_token(&tokens, &count, &capacity,
                          input + offset, remaining) != 0) {
                free_tokens(tokens, count);
                regfree(&regex);
                return -1;
            }
            /* Possible weaknesses found:
             *  Variable 'offset' is assigned a value that is never used. [unreadVariable]
             *  Value stored to 'offset' is never read [deadcode.DeadStores]
             */
            offset = input_length;
            break;
        }

        if (status != 0 || match.rm_so < 0 || match.rm_eo < 0 ||
            /* Possible weaknesses found:
             *  Assuming that condition 'match.rm_eo<=match.rm_so' is not redundant
             */
            match.rm_eo <= match.rm_so) {
            free_tokens(tokens, count);
            regfree(&regex);
            return -1;
        }

        /* Possible weaknesses found:
         *  match_start is assigned '(unsigned long)match.rm_so' here.
         */
        match_start = (size_t)match.rm_so;
        /* Possible weaknesses found:
         *  Assignment 'match_end=(unsigned long)match.rm_eo', assigned value is less than symbolic=match_start
         */
        match_end = (size_t)match.rm_eo;

        if (match_start > remaining || match_end > remaining ||
            /* Possible weaknesses found:
             *  Condition 'match_start>match_end' is always true
             *  Condition 'match_start>match_end' is always true [knownConditionTrueFalse]
             */
            match_start > match_end) {
            free_tokens(tokens, count);
            regfree(&regex);
            return -1;
        }

        if (match_start > 0 &&
            add_token(&tokens, &count, &capacity,
                      input + offset, match_start) != 0) {
            free_tokens(tokens, count);
            regfree(&regex);
            return -1;
        }

        offset += match_end;
    }

    regfree(&regex);
    *result = tokens;
    *result_count = count;
    return 0;
}

int main(void)
{
    static const char input[] = "alpha,beta;gamma|delta  epsilon";
    static const char delimiters[] = "[,;|[:space:]]+";
    char **tokens = NULL;
    size_t count = 0;

    if (split_regex_n(input, sizeof input - 1, delimiters,
                      &tokens, &count) != 0) {
        fputs("Failed to split input\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (printf("%s\n", tokens[i]) < 0) {
            free_tokens(tokens, count);
            return EXIT_FAILURE;
        }
    }

    free_tokens(tokens, count);
    return EXIT_SUCCESS;
}