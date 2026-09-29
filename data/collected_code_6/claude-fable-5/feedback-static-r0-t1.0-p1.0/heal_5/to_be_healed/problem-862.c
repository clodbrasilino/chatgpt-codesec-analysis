#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_WORD_LEN 64

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LEN];
    size_t count;
} WordEntry;

typedef struct {
    WordEntry *entries;
    size_t size;
    size_t capacity;
} WordList;

static int word_list_init(WordList *list)
{
    if (list == NULL) {
        return -1;
    }
    list->size = 0;
    list->capacity = 16;
    list->entries = calloc(list->capacity, sizeof(WordEntry));
    if (list->entries == NULL) {
        list->capacity = 0;
        return -1;
    }
    return 0;
}

static void word_list_free(WordList *list)
{
    if (list != NULL) {
        free(list->entries);
        list->entries = NULL;
        list->size = 0;
        list->capacity = 0;
    }
}

static int word_list_grow(WordList *list)
{
    size_t new_capacity;
    WordEntry *tmp;

    if (list == NULL || list->capacity == 0) {
        return -1;
    }
    if (list->capacity > SIZE_MAX / (2 * sizeof(WordEntry))) {
        return -1;
    }
    new_capacity = list->capacity * 2;
    tmp = realloc(list->entries, new_capacity * sizeof(WordEntry));
    if (tmp == NULL) {
        return -1;
    }
    memset(tmp + list->capacity, 0,
           (new_capacity - list->capacity) * sizeof(WordEntry));
    list->entries = tmp;
    list->capacity = new_capacity;
    return 0;
}

static int word_list_add(WordList *list, const char *word, size_t word_len)
{
    size_t i;
    WordEntry *entry;

    if (list == NULL || word == NULL || word_len == 0) {
        return -1;
    }

    if (word_len >= MAX_WORD_LEN) {
        word_len = MAX_WORD_LEN - 1;
    }

    for (i = 0; i < list->size; i++) {
        if (strncmp(list->entries[i].word, word, MAX_WORD_LEN - 1) == 0 &&
            list->entries[i].word[word_len] == '\0' &&
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            strlen(list->entries[i].word) == word_len) {
            if (list->entries[i].count == SIZE_MAX) {
                return -1;
            }
            list->entries[i].count++;
            return 0;
        }
    }

    if (list->size == list->capacity) {
        if (word_list_grow(list) != 0) {
            return -1;
        }
    }

    entry = &list->entries[list->size];
    memset(entry->word, 0, sizeof(entry->word));
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(entry->word, word, word_len);
    entry->word[word_len] = '\0';
    entry->count = 1;
    list->size++;
    return 0;
}

static int compare_entries(const void *a, const void *b)
{
    const WordEntry *ea = (const WordEntry *)a;
    const WordEntry *eb = (const WordEntry *)b;

    if (eb->count > ea->count) {
        return 1;
    }
    if (eb->count < ea->count) {
        return -1;
    }
    return strncmp(ea->word, eb->word, MAX_WORD_LEN);
}

static int tokenize_and_count(const char *text, WordList *list)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_WORD_LEN];
    size_t buf_index = 0;
    size_t i = 0;

    if (text == NULL || list == NULL) {
        return -1;
    }

    memset(buffer, 0, sizeof(buffer));

    while (text[i] != '\0') {
        unsigned char c = (unsigned char)text[i];
        if (isalpha(c)) {
            if (buf_index < sizeof(buffer) - 1) {
                buffer[buf_index] = (char)tolower(c);
                buf_index++;
            }
        } else if (buf_index > 0) {
            buffer[buf_index] = '\0';
            if (word_list_add(list, buffer, buf_index) != 0) {
                return -1;
            }
            buf_index = 0;
            memset(buffer, 0, sizeof(buffer));
        }
        i++;
    }

    if (buf_index > 0) {
        buffer[buf_index] = '\0';
        if (word_list_add(list, buffer, buf_index) != 0) {
            return -1;
        }
    }

    return 0;
}

int print_most_common_words(const char *text, size_t n)
{
    WordList list;
    size_t i;
    size_t limit;

    if (text == NULL || n == 0) {
        return -1;
    }

    if (word_list_init(&list) != 0) {
        return -1;
    }

    if (tokenize_and_count(text, &list) != 0) {
        word_list_free(&list);
        return -1;
    }

    if (list.size == 0) {
        word_list_free(&list);
        return 0;
    }

    qsort(list.entries, list.size, sizeof(WordEntry), compare_entries);

    limit = (n < list.size) ? n : list.size;
    for (i = 0; i < limit; i++) {
        if (printf("%s: %zu\n", list.entries[i].word,
                   list.entries[i].count) < 0) {
            word_list_free(&list);
            return -1;
        }
    }

    word_list_free(&list);
    return 0;
}

int main(void)
{
    const char *text = "The quick brown fox jumps over the lazy dog. "
                       "The dog barks and the fox runs. The quick fox "
                       "is quick and the dog is lazy.";
    size_t n = 5;

    if (print_most_common_words(text, n) != 0) {
        fprintf(stderr, "Error processing text\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}