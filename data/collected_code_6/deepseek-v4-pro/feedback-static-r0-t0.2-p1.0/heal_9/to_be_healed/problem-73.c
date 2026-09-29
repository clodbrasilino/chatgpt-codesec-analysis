#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

char **split_string(const char *input, const char *delimiter_pattern, int *token_count) {
    regex_t regex;
    regmatch_t match;
    char **tokens = NULL;
    int count = 0;
    int capacity = 10;
    const char *cursor;
    const char *token_start;
    int compile_result;
    size_t input_length;
    size_t token_length;

    if (input == NULL || delimiter_pattern == NULL || token_count == NULL) {
        return NULL;
    }

    input_length = strnlen(input, 4096);
    if (input_length == 0 || input_length >= 4096) {
        *token_count = 0;
        return NULL;
    }

    compile_result = regcomp(&regex, delimiter_pattern, REG_EXTENDED);
    if (compile_result != 0) {
        return NULL;
    }

    tokens = malloc(capacity * sizeof(char *));
    if (tokens == NULL) {
        regfree(&regex);
        return NULL;
    }

    cursor = input;
    token_start = input;

    while (*cursor != '\0') {
        int exec_result = regexec(&regex, cursor, 1, &match, 0);
        if (exec_result == 0) {
            if (cursor + match.rm_so >= token_start) {
                token_length = (size_t)(cursor + match.rm_so - token_start);
            } else {
                int i;
                for (i = 0; i < count; i++) {
                    free(tokens[i]);
                }
                free(tokens);
                regfree(&regex);
                return NULL;
            }

            if (token_length > 0) {
                if (count >= capacity) {
                    size_t new_capacity = (size_t)capacity * 2;
                    if (new_capacity > SIZE_MAX / sizeof(char *)) {
                        int i;
                        for (i = 0; i < count; i++) {
                            free(tokens[i]);
                        }
                        free(tokens);
                        regfree(&regex);
                        return NULL;
                    }
                    capacity = (int)new_capacity;
                    char **new_tokens = realloc(tokens, capacity * sizeof(char *));
                    if (new_tokens == NULL) {
                        int i;
                        for (i = 0; i < count; i++) {
                            free(tokens[i]);
                        }
                        free(tokens);
                        regfree(&regex);
                        return NULL;
                    }
                    tokens = new_tokens;
                }

                if (token_length >= 4096) {
                    int i;
                    for (i = 0; i < count; i++) {
                        free(tokens[i]);
                    }
                    free(tokens);
                    regfree(&regex);
                    return NULL;
                }

                tokens[count] = malloc(token_length + 1);
                if (tokens[count] == NULL) {
                    int i;
                    for (i = 0; i < count; i++) {
                        free(tokens[i]);
                    }
                    free(tokens);
                    regfree(&regex);
                    return NULL;
                }

                if (token_length > 0 && tokens[count] != NULL) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(tokens[count], token_start, token_length);
                }
                tokens[count][token_length] = '\0';
                count++;
            }
            cursor += match.rm_eo;
            token_start = cursor;
        } else if (exec_result == REG_NOMATCH) {
            break;
        } else {
            int i;
            for (i = 0; i < count; i++) {
                free(tokens[i]);
            }
            free(tokens);
            regfree(&regex);
            return NULL;
        }
    }

    if (*token_start != '\0') {
        size_t remaining_length = input_length - (size_t)(token_start - input);

        if (remaining_length >= 4096) {
            int i;
            for (i = 0; i < count; i++) {
                free(tokens[i]);
            }
            free(tokens);
            regfree(&regex);
            return NULL;
        }

        if (count >= capacity) {
            size_t new_capacity = (size_t)capacity * 2;
            if (new_capacity > SIZE_MAX / sizeof(char *)) {
                int i;
                for (i = 0; i < count; i++) {
                    free(tokens[i]);
                }
                free(tokens);
                regfree(&regex);
                return NULL;
            }
            capacity = (int)new_capacity;
            char **new_tokens = realloc(tokens, capacity * sizeof(char *));
            if (new_tokens == NULL) {
                int i;
                for (i = 0; i < count; i++) {
                    free(tokens[i]);
                }
                free(tokens);
                regfree(&regex);
                return NULL;
            }
            tokens = new_tokens;
        }

        tokens[count] = malloc(remaining_length + 1);
        if (tokens[count] == NULL) {
            int i;
            for (i = 0; i < count; i++) {
                free(tokens[i]);
            }
            free(tokens);
            regfree(&regex);
            return NULL;
        }

        if (remaining_length > 0 && tokens[count] != NULL) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(tokens[count], token_start, remaining_length);
        }
        tokens[count][remaining_length] = '\0';
        count++;
    }

    if (count == 0) {
        free(tokens);
        tokens = NULL;
    } else {
        char **final_tokens = realloc(tokens, count * sizeof(char *));
        if (final_tokens != NULL) {
            tokens = final_tokens;
        }
    }

    *token_count = count;
    regfree(&regex);
    return tokens;
}

void free_tokens(char **tokens, int count) {
    int i;
    if (tokens == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        free(tokens[i]);
    }
    free(tokens);
}

int main(void) {
    const char *input = "Hello,world;this:is|a test";
    const char *pattern = "[,;:| ]+";
    int token_count = 0;
    char **tokens = split_string(input, pattern, &token_count);

    if (tokens == NULL && token_count > 0) {
        fprintf(stderr, "Failed to split string\n");
        return 1;
    }

    if (tokens != NULL) {
        int i;
        for (i = 0; i < token_count; i++) {
            printf("Token %d: %s\n", i, tokens[i]);
        }
        free_tokens(tokens, token_count);
    }

    return 0;
}