#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_len = strlen(input);

    copy = malloc(input_len + 1);
    if (copy == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, input, input_len + 1);

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

            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            seen[seen_count] = malloc(strlen(token) + 1);
            if (seen[seen_count] == NULL) {
                free_words(seen, seen_count);
                free(copy);
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            memcpy(seen[seen_count], token, strlen(token) + 1);
            seen_count++;

            if (result_len > 0) {
                result[result_len] = ' ';
                result_len++;
                result[result_len] = '\0';
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            memcpy(result + result_len, token, strlen(token) + 1);
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            result_len += strlen(token);
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