#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char **split_string(const char *input, const char *delimiter_pattern, int *token_count) {
    regex_t regex;
    regmatch_t match;
    char **tokens = NULL;
    int count = 0;
    int capacity = 10;
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
            size_t token_length = (size_t)(cursor - token_start);
            if (token_length > 0) {
                if (count >= capacity) {
                    int new_capacity = capacity * 2;
                    if (new_capacity <= capacity) {
                        for (int i = 0; i < count; i++) {
                            free(tokens[i]);
                        }
                        free(tokens);
                        regfree(&regex);
                        return NULL;
                    }
                    char **new_tokens = (char **)realloc(tokens, new_capacity * sizeof(char *));
                    if (new_tokens == NULL) {
                        for (int i = 0; i < count; i++) {
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
                    for (int i = 0; i < count; i++) {
                        free(tokens[i]);
                    }
                    free(tokens);
                    regfree(&regex);
                    return NULL;
                }
                tokens[count] = (char *)malloc((token_length + 1) * sizeof(char));
                if (tokens[count] == NULL) {
                    for (int i = 0; i < count; i++) {
                        free(tokens[i]);
                    }
                    free(tokens);
                    regfree(&regex);
                    return NULL;
                }
                if (token_length > 0) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(tokens[count], token_start, token_length);
                }
                tokens[count][token_length] = '\0';
                count++;
            }
            if (match.rm_eo > 0) {
                cursor += match.rm_eo;
            } else {
                cursor++;
            }
            token_start = cursor;
        } else if (match_result == REG_NOMATCH) {
            break;
        } else {
            for (int i = 0; i < count; i++) {
                free(tokens[i]);
            }
            free(tokens);
            regfree(&regex);
            return NULL;
        }
    }

    if (*token_start != '\0') {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t remaining_length = strlen(token_start);
        if (remaining_length > 0) {
            if (count >= capacity) {
                int new_capacity = capacity * 2;
                if (new_capacity <= capacity) {
                    for (int i = 0; i < count; i++) {
                        free(tokens[i]);
                    }
                    free(tokens);
                    regfree(&regex);
                    return NULL;
                }
                char **new_tokens = (char **)realloc(tokens, new_capacity * sizeof(char *));
                if (new_tokens == NULL) {
                    for (int i = 0; i < count; i++) {
                        free(tokens[i]);
                    }
                    free(tokens);
                    regfree(&regex);
                    return NULL;
                }
                tokens = new_tokens;
                /* Possible weaknesses found:
                 *  Variable 'capacity' is assigned a value that is never used. [unreadVariable]
                 *  Value stored to 'capacity' is never read [deadcode.DeadStores]
                 */
                capacity = new_capacity;
            }
            if (remaining_length >= SIZE_MAX) {
                for (int i = 0; i < count; i++) {
                    free(tokens[i]);
                }
                free(tokens);
                regfree(&regex);
                return NULL;
            }
            tokens[count] = (char *)malloc((remaining_length + 1) * sizeof(char));
            if (tokens[count] == NULL) {
                for (int i = 0; i < count; i++) {
                    free(tokens[i]);
                }
                free(tokens);
                regfree(&regex);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(tokens[count], token_start, remaining_length);
            tokens[count][remaining_length] = '\0';
            count++;
        }
    }

    if (count == 0) {
        free(tokens);
        tokens = NULL;
    } else {
        char **final_tokens = (char **)realloc(tokens, count * sizeof(char *));
        if (final_tokens != NULL) {
            tokens = final_tokens;
        }
    }

    *token_count = count;
    regfree(&regex);
    return tokens;
}

void free_tokens(char **tokens, int token_count) {
    if (tokens == NULL) {
        return;
    }
    for (int i = 0; i < token_count; i++) {
        if (tokens[i] != NULL) {
            free(tokens[i]);
        }
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