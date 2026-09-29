#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char **split_at_uppercase(const char *input, size_t *count)
{
    regex_t regex;
    regmatch_t match;
    char **result = NULL;
    char **temp = NULL;
    size_t capacity = 8;
    size_t n = 0;
    const char *cursor = input;
    int rc;

    if (input == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;

    rc = regcomp(&regex, "[A-Z][^A-Z]*|^[^A-Z]+", REG_EXTENDED);
    if (rc != 0) {
        return NULL;
    }

    result = malloc(capacity * sizeof(char *));
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    while (*cursor != '\0') {
        rc = regexec(&regex, cursor, 1, &match, 0);
        if (rc != 0) {
            break;
        }

        if (match.rm_so == match.rm_eo) {
            break;
        }

        size_t len = (size_t)(match.rm_eo - match.rm_so);
        char *token = malloc(len + 1);
        if (token == NULL) {
            for (size_t i = 0; i < n; i++) {
                free(result[i]);
            }
            free(result);
            regfree(&regex);
            return NULL;
        }

        memcpy(token, cursor + match.rm_so, len);
        token[len] = '\0';

        if (n >= capacity) {
            capacity *= 2;
            temp = realloc(result, capacity * sizeof(char *));
            if (temp == NULL) {
                free(token);
                for (size_t i = 0; i < n; i++) {
                    free(result[i]);
                }
                free(result);
                regfree(&regex);
                return NULL;
            }
            result = temp;
        }

        result[n] = token;
        n++;
        cursor += match.rm_eo;
    }

    regfree(&regex);
    *count = n;
    return result;
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
    const char *text = "helloWorldThisIsATestString";
    size_t count = 0;
    char **tokens = split_at_uppercase(text, &count);

    if (tokens == NULL) {
        fprintf(stderr, "Failed to split string\n");
        return EXIT_FAILURE;
    }

    printf("Input: %s\n", text);
    for (size_t i = 0; i < count; i++) {
        printf("Token %zu: %s\n", i, tokens[i]);
    }

    free_tokens(tokens, count);
    return EXIT_SUCCESS;
}