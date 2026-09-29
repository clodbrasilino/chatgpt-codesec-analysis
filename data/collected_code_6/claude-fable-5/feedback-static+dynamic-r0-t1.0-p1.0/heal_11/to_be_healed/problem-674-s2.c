#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_INPUT_LEN 65536U

static int is_separator(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

static size_t bounded_strlen(const char *s, size_t max)
{
    size_t n = 0U;

    while (n < max && s[n] != '\0') {
        n++;
    }
    return n;
}

static void cleanup(const char **seen, size_t *seen_lens, char *result)
{
    free((void *)seen);
    free(seen_lens);
    free(result);
}

char *remove_duplicate_words(const char *input)
{
    size_t len;
    size_t result_len;
    size_t result_cap;
    size_t pos;
    char *result;
    const char **seen;
    size_t *seen_lens;
    size_t seen_count;
    size_t seen_cap;

    if (input == NULL) {
        return NULL;
    }

    len = bounded_strlen(input, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        return NULL;
    }

    result_cap = len + 1U;
    result = malloc(result_cap);
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';
    result_len = 0U;

    seen = NULL;
    seen_lens = NULL;
    seen_count = 0U;
    seen_cap = 0U;
    pos = 0U;

    while (pos < len) {
        size_t start;
        size_t token_len;
        size_t i;
        int is_duplicate;

        while (pos < len && is_separator(input[pos])) {
            pos++;
        }
        if (pos >= len) {
            break;
        }

        start = pos;
        while (pos < len && !is_separator(input[pos])) {
            pos++;
        }
        token_len = pos - start;

        is_duplicate = 0;
        for (i = 0U; i < seen_count; i++) {
            if (seen_lens[i] == token_len &&
                memcmp(seen[i], input + start, token_len) == 0) {
                is_duplicate = 1;
                break;
            }
        }

        if (is_duplicate == 0) {
            if (seen_count == seen_cap) {
                size_t new_cap = (seen_cap == 0U) ? 8U : (seen_cap * 2U);
                const char **tmp;
                size_t *tmp_lens;

                if (new_cap > (SIZE_MAX / sizeof(const char *)) ||
                    new_cap > (SIZE_MAX / sizeof(size_t))) {
                    cleanup(seen, seen_lens, result);
                    return NULL;
                }
                tmp = realloc((void *)seen, new_cap * sizeof(const char *));
                if (tmp == NULL) {
                    cleanup(seen, seen_lens, result);
                    return NULL;
                }
                seen = tmp;
                tmp_lens = realloc(seen_lens, new_cap * sizeof(size_t));
                if (tmp_lens == NULL) {
                    cleanup(seen, seen_lens, result);
                    return NULL;
                }
                seen_lens = tmp_lens;
                seen_cap = new_cap;
            }
            seen[seen_count] = input + start;
            seen_lens[seen_count] = token_len;
            seen_count++;

            if (result_len > 0U) {
                if (result_len + 1U >= result_cap) {
                    cleanup(seen, seen_lens, result);
                    return NULL;
                }
                result[result_len] = ' ';
                result_len++;
            }

            if (token_len >= result_cap ||
                result_len > result_cap - 1U - token_len) {
                cleanup(seen, seen_lens, result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_len, input + start, token_len);
            result_len += token_len;
            result[result_len] = '\0';
        }
    }

    free((void *)seen);
    free(seen_lens);
    return result;
}

int main(void)
{
    char *buffer;
    char *deduplicated;
    size_t len;

    buffer = malloc(MAX_INPUT_LEN);
    if (buffer == NULL) {
        fprintf(stderr, "Error: memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (fgets(buffer, (int)MAX_INPUT_LEN, stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    len = bounded_strlen(buffer, MAX_INPUT_LEN);
    while (len > 0U && (buffer[len - 1U] == '\n' || buffer[len - 1U] == '\r')) {
        buffer[len - 1U] = '\0';
        len--;
    }

    deduplicated = remove_duplicate_words(buffer);
    if (deduplicated == NULL) {
        fprintf(stderr, "Error: failed to process the string\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    printf("%s\n", deduplicated);

    free(deduplicated);
    free(buffer);
    return EXIT_SUCCESS;
}