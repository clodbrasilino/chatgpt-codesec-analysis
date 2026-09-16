#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 10000
#define MAX_WORD_LEN 100

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordCount;

typedef struct {
    WordCount *items;
    int size;
    int capacity;
} WordCountList;

static void init_word_list(WordCountList *list, int capacity) {
    list->items = (WordCount *)malloc((size_t)capacity * sizeof(WordCount));
    if (list->items == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    list->size = 0;
    list->capacity = capacity;
}

static void free_word_list(WordCountList *list) {
    free(list->items);
    list->items = NULL;
    list->size = 0;
    list->capacity = 0;
}

static void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = (char)tolower((unsigned char)str[i]);
    }
}

static int find_word(WordCountList *list, const char *word) {
    for (int i = 0; i < list->size; i++) {
        if (strcmp(list->items[i].word, word) == 0) {
            return i;
        }
    }
    return -1;
}

static void add_word(WordCountList *list, const char *word) {
    int index = find_word(list, word);
    if (index >= 0) {
        list->items[index].count++;
        return;
    }
    if (list->size >= list->capacity) {
        return;
    }
    strncpy(list->items[list->size].word, word, MAX_WORD_LEN - 1);
    list->items[list->size].word[MAX_WORD_LEN - 1] = '\0';
    list->items[list->size].count = 1;
    list->size++;
}

static int compare_word_counts(const void *a, const void *b) {
    const WordCount *wa = (const WordCount *)a;
    const WordCount *wb = (const WordCount *)b;
    if (wb->count != wa->count) {
        return wb->count - wa->count;
    }
    return strcmp(wa->word, wb->word);
}

void find_most_common_words(const char *text, int n) {
    if (text == NULL || n <= 0) {
        return;
    }

    WordCountList list;
    init_word_list(&list, MAX_WORDS);

    char buffer[MAX_WORD_LEN];
    int buf_index = 0;
    size_t text_len = strlen(text);

    for (size_t i = 0; i <= text_len; i++) {
        if (i < text_len && isalpha((unsigned char)text[i])) {
            if (buf_index < MAX_WORD_LEN - 1) {
                buffer[buf_index++] = text[i];
            }
        } else {
            if (buf_index > 0) {
                buffer[buf_index] = '\0';
                to_lowercase(buffer);
                add_word(&list, buffer);
                buf_index = 0;
            }
        }
    }

    qsort(list.items, (size_t)list.size, sizeof(WordCount), compare_word_counts);

    int output_count = (n < list.size) ? n : list.size;
    for (int i = 0; i < output_count; i++) {
        printf("%s: %d\n", list.items[i].word, list.items[i].count);
    }

    free_word_list(&list);
}

int main(void) {
    const char *text = "The quick brown fox jumps over the lazy dog. "
                       "The dog barks, and the fox runs away. "
                       "Quick thinking saves the day, but lazy days are rare.";
    int n = 3;

    printf("Top %d most common words:\n", n);
    find_most_common_words(text, n);

    return 0;
}