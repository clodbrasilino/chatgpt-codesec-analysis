#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void set_error(char *buffer, size_t buffer_size, const char *message)
{
    if (buffer != NULL && buffer_size > 0U) {
        (void)snprintf(buffer, buffer_size, "%s", message);
    }
}

static void set_regex_error(char *buffer, size_t buffer_size,
                            int error_code, const regex_t *regex)
{
    if (buffer != NULL && buffer_size > 0U) {
        (void)regerror(error_code, regex, buffer, buffer_size);
    }
}

static size_t string_length(const char *string)
{
    const char *end = string;

    while (*end != '\0') {
        ++end;
    }

    return (size_t)(end - string);
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
    size_t needed;
    size_t max_items;
    size_t i;
    char **resized_tokens;
    char *token;

    if (tokens == NULL || count == NULL || capacity == NULL ||
        (start == NULL && length != 0U)) {
        return -1;
    }

    if ((*tokens == NULL && (*capacity != 0U || *count != 0U)) ||
        (*tokens != NULL && (*capacity == 0U || *count >= *capacity))) {
        return -1;
    }

    if (*count > SIZE_MAX - 2U || length == SIZE_MAX) {
        return -1;
    }

    max_items = SIZE_MAX / sizeof **tokens;
    needed = *count + 2U;

    if (needed > max_items) {
        return -1;
    }

    if (*capacity < needed) {
        size_t new_capacity = (*capacity == 0U) ? 8U : *capacity;

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

        resized_tokens = realloc(*tokens,
                                 new_capacity * sizeof **tokens);
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

    for (i = 0U; i < length; ++i) {
        token[i] = start[i];
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
    char **tokens = NULL;
    size_t count = 0U;
    size_t capacity = 0U;
    size_t input_length;
    size_t offset = 0U;
    int result;

    if (error_buffer != NULL && error_buffer_size > 0U) {
        error_buffer[0] = '\0';
    }

    if (tokens_out == NULL || count_out == NULL) {
        set_error(error_buffer, error_buffer_size,
                  "Invalid output argument");
        return -1;
    }

    *tokens_out = NULL;
    *count_out = 0U;

    if (input == NULL || delimiter_pattern == NULL) {
        set_error(error_buffer, error_buffer_size,
                  "Invalid input argument");
        return -1;
    }

    result = regcomp(&regex, delimiter_pattern, REG_EXTENDED);
    if (result != 0) {
        set_regex_error(error_buffer, error_buffer_size, result, &regex);
        return -1;
    }

    result = regexec(&regex, "", 0U, NULL, 0);
    if (result == 0) {
        set_error(error_buffer, error_buffer_size,
                  "Delimiter regex must not match an empty string");
        regfree(&regex);
        return -1;
    }

    if (result != REG_NOMATCH) {
        set_regex_error(error_buffer, error_buffer_size, result, &regex);
        regfree(&regex);
        return -1;
    }

    input_length = string_length(input);

    while (offset <= input_length) {
        regmatch_t match;
        size_t remaining = input_length - offset;
        size_t match_start;
        size_t match_end;
        int flags = (offset == 0U) ? 0 : REG_NOTBOL;

        result = regexec(&regex, input + offset, 1U, &match, flags);

        if (result == REG_NOMATCH) {
            if (append_token(&tokens, &count, &capacity,
                             input + offset, remaining) != 0) {
                set_error(error_buffer, error_buffer_size,
                          "Memory allocation or size limit exceeded");
                free_split_tokens(tokens, count);
                regfree(&regex);
                return -1;
            }
            break;
        }

        if (result != 0) {
            set_regex_error(error_buffer, error_buffer_size,
                            result, &regex);
            free_split_tokens(tokens, count);
            regfree(&regex);
            return -1;
        }

        if (match.rm_so < 0 || match.rm_eo < 0 ||
            match.rm_eo <= match.rm_so) {
            set_error(error_buffer, error_buffer_size,
                      "Delimiter regex produced an invalid or empty match");
            free_split_tokens(tokens, count);
            regfree(&regex);
            return -1;
        }

        if ((uintmax_t)match.rm_so > (uintmax_t)remaining ||
            (uintmax_t)match.rm_eo > (uintmax_t)remaining) {
            set_error(error_buffer, error_buffer_size,
                      "Delimiter regex produced an out-of-range match");
            free_split_tokens(tokens, count);
            regfree(&regex);
            return -1;
        }

        match_start = (size_t)match.rm_so;
        match_end = (size_t)match.rm_eo;

        if (append_token(&tokens, &count, &capacity,
                         input + offset, match_start) != 0) {
            set_error(error_buffer, error_buffer_size,
                      "Memory allocation or size limit exceeded");
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
    const size_t error_buffer_size = 256U;
    char *error_buffer;
    char **tokens = NULL;
    size_t count = 0U;
    size_t i;

    if (argc != 3) {
        const char *program_name =
            (argc > 0 && argv[0] != NULL) ? argv[0] : "split_regex";

        (void)fprintf(stderr,
                      "Usage: %s <string> <delimiter-regex>\n",
                      program_name);
        return EXIT_FAILURE;
    }

    error_buffer = calloc(error_buffer_size, sizeof *error_buffer);
    if (error_buffer == NULL) {
        (void)fputs("Error: Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (split_regex(argv[1], argv[2], &tokens, &count,
                    error_buffer, error_buffer_size) != 0) {
        (void)fprintf(stderr, "Error: %s\n", error_buffer);
        free(error_buffer);
        return EXIT_FAILURE;
    }

    free(error_buffer);

    for (i = 0U; i < count; ++i) {
        if (fputs(tokens[i], stdout) == EOF ||
            fputc('\n', stdout) == EOF) {
            (void)fputs("Error: Failed to write output\n", stderr);
            free_split_tokens(tokens, count);
            return EXIT_FAILURE;
        }
    }

    free_split_tokens(tokens, count);

    if (fflush(stdout) == EOF) {
        (void)fputs("Error: Failed to flush output\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}