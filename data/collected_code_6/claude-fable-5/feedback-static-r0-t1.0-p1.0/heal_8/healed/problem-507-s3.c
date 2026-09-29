#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_WORD_LEN 4096

char **remove_words(char **words, size_t count, char **targets, size_t target_count, size_t *new_count);
void free_word_list(char **list, size_t count);
static void cleanup_partial(char **result, size_t kept);
static char *safe_duplicate(const char *src, size_t src_len);

static void cleanup_partial(char **result, size_t kept)
{
    while (kept > 0) {
        kept--;
        free(result[kept]);
    }
    free(result);
}

static char *safe_duplicate(const char *src, size_t src_len)
{
    char *dst;
    size_t alloc_len;

    if (src == NULL) {
        return NULL;
    }

    if (src_len >= MAX_WORD_LEN) {
        return NULL;
    }

    if (src_len > SIZE_MAX - 1) {
        return NULL;
    }

    alloc_len = src_len + 1;

    dst = malloc(alloc_len);
    if (dst == NULL) {
        return NULL;
    }

    if (src_len > 0) {
        if (src_len >= alloc_len) {
            free(dst);
            return NULL;
        }
        memcpy(dst, src, src_len);
    }
    dst[src_len] = '\0';

    return dst;
}

char **remove_words(char **words, size_t count, char **targets, size_t target_count, size_t *new_count)
{
    char **result;
    size_t i;
    size_t j;
    size_t kept;
    int match;

    if (words == NULL || new_count == NULL) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(char *)) {
        return NULL;
    }

    result = malloc(sizeof(char *) * (count > 0 ? count : 1));
    if (result == NULL) {
        return NULL;
    }

    kept = 0;
    for (i = 0; i < count; i++) {
        size_t word_len;

        if (words[i] == NULL) {
            continue;
        }

        word_len = strnlen(words[i], MAX_WORD_LEN);
        if (word_len >= MAX_WORD_LEN) {
            cleanup_partial(result, kept);
            return NULL;
        }

        match = 0;
        for (j = 0; j < target_count; j++) {
            if (targets != NULL && targets[j] != NULL &&
                strnlen(targets[j], MAX_WORD_LEN) < MAX_WORD_LEN &&
                strcmp(words[i], targets[j]) == 0) {
                match = 1;
                break;
            }
        }

        if (match == 0) {
            if (kept >= count) {
                cleanup_partial(result, kept);
                return NULL;
            }

            result[kept] = safe_duplicate(words[i], word_len);
            if (result[kept] == NULL) {
                cleanup_partial(result, kept);
                return NULL;
            }
            kept++;
        }
    }

    *new_count = kept;
    return result;
}

void free_word_list(char **list, size_t count)
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
    char *words[] = { "apple", "banana", "cherry", "date", "banana", "fig" };
    char *targets[] = { "banana", "date" };
    size_t word_count = sizeof(words) / sizeof(words[0]);
    size_t target_count = sizeof(targets) / sizeof(targets[0]);
    size_t new_count = 0;
    size_t i;
    char **filtered;

    filtered = remove_words(words, word_count, targets, target_count, &new_count);
    if (filtered == NULL) {
        fprintf(stderr, "Failed to remove words\n");
        return EXIT_FAILURE;
    }

    printf("Remaining words:\n");
    for (i = 0; i < new_count; i++) {
        printf("%s\n", filtered[i]);
    }

    free_word_list(filtered, new_count);
    return EXIT_SUCCESS;
}