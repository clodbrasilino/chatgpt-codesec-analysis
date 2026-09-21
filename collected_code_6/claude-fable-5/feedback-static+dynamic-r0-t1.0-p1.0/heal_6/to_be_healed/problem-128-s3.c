#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_WORD_LEN 4096

char **shortlist_words(const char *const *words, size_t count, size_t n, size_t *result_count);
void free_shortlist(char **list, size_t count);

char **shortlist_words(const char *const *words, size_t count, size_t n, size_t *result_count)
{
    char **result = NULL;
    size_t matched = 0;
    size_t i;

    if (words == NULL || result_count == NULL) {
        if (result_count != NULL) {
            *result_count = 0;
        }
        return NULL;
    }

    *result_count = 0;

    for (i = 0; i < count; i++) {
        if (words[i] != NULL) {
            size_t len = strnlen(words[i], MAX_WORD_LEN);
            if (len > n && len < MAX_WORD_LEN) {
                matched++;
            }
        }
    }

    if (matched == 0) {
        return NULL;
    }

    if (matched > SIZE_MAX / sizeof(char *)) {
        return NULL;
    }

    result = malloc(matched * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < count && *result_count < matched; i++) {
        if (words[i] != NULL) {
            size_t len = strnlen(words[i], MAX_WORD_LEN);
            if (len > n && len < MAX_WORD_LEN) {
                size_t copy_size;
                char *copy;

                if (len > SIZE_MAX - 1) {
                    size_t j;
                    for (j = 0; j < *result_count; j++) {
                        free(result[j]);
                    }
                    free(result);
                    *result_count = 0;
                    return NULL;
                }

                /* Possible weaknesses found:
                 *  copy_size is assigned 'len+1' here.
                 */
                copy_size = len + 1;
                copy = malloc(copy_size);

                /* Possible weaknesses found:
                 *  Assuming condition is false
                 */
                if (copy == NULL) {
                    size_t j;
                    for (j = 0; j < *result_count; j++) {
                        free(result[j]);
                    }
                    free(result);
                    *result_count = 0;
                    return NULL;
                }

                /* Possible weaknesses found:
                 *  Condition 'copy_size>len' is always true
                 *  Condition 'copy_size>len' is always true [knownConditionTrueFalse]
                 */
                if (copy_size > len) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(copy, words[i], len);
                    copy[len] = '\0';
                } else {
                    free(copy);
                    continue;
                }

                result[*result_count] = copy;
                (*result_count)++;
            }
        }
    }

    if (*result_count == 0) {
        free(result);
        return NULL;
    }

    return result;
}

void free_shortlist(char **list, size_t count)
{
    size_t i;

    if (list == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        free(list[i]);
    }
    free(list);
}

int main(void)
{
    const char *const words[] = {
        "apple", "cat", "banana", "dog", "elephant", "sun", "computer"
    };
    size_t word_count = sizeof(words) / sizeof(words[0]);
    size_t n = 4;
    size_t result_count = 0;
    char **shortlisted;
    size_t i;

    shortlisted = shortlist_words(words, word_count, n, &result_count);

    if (shortlisted == NULL) {
        if (printf("No words longer than %zu found.\n", n) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (printf("Words longer than %zu characters:\n", n) < 0) {
        free_shortlist(shortlisted, result_count);
        return EXIT_FAILURE;
    }

    for (i = 0; i < result_count; i++) {
        if (printf("%s\n", shortlisted[i]) < 0) {
            free_shortlist(shortlisted, result_count);
            return EXIT_FAILURE;
        }
    }

    free_shortlist(shortlisted, result_count);

    return EXIT_SUCCESS;
}