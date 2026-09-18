#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static void free_tokens(char **tokens, size_t count) {
    if (!tokens) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(tokens[i]);
    }
    free(tokens);
}

char **split_string_regex(const char *str, const char *pattern, size_t *out_count) {
    if (!str || !pattern || !out_count) {
        return NULL;
    }

    regex_t regex;
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return NULL;
    }

    size_t capacity = 10;
    size_t count = 0;
    char **tokens = malloc(capacity * sizeof(char *));
    if (!tokens) {
        regfree(&regex);
        return NULL;
    }

    regmatch_t pmatch[1];
    const char *cursor = str;

    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        if (count >= capacity - 1) {
            size_t new_capacity = capacity * 2;
            char **new_tokens = realloc(tokens, new_capacity * sizeof(char *));
            if (!new_tokens) {
                free_tokens(tokens, count);
                regfree(&regex);
                return NULL;
            }
            tokens = new_tokens;
            capacity = new_capacity;
        }

        regoff_t match_start = pmatch[0].rm_so;
        regoff_t match_end = pmatch[0].rm_eo;

        size_t token_len = (size_t)match_start;
        tokens[count] = malloc(token_len + 1);
        if (!tokens[count]) {
            free_tokens(tokens, count);
            regfree(&regex);
            return NULL;
        }

        memcpy(tokens[count], cursor, token_len);
        tokens[count][token_len] = '\0';
        count++;

        cursor += match_end;
        if (match_start == match_end) {
            if (*cursor == '\0') {
                break;
            }
            cursor++;
        }
    }

    size_t remaining_len = strlen(cursor);
    if (count >= capacity - 1) {
        char **new_tokens = realloc(tokens, (count + 2) * sizeof(char *));
        if (!new_tokens) {
            free_tokens(tokens, count);
            regfree(&regex);
            return NULL;
        }
        tokens = new_tokens;
    }

    tokens[count] = malloc(remaining_len + 1);
    if (!tokens[count]) {
        free_tokens(tokens, count);
        regfree(&regex);
        return NULL;
    }

    memcpy(tokens[count], cursor, remaining_len);
    tokens[count][remaining_len] = '\0';
    count++;

    tokens[count] = NULL;
    *out_count = count;

    regfree(&regex);
    return tokens;
}

int main(void) {
    const char *text = "apple, banana; cherry|date\torange";
    const char *pattern = "[,;| \t]+";
    size_t count = 0;

    char **tokens = split_string_regex(text, pattern, &count);
    if (!tokens) {
        fprintf(stderr, "Error processing string.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", tokens[i]);
    }

    free_tokens(tokens, count);

    return EXIT_SUCCESS;
}