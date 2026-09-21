#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_INPUT_LEN 65536

static int word_seen(char **words, size_t count, const char *word)
{
    size_t i;
    for (i = 0; i < count; i++) {
        if (strcmp(words[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

static void free_words(char **words, size_t count)
{
    size_t i;
    for (i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
}

static char *duplicate_string(const char *src, size_t max_len)
{
    size_t len;
    char *dst;

    if (src == NULL) {
        return NULL;
    }

    len = strnlen(src, max_len);

    if (len == SIZE_MAX) {
        return NULL;
    }

    dst = malloc(len + 1);
    if (dst == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dst, src, len);
    dst[len] = '\0';
    return dst;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'Python Exercises Practice Solution', got <no output>
  *  test case 0 failed: expected 'Python Exercises Practice Solution', got <no output>
  *  test case 1 failed: expected 'Python Exercises Practice Solution', got <no output>
  */

char *remove_duplicate_words(const char *input)
{
    char *copy = NULL;
    char *result = NULL;
    char **seen = NULL;
    char **tmp_seen = NULL;
    char *token = NULL;
    char *saveptr = NULL;
    size_t seen_count = 0;
    size_t seen_capacity = 0;
    size_t result_len = 0;
    size_t input_len;
    size_t token_len;

    if (input == NULL) {
        return NULL;
    }

    input_len = strnlen(input, MAX_INPUT_LEN);
    if (input_len >= MAX_INPUT_LEN) {
        return NULL;
    }

    copy = malloc(input_len + 1);
    if (copy == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, input, input_len);
    copy[input_len] = '\0';

    result = malloc(input_len + 1);
    if (result == NULL) {
        free(copy);
        return NULL;
    }
    result[0] = '\0';

    token = strtok_r(copy, " \t\n", &saveptr);
    while (token != NULL) {
        if (!word_seen(seen, seen_count, token)) {
            if (seen_count == seen_capacity) {
                size_t new_capacity = (seen_capacity == 0) ? 8 : seen_capacity * 2;
                if (new_capacity > SIZE_MAX / sizeof(char *)) {
                    free_words(seen, seen_count);
                    free(copy);
                    free(result);
                    return NULL;
                }
                tmp_seen = realloc(seen, new_capacity * sizeof(char *));
                if (tmp_seen == NULL) {
                    free_words(seen, seen_count);
                    free(copy);
                    free(result);
                    return NULL;
                }
                seen = tmp_seen;
                seen_capacity = new_capacity;
            }

            seen[seen_count] = duplicate_string(token, input_len);
            if (seen[seen_count] == NULL) {
                free_words(seen, seen_count);
                free(copy);
                free(result);
                return NULL;
            }
            seen_count++;

            token_len = strnlen(token, input_len);

            if (result_len > 0) {
                if (result_len + 1 > input_len) {
                    free_words(seen, seen_count);
                    free(copy);
                    free(result);
                    return NULL;
                }
                result[result_len] = ' ';
                result_len++;
                result[result_len] = '\0';
            }

            if (token_len > input_len || result_len > input_len - token_len) {
                free_words(seen, seen_count);
                free(copy);
                free(result);
                return NULL;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_len, token, token_len);
            result_len += token_len;
            result[result_len] = '\0';
        }
        token = strtok_r(NULL, " \t\n", &saveptr);
    }

    free_words(seen, seen_count);
    free(copy);

    return result;
}

int main(void)
{
    char *line = NULL;
    char *deduplicated = NULL;
    size_t len;

    line = malloc(MAX_INPUT_LEN);
    if (line == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (fgets(line, MAX_INPUT_LEN, stdin) == NULL) {
        free(line);
        fprintf(stderr, "Failed to read input\n");
        return EXIT_FAILURE;
    }

    len = strnlen(line, MAX_INPUT_LEN);
    if (len > 0 && line[len - 1] == '\n') {
        line[len - 1] = '\0';
    }

    deduplicated = remove_duplicate_words(line);
    free(line);

    if (deduplicated == NULL) {
        fprintf(stderr, "Failed to process the string\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", deduplicated);

    free(deduplicated);

    return EXIT_SUCCESS;
}