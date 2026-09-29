#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_WORD_LENGTH 4096

static size_t bounded_strlen(const char *s, size_t max_len)
{
    size_t len = 0;

    if (s == NULL) {
        return 0;
    }

    while (len < max_len && s[len] != '\0') {
        len++;
    }

    return len;
}

char **shortlist_words(const char *const *words, size_t count, size_t n, size_t *result_count)
{
    char **result;
    size_t i;
    size_t j = 0;

    if (result_count == NULL) {
        return NULL;
    }
    *result_count = 0;

    if (words == NULL || count == 0) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(char *)) {
        return NULL;
    }

    result = malloc(count * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        if (words[i] != NULL) {
            size_t len = bounded_strlen(words[i], MAX_WORD_LENGTH);
            size_t alloc_size;

            if (len == MAX_WORD_LENGTH || len <= n) {
                continue;
            }

            /* Possible weaknesses found:
             *  alloc_size is assigned 'len+1' here.
             */
            alloc_size = len + 1;

            result[j] = malloc(alloc_size);
            /* Possible weaknesses found:
             *  Assuming condition is false
             */
            if (result[j] == NULL) {
                size_t k;
                for (k = 0; k < j; k++) {
                    free(result[k]);
                }
                free(result);
                return NULL;
            }

            /* Possible weaknesses found:
             *  Condition 'len<alloc_size' is always true
             *  Condition 'len<alloc_size' is always true [knownConditionTrueFalse]
             */
            if (len < alloc_size) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result[j], words[i], len);
                result[j][len] = '\0';
            } else {
                result[j][0] = '\0';
            }
            j++;
        }
    }

    *result_count = j;
    return result;
}

void free_words(char **words, size_t count)
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

int main(void)
{
    const char *words[] = {"apple", "hi", "banana", "cat", "strawberry", "dog"};
    const size_t count = sizeof(words) / sizeof(words[0]);
    const size_t n = 3;
    size_t result_count = 0;
    char **result;
    size_t i;

    result = shortlist_words(words, count, n, &result_count);
    if (result == NULL) {
        fprintf(stderr, "Error: failed to shortlist words\n");
        return EXIT_FAILURE;
    }

    printf("Words longer than %zu characters:\n", n);
    for (i = 0; i < result_count; i++) {
        printf("%s\n", result[i]);
    }

    free_words(result, result_count);

    return EXIT_SUCCESS;
}