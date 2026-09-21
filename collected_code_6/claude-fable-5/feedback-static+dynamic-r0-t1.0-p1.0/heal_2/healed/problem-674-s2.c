#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_INPUT_LEN 65536U

char *remove_duplicate_words(const char *input)
{
    size_t len;
    size_t result_len;
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

    copy = malloc(len + 1U);
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, input, len);
    copy[len] = '\0';

    result = malloc(len + 1U);
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

                if (new_cap > (SIZE_MAX / sizeof(char *))) {
                    free(seen);
                    free(copy);
                    free(result);
                    return NULL;
                }
                tmp = realloc(seen, new_cap * sizeof(char *));
                if (tmp == NULL) {
                    free(seen);
                    free(copy);
                    free(result);
                    return NULL;
                }
                seen = tmp;
                seen_cap = new_cap;
            }
            seen[seen_count] = token;
            seen_count++;

            token_len = strnlen(token, len);

            if (result_len > 0U) {
                if (result_len + 1U > len) {
                    free(seen);
                    free(copy);
                    free(result);
                    return NULL;
                }
                result[result_len] = ' ';
                result_len++;
            }

            if (result_len + token_len > len) {
                free(seen);
                free(copy);
                free(result);
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
    char buffer[MAX_INPUT_LEN];
    char *deduplicated;
    size_t len;

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input\n");
        return EXIT_FAILURE;
    }

    len = strnlen(buffer, sizeof(buffer));
    if (len > 0U && buffer[len - 1U] == '\n') {
        buffer[len - 1U] = '\0';
    }

    deduplicated = remove_duplicate_words(buffer);
    if (deduplicated == NULL) {
        fprintf(stderr, "Error: failed to process the string\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", deduplicated);

    free(deduplicated);
    return EXIT_SUCCESS;
}