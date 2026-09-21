#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *word;
    size_t len;
} word_entry;

static void free_word_entries(word_entry *entries, size_t count)
{
    if (entries == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(entries[i].word);
    }
    free(entries);
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Python Exercises Practice Solution', got <no output>
  *  test case 0 failed: expected 'Python Exercises Practice Solution', got <no output>
  *  test case 2 failed: expected 'Python Exercises Practice Solution', got <no output>
  */

char *remove_duplicate_words(const char *input)
{
    if (input == NULL) {
        return NULL;
    }

    size_t capacity = 8;
    size_t count = 0;
    word_entry *entries = malloc(capacity * sizeof(*entries));
    if (entries == NULL) {
        return NULL;
    }

    const char *p = input;

    while (*p != '\0') {
        while (isspace((unsigned char)*p)) {
            p++;
        }
        if (*p == '\0') {
            break;
        }

        const char *start = p;
        while (*p != '\0' && !isspace((unsigned char)*p)) {
            p++;
        }
        size_t len = (size_t)(p - start);

        int duplicate = 0;
        for (size_t i = 0; i < count; i++) {
            if (entries[i].len == len && memcmp(entries[i].word, start, len) == 0) {
                duplicate = 1;
                break;
            }
        }
        if (duplicate) {
            continue;
        }

        char *word = malloc(len + 1);
        if (word == NULL) {
            free_word_entries(entries, count);
            return NULL;
        }
        for (size_t i = 0; i < len; i++) {
            word[i] = start[i];
        }
        word[len] = '\0';

        if (count == capacity) {
            if (capacity > (size_t)-1 / 2) {
                free(word);
                free_word_entries(entries, count);
                return NULL;
            }
            size_t new_capacity = capacity * 2;
            word_entry *new_entries = realloc(entries, new_capacity * sizeof(*entries));
            if (new_entries == NULL) {
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
        if (i > 0) {
            result_len += 1;
        }
    }

    char *result = malloc(result_len);
    if (result == NULL) {
        free_word_entries(entries, count);
        return NULL;
    }

    size_t pos = 0;
    for (size_t i = 0; i < count; i++) {
        if (i > 0) {
            result[pos] = ' ';
            pos++;
        }
        for (size_t j = 0; j < entries[i].len; j++) {
            result[pos + j] = entries[i].word[j];
        }
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
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    printf("%s\n", result);
    free(result);
    return EXIT_SUCCESS;
}