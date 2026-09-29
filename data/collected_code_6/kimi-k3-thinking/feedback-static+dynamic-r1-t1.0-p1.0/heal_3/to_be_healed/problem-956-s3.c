#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>

#define MAX_INPUT_LENGTH 1048576

void free_tokens(char **tokens, size_t count)
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

static int copy_substring(char *dest, size_t dest_size, const char *src, size_t copy_len)
{
    if (dest == NULL || src == NULL || dest_size == 0 || copy_len >= dest_size) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dest, src, copy_len);
    dest[copy_len] = '\0';

    return 0;
}

char **split_at_uppercase(const char *input, size_t *token_count)
{
    regex_t regex;
    regmatch_t match[1];
    char **tokens;
    char **resized;
    size_t capacity = 8;
    size_t count = 0;
    size_t start = 0;
    size_t offset = 0;
    size_t len;
    int status;

    if (input == NULL || token_count == NULL) {
        return NULL;
    }

    *token_count = 0;

    len = strnlen(input, MAX_INPUT_LENGTH);
    if (len == MAX_INPUT_LENGTH) {
        return NULL;
    }

    status = regcomp(&regex, "[[:upper:]]", REG_EXTENDED);
    if (status != 0) {
        return NULL;
    }

    tokens = malloc(capacity * sizeof(*tokens));
    if (tokens == NULL) {
        regfree(&regex);
        return NULL;
    }

    while (offset < len) {
        size_t pos;

        status = regexec(&regex, input + offset, 1, match, 0);

        if (status == REG_NOMATCH) {
            break;
        }

        if (status != 0 || match[0].rm_so < 0) {
            free_tokens(tokens, count);
            regfree(&regex);
            return NULL;
        }

        pos = offset + (size_t)match[0].rm_so;

        if (pos > start) {
            size_t tok_len = pos - start;

            if (count == capacity) {
                if (capacity > (SIZE_MAX / 2) / sizeof(*tokens)) {
                    free_tokens(tokens, count);
                    regfree(&regex);
                    return NULL;
                }
                resized = realloc(tokens, capacity * 2 * sizeof(*tokens));
                if (resized == NULL) {
                    free_tokens(tokens, count);
                    regfree(&regex);
                    return NULL;
                }
                tokens = resized;
                capacity *= 2;
            }

            tokens[count] = malloc(tok_len + 1);
            if (tokens[count] == NULL) {
                free_tokens(tokens, count);
                regfree(&regex);
                return NULL;
            }

            if (copy_substring(tokens[count], tok_len + 1, input + start, tok_len) != 0) {
                free_tokens(tokens, count + 1);
                regfree(&regex);
                return NULL;
            }

            count++;
        }

        start = pos;
        offset = pos + 1;
    }

    if (start < len) {
        size_t tok_len = len - start;

        if (count == capacity) {
            resized = realloc(tokens, (count + 1) * sizeof(*tokens));
            if (resized == NULL) {
                free_tokens(tokens, count);
                regfree(&regex);
                return NULL;
            }
            tokens = resized;
        }

        tokens[count] = malloc(tok_len + 1);
        if (tokens[count] == NULL) {
            free_tokens(tokens, count);
            regfree(&regex);
            return NULL;
        }

        if (copy_substring(tokens[count], tok_len + 1, input + start, tok_len) != 0) {
            free_tokens(tokens, count + 1);
            regfree(&regex);
            return NULL;
        }

        count++;
    }

    regfree(&regex);
    *token_count = count;
    return tokens;
}

int main(void)
{
    const char *input = "SplitThisStringAtUppercaseLetters";
    size_t count = 0;
    size_t i;
    char **tokens;

    tokens = split_at_uppercase(input, &count);

    if (tokens == NULL) {
        fprintf(stderr, "Error: failed to split the string\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        printf("%s\n", tokens[i]);
    }

    free_tokens(tokens, count);

    return EXIT_SUCCESS;
}