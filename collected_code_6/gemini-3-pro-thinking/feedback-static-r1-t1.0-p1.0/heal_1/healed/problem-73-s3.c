#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

typedef struct {
    char **tokens;
    size_t count;
} StringArray;

void free_string_array(StringArray *array) {
    if (!array) {
        return;
    }
    if (array->tokens) {
        for (size_t i = 0; i < array->count; i++) {
            free(array->tokens[i]);
        }
        free(array->tokens);
    }
    free(array);
}

StringArray* split_string(const char *str, const char *pattern) {
    if (!str || !pattern) {
        return NULL;
    }

    StringArray *result = malloc(sizeof(StringArray));
    if (!result) {
        return NULL;
    }
    result->tokens = NULL;
    result->count = 0;

    regex_t regex;
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        free(result);
        return NULL;
    }

    const char *cursor = str;
    regmatch_t match;
    size_t capacity = 0;

    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        if (match.rm_so < 0 || match.rm_eo < 0) {
            break;
        }

        size_t len = (size_t)match.rm_so;
        char *token = malloc(len + 1);
        if (!token) {
            regfree(&regex);
            free_string_array(result);
            return NULL;
        }

        for (size_t i = 0; i < len; i++) {
            token[i] = cursor[i];
        }
        token[len] = '\0';

        if (result->count >= capacity) {
            size_t new_capacity = capacity == 0 ? 4 : capacity * 2;
            char **new_tokens = realloc(result->tokens, new_capacity * sizeof(char *));
            if (!new_tokens) {
                free(token);
                regfree(&regex);
                free_string_array(result);
                return NULL;
            }
            result->tokens = new_tokens;
            capacity = new_capacity;
        }

        result->tokens[result->count++] = token;
        
        if (match.rm_eo == 0) {
            cursor++;
        } else {
            cursor += match.rm_eo;
        }
    }

    size_t remaining_len = 0;
    while (cursor[remaining_len] != '\0') {
        remaining_len++;
    }

    char *last_token = malloc(remaining_len + 1);
    if (!last_token) {
        regfree(&regex);
        free_string_array(result);
        return NULL;
    }

    for (size_t i = 0; i < remaining_len; i++) {
        last_token[i] = cursor[i];
    }
    last_token[remaining_len] = '\0';

    if (result->count >= capacity) {
        char **new_tokens = realloc(result->tokens, (result->count + 1) * sizeof(char *));
        if (!new_tokens) {
            free(last_token);
            regfree(&regex);
            free_string_array(result);
            return NULL;
        }
        result->tokens = new_tokens;
    }
    result->tokens[result->count++] = last_token;

    regfree(&regex);
    return result;
}

int main(void) {
    const char *str = "apple,banana;cherry|date orange";
    const char *pattern = "[,;| ]";

    StringArray *result = split_string(str, pattern);
    if (!result) {
        fprintf(stderr, "Failed to split string.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < result->count; i++) {
        printf("%s\n", result->tokens[i]);
    }

    free_string_array(result);
    return EXIT_SUCCESS;
}