#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void free_string_array(char **array, size_t count);
char **split_string_by_regex(const char *input, const char *pattern, size_t *out_count);

void free_string_array(char **array, size_t count) {
    if (!array) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(array[i]);
    }
    free(array);
}

char **split_string_by_regex(const char *input, const char *pattern, size_t *out_count) {
    if (!input || !pattern || !out_count) {
        return NULL;
    }

    regex_t regex;
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return NULL;
    }

    size_t capacity = 16;
    size_t count = 0;
    char **tokens = malloc(capacity * sizeof(char *));
    
    if (!tokens) {
        regfree(&regex);
        return NULL;
    }

    const char *cursor = input;
    regmatch_t match[1];

    while (regexec(&regex, cursor, 1, match, 0) == 0) {
        size_t token_length = (size_t)match[0].rm_so;
        char *token = malloc(token_length + 1);
        
        if (!token) {
            free_string_array(tokens, count);
            regfree(&regex);
            return NULL;
        }
        
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(token, cursor, token_length);
        token[token_length] = '\0';

        if (count >= capacity) {
            size_t new_capacity = capacity * 2;
            char **new_tokens = realloc(tokens, new_capacity * sizeof(char *));
            if (!new_tokens) {
                free(token);
                free_string_array(tokens, count);
                regfree(&regex);
                return NULL;
            }
            tokens = new_tokens;
            capacity = new_capacity;
        }
        
        tokens[count++] = token;
        cursor += match[0].rm_eo;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t remaining_length = strlen(cursor);
    char *last_token = malloc(remaining_length + 1);
    
    if (!last_token) {
        free_string_array(tokens, count);
        regfree(&regex);
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(last_token, cursor, remaining_length);
    last_token[remaining_length] = '\0';

    if (count >= capacity) {
        char **new_tokens = realloc(tokens, (capacity + 1) * sizeof(char *));
        if (!new_tokens) {
            free(last_token);
            free_string_array(tokens, count);
            regfree(&regex);
            return NULL;
        }
        tokens = new_tokens;
    }
    
    tokens[count++] = last_token;

    regfree(&regex);
    *out_count = count;
    
    return tokens;
}

int main(void) {
    const char *text = "apple, orange;banana|grape!mango";
    const char *pattern = "[,;|! ]+";
    size_t token_count = 0;

    char **result = split_string_by_regex(text, pattern, &token_count);

    if (!result) {
        fprintf(stderr, "Failed to split string.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < token_count; i++) {
        printf("Token %zu: %s\n", i, result[i]);
    }

    free_string_array(result, token_count);

    return EXIT_SUCCESS;
}