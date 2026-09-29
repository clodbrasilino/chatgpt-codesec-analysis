#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096
#define ERRBUF_SIZE 256

static void cleanup_tokens(char **tokens, size_t size);
static void print_regex_error(int ret, const regex_t *regex, const char *context);
char **split_string(const char *input, const char *pattern, size_t *count);
void free_tokens(char **tokens, size_t count);

static void cleanup_tokens(char **tokens, size_t size)
{
    if (tokens == NULL) {
        return;
    }
    for (size_t i = 0; i < size; i++) {
        free(tokens[i]);
    }
    free(tokens);
}

static void print_regex_error(int ret, const regex_t *regex, const char *context)
{
    char errbuf[ERRBUF_SIZE];

    memset(errbuf, 0, sizeof(errbuf));
    regerror(ret, regex, errbuf, sizeof(errbuf) - 1);
    errbuf[sizeof(errbuf) - 1] = '\0';
    fprintf(stderr, "%s: %s\n", context, errbuf);
}

char **split_string(const char *input, const char *pattern, size_t *count)
{
    regex_t regex;
    regmatch_t match;
    char **tokens = NULL;
    char **temp = NULL;
    size_t capacity = 8;
    size_t size = 0;
    const char *cursor;
    const char *end;
    size_t input_len;
    int ret;

    if (input == NULL || pattern == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;

    input_len = strnlen(input, MAX_INPUT_LEN);
    if (input_len >= MAX_INPUT_LEN) {
        fprintf(stderr, "input too long or not terminated\n");
        return NULL;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        print_regex_error(ret, &regex, "regcomp failed");
        return NULL;
    }

    if (capacity > SIZE_MAX / sizeof(char *)) {
        regfree(&regex);
        return NULL;
    }

    tokens = malloc(capacity * sizeof(char *));
    if (tokens == NULL) {
        regfree(&regex);
        return NULL;
    }

    cursor = input;
    end = input + input_len;

    while (cursor < end) {
        size_t token_len;

        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == 0 && match.rm_so == match.rm_eo) {
            regfree(&regex);
            cleanup_tokens(tokens, size);
            fprintf(stderr, "pattern matches empty string\n");
            return NULL;
        }

        if (ret == 0) {
            if (match.rm_so < 0 || match.rm_eo < match.rm_so ||
                (size_t)match.rm_eo > (size_t)(end - cursor)) {
                regfree(&regex);
                cleanup_tokens(tokens, size);
                return NULL;
            }
            token_len = (size_t)match.rm_so;
        } else if (ret == REG_NOMATCH) {
            token_len = (size_t)(end - cursor);
        } else {
            print_regex_error(ret, &regex, "regexec failed");
            regfree(&regex);
            cleanup_tokens(tokens, size);
            return NULL;
        }

        if (token_len > 0) {
            char *token;

            if (token_len > (size_t)(end - cursor) || token_len >= SIZE_MAX) {
                regfree(&regex);
                cleanup_tokens(tokens, size);
                return NULL;
            }

            token = malloc(token_len + 1);
            if (token == NULL) {
                regfree(&regex);
                cleanup_tokens(tokens, size);
                return NULL;
            }

            memcpy(token, cursor, token_len);
            token[token_len] = '\0';

            if (size == capacity) {
                if (capacity > SIZE_MAX / 2 ||
                    capacity * 2 > SIZE_MAX / sizeof(char *)) {
                    free(token);
                    regfree(&regex);
                    cleanup_tokens(tokens, size);
                    return NULL;
                }
                capacity *= 2;
                temp = realloc(tokens, capacity * sizeof(char *));
                if (temp == NULL) {
                    free(token);
                    regfree(&regex);
                    cleanup_tokens(tokens, size);
                    return NULL;
                }
                tokens = temp;
            }
            tokens[size] = token;
            size++;
        }

        if (ret == REG_NOMATCH) {
            break;
        }
        cursor += match.rm_eo;
    }

    regfree(&regex);
    *count = size;
    return tokens;
}

void free_tokens(char **tokens, size_t count)
{
    cleanup_tokens(tokens, count);
}

int main(void)
{
    const char *input = "apple,banana;cherry orange|grape,,melon";
    const char *pattern = "[,; |]+";
    size_t count = 0;
    char **tokens;

    tokens = split_string(input, pattern, &count);
    if (tokens == NULL) {
        fprintf(stderr, "failed to split string\n");
        return EXIT_FAILURE;
    }

    printf("Found %zu tokens:\n", count);
    for (size_t i = 0; i < count; i++) {
        printf("  [%zu] %s\n", i, tokens[i]);
    }

    free_tokens(tokens, count);
    return EXIT_SUCCESS;
}