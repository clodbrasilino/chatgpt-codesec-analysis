#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char **shortlist_words(const char *const *words, size_t count, size_t n, size_t *out_count)
{
    char **result = NULL;
    size_t i;
    size_t j = 0;

    if (out_count == NULL) {
        return NULL;
    }
    *out_count = 0;

    if (count == 0) {
        return NULL;
    }

    if (words == NULL) {
        return NULL;
    }

    result = malloc(count * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        size_t len;

        if (words[i] == NULL) {
            continue;
        }

        len = strlen(words[i]);
        if (len > n) {
            result[j] = malloc(len + 1);
            if (result[j] == NULL) {
                size_t k;
                for (k = 0; k < j; k++) {
                    free(result[k]);
                }
                free(result);
                return NULL;
            }
            memcpy(result[j], words[i], len + 1);
            j++;
        }
    }

    *out_count = j;
    return result;
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

int main(void)
{
    const char *word_list[] = {
        "apple", "hi", "banana", "cat", "strawberry", "dog", "elephant"
    };
    const size_t word_count = sizeof(word_list) / sizeof(word_list[0]);
    const size_t n = 4;
    size_t shortlist_count = 0;
    char **shortlisted = NULL;
    size_t i;

    shortlisted = shortlist_words(word_list, word_count, n, &shortlist_count);
    if (shortlisted == NULL) {
        fprintf(stderr, "Error: unable to shortlist words\n");
        return EXIT_FAILURE;
    }

    printf("Words longer than %zu characters:\n", n);
    for (i = 0; i < shortlist_count; i++) {
        printf("%s\n", shortlisted[i]);
    }

    free_words(shortlisted, shortlist_count);
    shortlisted = NULL;

    return EXIT_SUCCESS;
}