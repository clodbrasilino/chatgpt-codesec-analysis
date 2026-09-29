#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stddef.h>

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
    if (list == NULL) {
        fprintf(stderr, "Invalid list pointer\n");
        exit(EXIT_FAILURE);
    }
    if (capacity <= 0 || capacity > MAX_WORDS) {
        fprintf(stderr, "Invalid capacity\n");
        exit(EXIT_FAILURE);
    }
    list->items = (WordCount *)malloc((size_t)capacity * sizeof(WordCount));
    if (list->items == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    list->size = 0;
    list->capacity = capacity;
}

static void free_word_list(WordCountList *list) {
    if (list != NULL && list->items != NULL) {
        free(list->items);
        list->items = NULL;
        list->size = 0;
        list->capacity = 0;
    }
}

static void to_lowercase(char *str) {
    if (str == NULL) {
        return;
    }
    for (size_t i = 0; str[i] != '\0'; i++) {
        str[i] = (char)tolower((unsigned char)str[i]);
    }
}

static int find_word(const WordCountList *list, const char *word) {
    if (list == NULL || word == NULL || list->items == NULL) {
        return -1;
    }
    for (int i = 0; i < list->size; i++) {
        if (strcmp(list->items[i].word, word) == 0) {
            return i;
        }
    }
    return -1;
}

static void add_word(WordCountList *list, const char *word) {
    if (list == NULL || word == NULL || list->items == NULL) {
        return;
    }
    if (list->size >= list->capacity) {
        return;
    }
    
    size_t word_len = 0;
    while (word[word_len] != '\0') {
        if (word_len >= MAX_WORD_LEN) {
            return;
        }
        word_len++;
    }
    
    if (word_len >= MAX_WORD_LEN) {
        return;
    }
    
    int index = find_word(list, word);
    if (index >= 0) {
        list->items[index].count++;
        return;
    }
    
    if (word_len > 0) {
        size_t safe_len = word_len < (size_t)(MAX_WORD_LEN - 1) ? word_len : (size_t)(MAX_WORD_LEN - 1);
        memcpy(list->items[list->size].word, word, safe_len);
        list->items[list->size].word[safe_len] = '\0';
        list->items[list->size].count = 1;
        list->size++;
    } else {
        list->items[list->size].word[0] = '\0';
        list->items[list->size].count = 1;
        list->size++;
    }
}

static int compare_word_counts(const void *a, const void *b) {
    if (a == NULL || b == NULL) {
        return 0;
    }
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

    char *buffer = (char *)malloc(MAX_WORD_LEN * sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Buffer allocation failed\n");
        free_word_list(&list);
        return;
    }
    
    size_t buf_index = 0;
    size_t pos = 0;

    while (text[pos] != '\0') {
        if (isalpha((unsigned char)text[pos])) {
            if (buf_index < (size_t)(MAX_WORD_LEN - 1)) {
                buffer[buf_index++] = text[pos];
            }
        } else {
            if (buf_index > 0) {
                buffer[buf_index] = '\0';
                to_lowercase(buffer);
                add_word(&list, buffer);
                buf_index = 0;
            }
        }
        pos++;
        if (pos > SIZE_MAX - 1) {
            break;
        }
    }

    if (buf_index > 0) {
        buffer[buf_index] = '\0';
        to_lowercase(buffer);
        add_word(&list, buffer);
    }

    free(buffer);
    buffer = NULL;

    if (list.size > 0 && list.items != NULL) {
        qsort(list.items, (size_t)list.size, sizeof(WordCount), compare_word_counts);
    }

    int output_count = (n < list.size) ? n : list.size;
    if (output_count > 0 && list.items != NULL) {
        for (int j = 0; j < output_count; j++) {
            printf("%s: %d\n", list.items[j].word, list.items[j].count);
        }
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