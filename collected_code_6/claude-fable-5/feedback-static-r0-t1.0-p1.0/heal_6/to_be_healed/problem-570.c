#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_WORD_LEN 4096

char **remove_words(const char **words, size_t count, const char *pattern, size_t *out_count);
void free_word_list(char **list, size_t count);
static char *duplicate_word(const char *word);

static char *duplicate_word(const char *word)
{
    size_t len;
    size_t dest_size;
    char *copy;

    if (word == NULL) {
        return NULL;
    }

    len = strnlen(word, MAX_WORD_LEN);
    if (len >= MAX_WORD_LEN) {
        len = MAX_WORD_LEN - 1;
    }

    if (len > SIZE_MAX - 1) {
        return NULL;
    }

    dest_size = len + 1;
    copy = malloc(dest_size);
    if (copy == NULL) {
        return NULL;
    }

    if (len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, word, len);
    }
    copy[len] = '\0';

    return copy;
}

char **remove_words(const char **words, size_t count, const char *pattern, size_t *out_count)
{
    char **result = NULL;
    size_t kept = 0;
    size_t i;

    if (words == NULL || pattern == NULL || out_count == NULL) {
        return NULL;
    }

    *out_count = 0;

    if (count == 0) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(char *)) {
        return NULL;
    }

    result = calloc(count, sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        if (words[i] == NULL) {
            continue;
        }
        if (strstr(words[i], pattern) == NULL) {
            char *copy = duplicate_word(words[i]);
            if (copy == NULL) {
                free_word_list(result, kept);
                return NULL;
            }
            result[kept] = copy;
            kept++;
        }
    }

    *out_count = kept;
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
    const char *words[] = { "apple", "banana", "cherry", "grape", "apricot" };
    size_t count = sizeof(words) / sizeof(words[0]);
    const char *pattern = "ap";
    size_t result_count = 0;
    char **filtered;
    size_t i;

    filtered = remove_words(words, count, pattern, &result_count);
    if (filtered == NULL) {
        fprintf(stderr, "Failed to filter word list\n");
        return EXIT_FAILURE;
    }

    printf("Words not containing \"%s\":\n", pattern);
    for (i = 0; i < result_count; i++) {
        printf("%s\n", filtered[i]);
    }

    free_word_list(filtered, result_count);

    return EXIT_SUCCESS;
}