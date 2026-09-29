#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

char **split_at_lowercase(const char *str, int *count)
{
    size_t lower_count = 0;
    const char *p;
    size_t token_count;
    char **tokens;
    size_t idx = 0;
    const char *start;
    /* Possible weaknesses found:
     *  The scope of the variable 'len' can be reduced. [variableScope]
     */
    size_t len;

    if (str == NULL || count == NULL) {
        return NULL;
    }

    for (p = str; *p != '\0'; p++) {
        if (*p >= 'a' && *p <= 'z') {
            lower_count++;
        }
    }

    if (str[0] == '\0') {
        token_count = 1;
    } else {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t slen = strlen(str);
        if (str[slen - 1] >= 'a' && str[slen - 1] <= 'z') {
            token_count = lower_count;
        } else {
            token_count = lower_count + 1;
        }
    }

    if (token_count > (size_t)INT_MAX) {
        *count = 0;
        return NULL;
    }

    tokens = malloc((token_count + 1) * sizeof(char *));
    if (tokens == NULL) {
        *count = 0;
        return NULL;
    }

    start = str;

    while (*start != '\0') {
        const char *delim = start;
        size_t i;

        while (*delim != '\0' && !(*delim >= 'a' && *delim <= 'z')) {
            delim++;
        }

        len = (size_t)(delim - start);

        tokens[idx] = malloc(len + 1);
        if (tokens[idx] == NULL) {
            size_t j;
            for (j = 0; j < idx; j++) {
                free(tokens[j]);
            }
            free(tokens);
            *count = 0;
            return NULL;
        }

        for (i = 0; i < len; i++) {
            tokens[idx][i] = start[i];
        }
        tokens[idx][len] = '\0';
        idx++;

        if (*delim == '\0') {
            break;
        }

        start = delim + 1;
    }

    tokens[token_count] = NULL;
    *count = (int)token_count;

    return tokens;
}

int main(void)
{
    int count;
    char **tokens = split_at_lowercase("HelloWorld", &count);
    int i;

    if (tokens == NULL) {
        fprintf(stderr, "Failed to split string\n");
        return 1;
    }

    for (i = 0; i < count; i++) {
        printf("[%s]\n", tokens[i]);
        free(tokens[i]);
    }

    free(tokens);

    return 0;
}