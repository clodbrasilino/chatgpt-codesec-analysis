#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

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
    size_t pos;
    size_t tok_len;
    int status;

    if (input == NULL || token_count == NULL) {
        return NULL;
    }

    *token_count = 0;

    status = regcomp(&regex, "[[:upper:]]", REG_EXTENDED);
    if (status != 0) {
        return NULL;
    }

    tokens = malloc(capacity * sizeof(*tokens));
    if (tokens == NULL) {
        regfree(&regex);
        return NULL;
    }

    len = strlen(input);

    while (offset < len) {
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
            tok_len = pos - start;

            if (count == capacity) {
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

            memcpy(tokens[count], input + start, tok_len);
            tokens[count][tok_len] = '\0';
            count++;
        }

        start = pos;
        offset = pos + 1;
    }

    if (start < len) {
        tok_len = len - start;

        if (count == capacity) {
            resized = realloc(tokens, (capacity + 1) * sizeof(*tokens));
            if (resized == NULL) {
                free_tokens(tokens, count);
                regfree(&regex);
                return NULL;
            }
            tokens = resized;
            capacity += 1;
        }

        tokens[count] = malloc(tok_len + 1);
        if (tokens[count] == NULL) {
            free_tokens(tokens, count);
            regfree(&regex);
            return NULL;
        }

        memcpy(tokens[count], input + start, tok_len);
        tokens[count][tok_len] = '\0';
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