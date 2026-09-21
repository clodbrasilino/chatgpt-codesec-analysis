#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

static char **split_string(const char *input, const char *delimiter_pattern, int *token_count) {
    regex_t regex;
    regmatch_t match;
    char **tokens = NULL;
    int count = 0;
    size_t capacity = 10;
    const char *cursor = input;
    const char *token_start = input;
    int compile_result;

    if (input == NULL || delimiter_pattern == NULL || token_count == NULL) {
        return NULL;
    }

    compile_result = regcomp(&regex, delimiter_pattern, REG_EXTENDED);
    if (compile_result != 0) {
        return NULL;
    }

    tokens = (char **)malloc(capacity * sizeof(char *));
    if (tokens == NULL) {
        regfree(&regex);
        return NULL;
    }

    while (*cursor != '\0') {
        int match_result = regexec(&regex, cursor, 1, &match, 0);
        if (match_result == 0) {
            const char *match_start = cursor + match.rm_so;
            size_t token_length = (size_t)(match_start - token_start);
            if (token_length > 0) {
                if (count >= capacity) {
                    if (capacity > SIZE_MAX / 2 / sizeof(char *)) {
                        for (size_t i = 0; i < count; i++) {
                            free(tokens[i]);
                        }
                        free(tokens);
                        regfree(&regex);
                        return NULL;
                    }
                    size_t new_capacity = capacity * 2;
                    char **new_tokens = (char **)realloc(tokens, new_capacity * sizeof(char *));
                    if (new_tokens == NULL) {
                        for (size_t i = 0; i < count; i++) {
                            free(tokens[i]);
                        }
                        free(tokens);
                        regfree(&regex);
                        return NULL;
                    }
                    tokens = new_tokens;
                    capacity = new_capacity;
                }
                if (token_length >= SIZE_MAX) {
                    for (size_t i = 0; i < count; i++) {
                        free(tokens[i]);
                    }
                    free(tokens);
                    regfree(&regex);
                    return NULL;
                }
                tokens[count] = (char *)malloc(token_length + 1);
                if (tokens[count] == NULL) {
                    for (size_t i = 0; i < count; i++) {
                        free(tokens[i]);
                    }
                    free(tokens);
                    regfree(&regex);
                    return NULL;
                }
                if (token_length > SIZE_MAX - 1) {
                    free(tokens[count]);
                    for (size_t i = 0; i < count; i++) {
                        free(tokens[i]);
                    }
                    free(tokens);
                    regfree(&regex);
                    return NULL;
                }
                memcpy(tokens[count], token_start, token_length);
                tokens[count][token_length] = '\0';
                count++;
            }
            cursor += match.rm_eo;
            token_start = cursor;
        } else if (match_result == REG_NOMATCH) {
            break;
        } else {
            for (size_t i = 0; i < count; i++) {
                free(tokens[i]);
            }
            free(tokens);
            regfree(&regex);
            return NULL;
        }
    }

    if (*token_start != '\0') {
        size_t remaining_length = strlen(token_start);
        if (remaining_length > 0) {
            if (count >= capacity) {
                if (capacity > SIZE_MAX / 2 / sizeof(char *)) {
                    for (size_t i = 0; i < count; i++) {
                        free(tokens[i]);
                    }
                    free(tokens);
                    regfree(&regex);
                    return NULL;
                }
                size_t new_capacity = capacity * 2;
                char **new_tokens = (char **)realloc(tokens, new_capacity * sizeof(char *));
                if (new_tokens == NULL) {
                    for (size_t i = 0; i < count; i++) {
                        free(tokens[i]);
                    }
                    free(tokens);
                    regfree(&regex);
                    return NULL;
                }
                tokens = new_tokens;
                capacity = new_capacity;
            }
            if (remaining_length >= SIZE_MAX) {
                for (size_t i = 0; i < count; i++) {
                    free(tokens[i]);
                }
                free(tokens);
                regfree(&regex);
                return NULL;
            }
            tokens[count] = (char *)malloc(remaining_length + 1);
            if (tokens[count] == NULL) {
                for (size_t i = 0; i < count; i++) {
                    free(tokens[i]);
                }
                free(tokens);
                regfree(&regex);
                return NULL;
            }
            if (remaining_length > SIZE_MAX - 1) {
                free(tokens[count]);
                for (size_t i = 0; i < count; i++) {
                    free(tokens[i]);
                }
                free(tokens);
                regfree(&regex);
                return NULL;
            }
            memcpy(tokens[count], token_start, remaining_length + 1);
            count++;
        }
    }

    if (count == 0) {
        free(tokens);
        tokens = NULL;
    } else {
        char **final_tokens = (char **)realloc(tokens, (size_t)count * sizeof(char *));
        if (final_tokens != NULL) {
            tokens = final_tokens;
        }
    }

    *token_count = count;
    regfree(&regex);
    return tokens;
}

static void free_tokens(char **tokens, int token_count) {
    if (tokens == NULL) {
        return;
    }
    for (int i = 0; i < token_count; i++) {
        free(tokens[i]);
    }
    free(tokens);
}

int main(void) {
    const char *input = "Hello,world;this:is|a test";
    const char *pattern = "[,;:| ]+";
    int token_count = 0;
    char **tokens = split_string(input, pattern, &token_count);

    if (tokens == NULL) {
        fprintf(stderr, "Failed to split string\n");
        return 1;
    }

    for (int i = 0; i < token_count; i++) {
        printf("Token %d: %s\n", i, tokens[i]);
    }

    free_tokens(tokens, token_count);
    return 0;
}