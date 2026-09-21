#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_WORD_LEN 64

typedef struct {
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
    list->entries = malloc(list->capacity * sizeof(WordEntry));
    if (list->entries == NULL) {
        list->capacity = 0;
        return -1;
    }
    return 0;
}

static void word_list_free(WordList *list)
{
    if (list == NULL) {
        return;
    }
    free(list->entries);
    list->entries = NULL;
    list->size = 0;
    list->capacity = 0;
}

static int word_list_grow(WordList *list)
{
    size_t new_capacity;
    WordEntry *tmp;

    if (list->capacity > SIZE_MAX / 2) {
        return -1;
    }
    new_capacity = list->capacity * 2;
    if (new_capacity > SIZE_MAX / sizeof(WordEntry)) {
        return -1;
    }
    tmp = realloc(list->entries, new_capacity * sizeof(WordEntry));
    if (tmp == NULL) {
        return -1;
    }
    list->entries = tmp;
    list->capacity = new_capacity;
    return 0;
}

static int word_list_add(WordList *list, const char *word)
{
    size_t i;
    size_t word_len;

    if (list == NULL || word == NULL) {
        return -1;
    }

    word_len = strlen(word);
    if (word_len == 0 || word_len >= MAX_WORD_LEN) {
        return -1;
    }

    for (i = 0; i < list->size; i++) {
        if (strcmp(list->entries[i].word, word) == 0) {
            list->entries[i].count++;
            return 0;
        }
    }

    if (list->size == list->capacity) {
        if (word_list_grow(list) != 0) {
            return -1;
        }
    }

    memcpy(list->entries[list->size].word, word, word_len);
    list->entries[list->size].word[word_len] = '\0';
    list->entries[list->size].count = 1;
    list->size++;
    return 0;
}

static int compare_entries(const void *a, const void *b)
{
    const WordEntry *ea = a;
    const WordEntry *eb = b;

    if (eb->count > ea->count) {
        return 1;
    }
    if (eb->count < ea->count) {
        return -1;
    }
    return strcmp(ea->word, eb->word);
}

static int flush_word(WordList *list, char *buffer, size_t *buf_len)
{
    if (*buf_len > 0) {
        buffer[*buf_len] = '\0';
        if (word_list_add(list, buffer) != 0) {
            return -1;
        }
        *buf_len = 0;
    }
    return 0;
}

static int count_words(const char *text, WordList *list)
{
    char buffer[MAX_WORD_LEN];
    size_t buf_len = 0;
    size_t i = 0;

    if (text == NULL || list == NULL) {
        return -1;
    }

    while (text[i] != '\0') {
        unsigned char c = (unsigned char)text[i];
        if (isalpha(c)) {
            if (buf_len < MAX_WORD_LEN - 1) {
                buffer[buf_len] = (char)tolower(c);
                buf_len++;
            }
        } else {
            if (flush_word(list, buffer, &buf_len) != 0) {
                return -1;
            }
        }
        i++;
    }

    if (flush_word(list, buffer, &buf_len) != 0) {
        return -1;
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

    if (count_words(text, &list) != 0) {
        word_list_free(&list);
        return -1;
    }

    if (list.size > 0) {
        qsort(list.entries, list.size, sizeof(WordEntry), compare_entries);
    }

    limit = (n < list.size) ? n : list.size;
    for (i = 0; i < limit; i++) {
        if (printf("%s: %zu\n", list.entries[i].word, list.entries[i].count) < 0) {
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
                       "The dog barks and the fox runs. "
                       "A quick response from the dog surprised the fox.";
    size_t n = 5;

    if (print_most_common_words(text, n) != 0) {
        fprintf(stderr, "Error processing text\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}