#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_INPUT_LEN 65536U

static void cleanup(char **seen, char *copy, char *result)
{
    free(seen);
    free(copy);
    free(result);
}

char *remove_duplicate_words(const char *input)
{
    size_t len;
    size_t result_len;
    size_t copy_size;
    char *copy;
    char *result;
    char **seen;
    size_t seen_count;
    size_t seen_cap;
    char *token;
    char *saveptr;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        return NULL;
    }

    copy_size = len + 1U;

    copy = malloc(copy_size);
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, input, copy_size - 1U);
    copy[copy_size - 1U] = '\0';

    result = malloc(copy_size);
    if (result == NULL) {
        free(copy);
        return NULL;
    }
    result[0] = '\0';
    result_len = 0U;

    seen = NULL;
    seen_count = 0U;
    seen_cap = 0U;
    saveptr = NULL;

    token = strtok_r(copy, " \t\n", &saveptr);
    while (token != NULL) {
        int is_duplicate = 0;
        size_t i;

        for (i = 0U; i < seen_count; i++) {
            if (strcmp(seen[i], token) == 0) {
                is_duplicate = 1;
                break;
            }
        }

        if (is_duplicate == 0) {
            size_t token_len;

            if (seen_count == seen_cap) {
                size_t new_cap = (seen_cap == 0U) ? 8U : (seen_cap * 2U);
                char **tmp;

                if (new_cap > SIZE_MAX / sizeof(char *)) {
                    cleanup(seen, copy, result);
                    return NULL;
                }
                tmp = realloc(seen, new_cap * sizeof(char *));
                if (tmp == NULL) {
                    cleanup(seen, copy, result);
                    return NULL;
                }
                seen = tmp;
                seen_cap = new_cap;
            }
            seen[seen_count] = token;
            seen_count++;

            token_len = strnlen(token, copy_size);
            if (token_len > len) {
                cleanup(seen, copy, result);
                return NULL;
            }

            if (result_len > 0U) {
                if (result_len >= len) {
                    cleanup(seen, copy, result);
                    return NULL;
                }
                result[result_len] = ' ';
                result_len++;
            }

            if (result_len > len || token_len > len - result_len) {
                cleanup(seen, copy, result);
                return NULL;
            }
            memcpy(result + result_len, token, token_len);
            result_len += token_len;
            result[result_len] = '\0';
        }

        token = strtok_r(NULL, " \t\n", &saveptr);
    }

    free(seen);
    free(copy);
    return result;
}

int main(void)
{
    const char *text = "the quick brown fox jumps over the lazy dog the quick fox";
    char *deduplicated;

    deduplicated = remove_duplicate_words(text);
    if (deduplicated == NULL) {
        fprintf(stderr, "Error: failed to process the string\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", text);
    printf("Result:   %s\n", deduplicated);

    free(deduplicated);
    return EXIT_SUCCESS;
}