#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void set_error(char *buffer, size_t buffer_size, const char *message)
{
    if (buffer != NULL && buffer_size > 0U) {
        (void)snprintf(buffer, buffer_size, "%s", message);
    }
}

void free_split_tokens(char **tokens, size_t count)
{
    size_t i;

    if (tokens == NULL) {
        return;
    }

    for (i = 0U; i < count; ++i) {
        free(tokens[i]);
    }

    free(tokens);
}

static int append_token(char ***tokens, size_t *count, size_t *capacity,
                        const char *start, size_t length)
{
    char **resized_tokens;
    char *token;
    size_t needed;
    size_t new_capacity;
    size_t max_items;

    if (*count > SIZE_MAX - 2U || length == SIZE_MAX) {
        return -1;
    }

    needed = *count + 2U;
    max_items = SIZE_MAX / sizeof(**tokens);

    if (needed > max_items) {
        return -1;
    }

    if (*capacity < needed) {
        new_capacity = (*capacity == 0U) ? 8U : *capacity;

        if (new_capacity > max_items) {
            new_capacity = max_items;
        }

        while (new_capacity < needed) {
            if (new_capacity > max_items / 2U) {
                new_capacity = max_items;
            } else {
                new_capacity *= 2U;
            }
        }

        resized_tokens = realloc(*tokens, new_capacity * sizeof(**tokens));
        if (resized_tokens == NULL) {
            return -1;
        }

        *tokens = resized_tokens;
        *capacity = new_capacity;
    }

    token = malloc(length + 1U);
    if (token == NULL) {
        return -1;
    }

    if (length > 0U) {
        memcpy(token, start, length);
    }
    token[length] = '\0';

    (*tokens)[*count] = token;
    ++(*count);
    (*tokens)[*count] = NULL;

    return 0;
}

int split_regex(const char *input, const char *delimiter_pattern,
                char ***tokens_out, size_t *count_out,
                char *error_buffer, size_t error_buffer_size)
{
    regex_t regex;
    regmatch_t match;
    regmatch_t empty_match;
    char **tokens = NULL;
    size_t count = 0U;
    size_t capacity = 0U;
    size_t input_length;
    size_t offset = 0U;
    size_t remaining;
    size_t match_start;
    size_t match_end;
    int result;
    int flags;

    if (tokens_out == NULL || count_out == NULL) {
        set_error(error_buffer, error_buffer_size, "Invalid output argument");
        return -1;
    }

    *tokens_out = NULL;
    *count_out = 0U;

    if (input == NULL || delimiter_pattern == NULL) {
        set_error(error_buffer, error_buffer_size, "Invalid input argument");
        return -1;
    }

    result = regcomp(&regex, delimiter_pattern, REG_EXTENDED);
    if (result != 0) {
        if (error_buffer != NULL && error_buffer_size > 0U) {
            (void)regerror(result, &regex, error_buffer, error_buffer_size);
        }
        return -1;
    }

    result = regexec(&regex, "", 1U, &empty_match, 0);
    if (result == 0 && empty_match.rm_so == empty_match.rm_eo) {
        set_error(error_buffer, error_buffer_size,
                  "Delimiter regex must not match an empty string");
        regfree(&regex);
        return -1;
    }

    if (result != 0 && result != REG_NOMATCH) {
        if (error_buffer != NULL && error_buffer_size > 0U) {
            (void)regerror(result, &regex, error_buffer, error_buffer_size);
        }
        regfree(&regex);
        return -1;
    }

    input_length = strlen(input);

    while (offset <= input_length) {
        remaining = input_length - offset;
        flags = (offset == 0U) ? 0 : REG_NOTBOL;
        result = regexec(&regex, input + offset, 1U, &match, flags);

        if (result == REG_NOMATCH) {
            if (append_token(&tokens, &count, &capacity,
                             input + offset, remaining) != 0) {
                set_error(error_buffer, error_buffer_size,
                          "Memory allocation failed");
                free_split_tokens(tokens, count);
                regfree(&regex);
                return -1;
            }
            break;
        }

        if (result != 0) {
            if (error_buffer != NULL && error_buffer_size > 0U) {
                (void)regerror(result, &regex, error_buffer, error_buffer_size);
            }
            free_split_tokens(tokens, count);
            regfree(&regex);
            return -1;
        }

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            set_error(error_buffer, error_buffer_size,
                      "Delimiter regex produced an invalid or empty match");
            free_split_tokens(tokens, count);
            regfree(&regex);
            return -1;
        }

        match_start = (size_t)match.rm_so;
        match_end = (size_t)match.rm_eo;

        if (match_start > remaining || match_end > remaining) {
            set_error(error_buffer, error_buffer_size,
                      "Delimiter regex produced an out-of-range match");
            free_split_tokens(tokens, count);
            regfree(&regex);
            return -1;
        }

        if (append_token(&tokens, &count, &capacity,
                         input + offset, match_start) != 0) {
            set_error(error_buffer, error_buffer_size,
                      "Memory allocation failed");
            free_split_tokens(tokens, count);
            regfree(&regex);
            return -1;
        }

        offset += match_end;
    }

    regfree(&regex);
    *tokens_out = tokens;
    *count_out = count;
    return 0;
}

int main(int argc, char *argv[])
{
    char **tokens = NULL;
    size_t count = 0U;
    size_t i;
    char error_buffer[256];

    if (argc != 3) {
        (void)fprintf(stderr, "Usage: %s <string> <delimiter-regex>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (split_regex(argv[1], argv[2], &tokens, &count,
                    error_buffer, sizeof(error_buffer)) != 0) {
        (void)fprintf(stderr, "Error: %s\n", error_buffer);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; ++i) {
        if (fputs(tokens[i], stdout) == EOF || fputc('\n', stdout) == EOF) {
            (void)fprintf(stderr, "Error: Failed to write output\n");
            free_split_tokens(tokens, count);
            return EXIT_FAILURE;
        }
    }

    free_split_tokens(tokens, count);

    if (fflush(stdout) == EOF) {
        (void)fprintf(stderr, "Error: Failed to flush output\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}