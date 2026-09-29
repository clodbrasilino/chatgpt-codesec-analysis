#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_INPUT_LEN 4096

static int word_seen(char **words, size_t count, const char *word);
static void free_words(char **words, size_t count);
static char *duplicate_string(const char *src, size_t len);
static int append_to_buffer(char *dst, size_t dst_capacity, size_t *dst_len,
                            const char *src, size_t src_len);
char *remove_duplicate_words(const char *input);

static int word_seen(char **words, size_t count, const char *word)
{
    size_t i;

    if (words == NULL || word == NULL) {
        return 0;
    }

    for (i = 0; i < count; i++) {
        if (words[i] != NULL && strcmp(words[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

static void free_words(char **words, size_t count)
{
    size_t i;

    if (words == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
}

static char *duplicate_string(const char *src, size_t len)
{
    char *dst;
    size_t alloc_size;

    if (src == NULL) {
        return NULL;
    }

    if (len >= SIZE_MAX) {
        return NULL;
    }

    alloc_size = len + 1;

    dst = malloc(alloc_size);
    if (dst == NULL) {
        return NULL;
    }

    if (strnlen(src, len) < len) {
        free(dst);
        return NULL;
    }

    if (len > alloc_size - 1) {
        free(dst);
        return NULL;
    }

    memcpy(dst, src, len);
    dst[len] = '\0';

    return dst;
}

static int append_to_buffer(char *dst, size_t dst_capacity, size_t *dst_len,
                            const char *src, size_t src_len)
{
    if (dst == NULL || dst_len == NULL || src == NULL) {
        return -1;
    }

    if (*dst_len > dst_capacity) {
        return -1;
    }

    if (src_len > dst_capacity - *dst_len) {
        return -1;
    }

    if (strnlen(src, src_len) < src_len) {
        return -1;
    }

    memcpy(dst + *dst_len, src, src_len);
    *dst_len += src_len;
    dst[*dst_len] = '\0';

    return 0;
}

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

    copy = duplicate_string(input, input_len);
    if (copy == NULL) {
        return NULL;
    }

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

            token_len = strnlen(token, input_len);

            seen[seen_count] = duplicate_string(token, token_len);
            if (seen[seen_count] == NULL) {
                free_words(seen, seen_count);
                free(copy);
                free(result);
                return NULL;
            }
            seen_count++;

            if (result_len > 0) {
                if (append_to_buffer(result, input_len, &result_len, " ", 1) != 0) {
                    free_words(seen, seen_count);
                    free(copy);
                    free(result);
                    return NULL;
                }
            }

            if (append_to_buffer(result, input_len, &result_len, token, token_len) != 0) {
                free_words(seen, seen_count);
                free(copy);
                free(result);
                return NULL;
            }
        }
        token = strtok_r(NULL, " \t\n", &saveptr);
    }

    free_words(seen, seen_count);
    free(copy);

    return result;
}

int main(void)
{
    const char *text = "the quick brown fox the lazy dog quick brown";
    char *deduplicated = NULL;

    deduplicated = remove_duplicate_words(text);
    if (deduplicated == NULL) {
        fprintf(stderr, "Failed to process the string\n");
        return EXIT_FAILURE;
    }

    printf("Original:  %s\n", text);
    printf("Result:    %s\n", deduplicated);

    free(deduplicated);

    return EXIT_SUCCESS;
}