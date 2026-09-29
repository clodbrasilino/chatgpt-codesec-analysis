#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *word;
    size_t len;
} word_entry;

static void free_word_entries(word_entry *entries, size_t count)
{
    if (entries == NULL) return;
    for (size_t i = 0; i < count; i++) free(entries[i].word);
    free(entries);
}

char *remove_duplicate_words(const char *input)
{
    if (input == NULL) return NULL;

    size_t capacity = 8;
    size_t count = 0;
    word_entry *entries = malloc(capacity * sizeof(*entries));
    if (!entries) return NULL;

    const char *p = input;
    while (*p) {
        while (isspace((unsigned char)*p)) p++;
        if (*p == '\0') break;
        const char *start = p;
        while (*p && !isspace((unsigned char)*p)) p++;
        size_t len = (size_t)(p - start);

        int duplicate = 0;
        for (size_t i = 0; i < count; i++) {
            if (entries[i].len == len && memcmp(entries[i].word, start, len) == 0) {
                duplicate = 1;
                break;
            }
        }
        if (duplicate) continue;

        char *word = malloc(len + 1);
        if (!word) {
            free_word_entries(entries, count);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(word, start, len);
        word[len] = '\0';

        if (count == capacity) {
            if (capacity > SIZE_MAX / (2 * sizeof(word_entry))) {
                free(word);
                free_word_entries(entries, count);
                return NULL;
            }
            size_t new_capacity = capacity * 2;
            word_entry *new_entries = realloc(entries, new_capacity * sizeof(*entries));
            if (!new_entries) {
                free(word);
                free_word_entries(entries, count);
                return NULL;
            }
            entries = new_entries;
            capacity = new_capacity;
        }

        entries[count].word = word;
        entries[count].len = len;
        count++;
    }

    size_t result_len = 1;
    for (size_t i = 0; i < count; i++) {
        result_len += entries[i].len;
        if (i > 0) result_len += 1;
    }

    char *result = malloc(result_len);
    if (!result) {
        free_word_entries(entries, count);
        return NULL;
    }

    size_t pos = 0;
    for (size_t i = 0; i < count; i++) {
        if (i > 0) result[pos++] = ' ';
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + pos, entries[i].word, entries[i].len);
        pos += entries[i].len;
    }
    result[pos] = '\0';

    free_word_entries(entries, count);
    return result;
}

int main(void)
{
    const char text[] = "apple banana apple cherry banana";
    char *result = remove_duplicate_words(text);
    if (!result) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    printf("%s\n", result);
    free(result);
    return EXIT_SUCCESS;
}