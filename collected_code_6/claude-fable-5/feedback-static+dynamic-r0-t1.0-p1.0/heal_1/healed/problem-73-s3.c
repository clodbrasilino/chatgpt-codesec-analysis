#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static void print_regex_error(int errcode, const regex_t *regex, const char *prefix)
{
    size_t needed = regerror(errcode, regex, NULL, 0);
    char *errbuf = malloc(needed);
    if (errbuf != NULL) {
        regerror(errcode, regex, errbuf, needed);
        fprintf(stderr, "%s: %s\n", prefix, errbuf);
        free(errbuf);
    } else {
        fprintf(stderr, "%s: unknown error\n", prefix);
    }
}

char **split_string(const char *input, const char *pattern, size_t *count)
{
    regex_t regex;
    regmatch_t match;
    char **tokens = NULL;
    char **temp = NULL;
    size_t capacity = 8;
    size_t size = 0;
    const char *cursor = input;
    size_t remaining;
    int ret;

    if (input == NULL || pattern == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;
    remaining = strlen(input);

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        print_regex_error(ret, &regex, "regcomp failed");
        return NULL;
    }

    tokens = malloc(capacity * sizeof(char *));
    if (tokens == NULL) {
        regfree(&regex);
        return NULL;
    }

    while (remaining > 0) {
        size_t token_len;

        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == 0 && match.rm_so == match.rm_eo) {
            regfree(&regex);
            for (size_t i = 0; i < size; i++) {
                free(tokens[i]);
            }
            free(tokens);
            fprintf(stderr, "pattern matches empty string\n");
            return NULL;
        }

        if (ret == 0) {
            if ((size_t)match.rm_eo > remaining || match.rm_so < 0) {
                regfree(&regex);
                for (size_t i = 0; i < size; i++) {
                    free(tokens[i]);
                }
                free(tokens);
                fprintf(stderr, "invalid match offsets\n");
                return NULL;
            }
            token_len = (size_t)match.rm_so;
        } else if (ret == REG_NOMATCH) {
            token_len = remaining;
        } else {
            print_regex_error(ret, &regex, "regexec failed");
            regfree(&regex);
            for (size_t i = 0; i < size; i++) {
                free(tokens[i]);
            }
            free(tokens);
            return NULL;
        }

        if (token_len > 0) {
            char *token = malloc(token_len + 1);
            if (token == NULL) {
                regfree(&regex);
                for (size_t i = 0; i < size; i++) {
                    free(tokens[i]);
                }
                free(tokens);
                return NULL;
            }
            memcpy(token, cursor, token_len);
            token[token_len] = '\0';

            if (size == capacity) {
                if (capacity > SIZE_MAX / 2 / sizeof(char *)) {
                    free(token);
                    regfree(&regex);
                    for (size_t i = 0; i < size; i++) {
                        free(tokens[i]);
                    }
                    free(tokens);
                    return NULL;
                }
                capacity *= 2;
                temp = realloc(tokens, capacity * sizeof(char *));
                if (temp == NULL) {
                    free(token);
                    regfree(&regex);
                    for (size_t i = 0; i < size; i++) {
                        free(tokens[i]);
                    }
                    free(tokens);
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
        remaining -= (size_t)match.rm_eo;
    }

    regfree(&regex);
    *count = size;
    return tokens;
}

void free_tokens(char **tokens, size_t count)
{
    if (tokens == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(tokens[i]);
    }
    free(tokens);
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