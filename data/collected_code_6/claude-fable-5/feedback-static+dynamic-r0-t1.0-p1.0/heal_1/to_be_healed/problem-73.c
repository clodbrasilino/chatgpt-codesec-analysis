#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char **split_string(const char *input, const char *pattern, size_t *count);
void free_tokens(char **tokens, size_t count);

char **split_string(const char *input, const char *pattern, size_t *count)
{
    regex_t regex;
    regmatch_t match;
    char **tokens = NULL;
    char **temp = NULL;
    size_t n = 0;
    const char *cursor = input;
    int ret;

    if (input == NULL || pattern == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char errbuf[256];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "regcomp failed: %s\n", errbuf);
        return NULL;
    }

    while (*cursor != '\0') {
        size_t len;

        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == 0 && match.rm_so != match.rm_eo) {
            len = (size_t)match.rm_so;
        } else if (ret == 0 && match.rm_so == match.rm_eo) {
            break;
        } else {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            len = strlen(cursor);
        }

        if (len > 0) {
            char *token = malloc(len + 1);
            if (token == NULL) {
                regfree(&regex);
                free_tokens(tokens, n);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(token, cursor, len);
            token[len] = '\0';

            temp = realloc(tokens, (n + 1) * sizeof(char *));
            if (temp == NULL) {
                free(token);
                regfree(&regex);
                free_tokens(tokens, n);
                return NULL;
            }
            tokens = temp;
            tokens[n] = token;
            n++;
        }

        if (ret == 0) {
            cursor += match.rm_eo;
        } else {
            break;
        }
    }

    regfree(&regex);
    *count = n;
    return tokens;
}

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

int main(void)
{
    const char *text = "apple,banana;cherry  orange|grape";
    const char *pattern = "[,;| ]+";
    size_t count = 0;
    size_t i;
    char **tokens;

    tokens = split_string(text, pattern, &count);
    if (tokens == NULL && count == 0) {
        fprintf(stderr, "split_string failed or returned no tokens\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        if (printf("Token %zu: %s\n", i + 1, tokens[i]) < 0) {
            free_tokens(tokens, count);
            return EXIT_FAILURE;
        }
    }

    free_tokens(tokens, count);
    return EXIT_SUCCESS;
}