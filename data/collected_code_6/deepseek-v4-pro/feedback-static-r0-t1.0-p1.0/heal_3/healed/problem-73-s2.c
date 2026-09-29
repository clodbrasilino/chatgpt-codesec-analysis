#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static char **split_string(const char *input, const char *delimiters, int *count) {
    if (!input || !delimiters || !count) {
        return NULL;
    }

    size_t delim_len = strnlen(delimiters, 256);
    size_t pattern_size = delim_len + 5;
    char *pattern = malloc(pattern_size);
    if (!pattern) {
        return NULL;
    }
    snprintf(pattern, pattern_size, "[%s]+", delimiters);

    regex_t regex;
    int ret = regcomp(&regex, pattern, REG_EXTENDED);
    free(pattern);
    if (ret != 0) {
        return NULL;
    }

    char **tokens = NULL;
    int token_count = 0;
    const char *current = input;
    regmatch_t match;
    size_t input_len = strnlen(input, 65536);

    while (*current && (size_t)(current - input) < input_len) {
        if (regexec(&regex, current, 1, &match, 0) == 0) {
            if (match.rm_so > 0) {
                char **new_tokens = realloc(tokens, (token_count + 1) * sizeof(char *));
                if (!new_tokens) {
                    for (int i = 0; i < token_count; i++) {
                        free(tokens[i]);
                    }
                    free(tokens);
                    regfree(&regex);
                    *count = 0;
                    return NULL;
                }
                tokens = new_tokens;
                tokens[token_count] = strndup(current, match.rm_so);
                if (!tokens[token_count]) {
                    for (int i = 0; i < token_count; i++) {
                        free(tokens[i]);
                    }
                    free(tokens);
                    regfree(&regex);
                    *count = 0;
                    return NULL;
                }
                token_count++;
            }
            current += match.rm_eo;
        } else {
            size_t remaining = strnlen(current, input_len - (current - input));
            if (remaining > 0) {
                char **new_tokens = realloc(tokens, (token_count + 1) * sizeof(char *));
                if (!new_tokens) {
                    for (int i = 0; i < token_count; i++) {
                        free(tokens[i]);
                    }
                    free(tokens);
                    regfree(&regex);
                    *count = 0;
                    return NULL;
                }
                tokens = new_tokens;
                tokens[token_count] = strndup(current, remaining);
                if (!tokens[token_count]) {
                    for (int i = 0; i < token_count; i++) {
                        free(tokens[i]);
                    }
                    free(tokens);
                    regfree(&regex);
                    *count = 0;
                    return NULL;
                }
                token_count++;
            }
            break;
        }
    }

    regfree(&regex);
    *count = token_count;
    return tokens;
}

static void free_tokens(char **tokens, int count) {
    if (!tokens) return;
    for (int i = 0; i < count; i++) {
        free(tokens[i]);
    }
    free(tokens);
}

int main(void) {
    const char *input = "Hello,world;this:is|a test,string;with:multiple delimiters";
    const char *delimiters = ",;:| ";
    int count = 0;

    char **tokens = split_string(input, delimiters, &count);

    if (!tokens) {
        fprintf(stderr, "Failed to split string\n");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        printf("Token %d: %s\n", i, tokens[i]);
    }

    free_tokens(tokens, count);
    return 0;
}