#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_INPUT_LEN 65536

static size_t bounded_strlen(const char *s, size_t max_len)
{
    size_t i = 0;
    while (i < max_len && s[i] != '\0') {
        i++;
    }
    return i;
}

static int is_separator(char c)
{
    return c == ' ' || c == '\t' || c == '\n';
}

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

static char *duplicate_string(const char *src, size_t len)
{
    char *dst;

    if (src == NULL) {
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
    char *result = NULL;
    char **seen = NULL;
    char **tmp_seen = NULL;
    char *word = NULL;
    size_t seen_count = 0;
    size_t seen_capacity = 0;
    size_t result_len = 0;
    size_t input_len;
    size_t pos = 0;

    if (input == NULL) {
        return NULL;
    }

    input_len = bounded_strlen(input, MAX_INPUT_LEN);
    if (input_len >= MAX_INPUT_LEN) {
        return NULL;
    }

    result = malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';

    while (pos < input_len) {
        size_t start;
        size_t token_len;

        while (pos < input_len && is_separator(input[pos])) {
            pos++;
        }
        if (pos >= input_len) {
            break;
        }

        start = pos;
        while (pos < input_len && !is_separator(input[pos])) {
            pos++;
        }
        token_len = pos - start;

        word = duplicate_string(input + start, token_len);
        if (word == NULL) {
            free_words(seen, seen_count);
            free(result);
            return NULL;
        }

        if (word_seen(seen, seen_count, word)) {
            free(word);
            continue;
        }

        if (seen_count == seen_capacity) {
            size_t new_capacity = (seen_capacity == 0) ? 8 : seen_capacity * 2;
            if (new_capacity > SIZE_MAX / sizeof(char *)) {
                free(word);
                free_words(seen, seen_count);
                free(result);
                return NULL;
            }
            tmp_seen = realloc(seen, new_capacity * sizeof(char *));
            if (tmp_seen == NULL) {
                free(word);
                free_words(seen, seen_count);
                free(result);
                return NULL;
            }
            seen = tmp_seen;
            seen_capacity = new_capacity;
        }

        seen[seen_count] = word;
        seen_count++;
        word = NULL;

        if (result_len > 0) {
            if (result_len + 1 > input_len) {
                free_words(seen, seen_count);
                free(result);
                return NULL;
            }
            result[result_len] = ' ';
            result_len++;
            result[result_len] = '\0';
        }

        if (token_len > input_len || result_len > input_len - token_len) {
            free_words(seen, seen_count);
            free(result);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + result_len, input + start, token_len);
        result_len += token_len;
        result[result_len] = '\0';
    }

    free_words(seen, seen_count);

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

    len = bounded_strlen(line, MAX_INPUT_LEN);
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