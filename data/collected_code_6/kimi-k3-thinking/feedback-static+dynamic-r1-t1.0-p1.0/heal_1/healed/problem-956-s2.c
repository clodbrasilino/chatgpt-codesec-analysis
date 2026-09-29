#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>

#define MAX_INPUT_LENGTH ((size_t)1024 * 1024)

static char *duplicate_range(const char *start, size_t length)
{
    char *result;

    if (start == NULL || length == SIZE_MAX) {
        return NULL;
    }

    result = (char *)malloc(length + 1);
    if (result == NULL) {
        return NULL;
    }

    memcpy(result, start, length);
    result[length] = '\0';
    return result;
}

static int append_token(char ***tokens, size_t *count, size_t *capacity,
                        const char *start, size_t length)
{
    if (*count == *capacity) {
        size_t new_capacity = (*capacity == 0) ? 8 : *capacity * 2;
        char **new_tokens;

        if (new_capacity > SIZE_MAX / sizeof(*new_tokens)) {
            return -1;
        }

        new_tokens = (char **)realloc(*tokens, new_capacity * sizeof(*new_tokens));
        if (new_tokens == NULL) {
            return -1;
        }
        *tokens = new_tokens;
        *capacity = new_capacity;
    }

    (*tokens)[*count] = duplicate_range(start, length);
    if ((*tokens)[*count] == NULL) {
        return -1;
    }
    (*count)++;
    return 0;
}

static void report_regex_error(int ret, const regex_t *regex, const char *stage)
{
    size_t error_size = regerror(ret, regex, NULL, 0);
    char *error_buffer;

    if (error_size == 0) {
        fprintf(stderr, "%s failed with error code %d\n", stage, ret);
        return;
    }

    error_buffer = (char *)malloc(error_size);
    if (error_buffer == NULL) {
        fprintf(stderr, "%s failed with error code %d\n", stage, ret);
        return;
    }

    regerror(ret, regex, error_buffer, error_size);
    fprintf(stderr, "%s failed: %s\n", stage, error_buffer);
    free(error_buffer);
}

int split_at_uppercase(const char *input, char ***tokens_out, size_t *count_out)
{
    regex_t regex;
    regmatch_t match;
    int ret;
    char **tokens = NULL;
    size_t token_count = 0;
    size_t capacity = 0;
    size_t segment_start = 0;
    size_t offset = 0;
    size_t input_length;
    size_t upper_pos;

    if (input == NULL || tokens_out == NULL || count_out == NULL) {
        return -1;
    }

    *tokens_out = NULL;
    *count_out = 0;

    input_length = strnlen(input, MAX_INPUT_LENGTH);
    if (input_length == MAX_INPUT_LENGTH) {
        fprintf(stderr, "Input exceeds maximum length or is not NUL-terminated\n");
        return -1;
    }

    ret = regcomp(&regex, "[A-Z]", REG_EXTENDED);
    if (ret != 0) {
        report_regex_error(ret, &regex, "regcomp");
        return -1;
    }

    while (offset < input_length) {
        ret = regexec(&regex, input + offset, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            report_regex_error(ret, &regex, "regexec");
            goto fail;
        }

        upper_pos = offset + (size_t)match.rm_so;
        if (upper_pos > segment_start) {
            if (append_token(&tokens, &token_count, &capacity,
                             input + segment_start,
                             upper_pos - segment_start) != 0) {
                goto fail;
            }
        }
        segment_start = upper_pos;
        offset = upper_pos + 1;
    }

    if (input_length > segment_start) {
        if (append_token(&tokens, &token_count, &capacity,
                         input + segment_start,
                         input_length - segment_start) != 0) {
            goto fail;
        }
    }

    regfree(&regex);
    *tokens_out = tokens;
    *count_out = token_count;
    return 0;

fail:
    regfree(&regex);
    while (token_count > 0) {
        token_count--;
        free(tokens[token_count]);
    }
    free(tokens);
    return -1;
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
    const char *input = "HelloWorldThisIsATestString";
    char **tokens = NULL;
    size_t count = 0;
    size_t i;

    if (split_at_uppercase(input, &tokens, &count) != 0) {
        fprintf(stderr, "Failed to split string\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        printf("Token %zu: %s\n", i, tokens[i]);
    }

    free_tokens(tokens, count);
    return EXIT_SUCCESS;
}