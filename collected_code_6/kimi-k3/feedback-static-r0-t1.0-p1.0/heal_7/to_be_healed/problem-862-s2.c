#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_WORD_LEN 100
#define INITIAL_CAPACITY 16
#define MAX_TEXT_LEN 10000

typedef struct {
    char *word;
    size_t word_len;
    int count;
} WordCount;

typedef struct {
    WordCount *words;
    size_t size;
    size_t capacity;
} WordList;

int init_word_list(WordList *list) {
    if (list == NULL) {
        return 0;
    }
    list->words = calloc(INITIAL_CAPACITY, sizeof(WordCount));
    if (list->words == NULL) {
        return 0;
    }
    list->size = 0;
    list->capacity = INITIAL_CAPACITY;
    return 1;
}

void free_word_list(WordList *list) {
    if (list == NULL) {
        return;
    }
    if (list->words != NULL) {
        for (size_t i = 0; i < list->size; i++) {
            free(list->words[i].word);
            list->words[i].word = NULL;
        }
        free(list->words);
        list->words = NULL;
    }
    list->size = 0;
    list->capacity = 0;
}

int resize_word_list(WordList *list) {
    if (list == NULL || list->capacity == 0) {
        return 0;
    }
    if (list->capacity > SIZE_MAX / (2 * sizeof(WordCount))) {
        return 0;
    }
    size_t new_capacity = list->capacity * 2;
    WordCount *new_words = realloc(list->words, new_capacity * sizeof(WordCount));
    if (new_words == NULL) {
        return 0;
    }
    list->words = new_words;
    list->capacity = new_capacity;
    return 1;
}

void to_lower(char *str, size_t len) {
    if (str == NULL) {
        return;
    }
    for (size_t i = 0; i < len; i++) {
        str[i] = (char)tolower((unsigned char)str[i]);
    }
}

int find_word(WordList *list, const char *word, size_t word_len) {
    if (list == NULL || word == NULL || word_len == 0) {
        return -1;
    }
    for (size_t i = 0; i < list->size; i++) {
        if (list->words[i].word_len == word_len && 
            memcmp(list->words[i].word, word, word_len) == 0) {
            return (int)i;
        }
    }
    return -1;
}

int add_word(WordList *list, const char *word, size_t word_len) {
    if (list == NULL || word == NULL || word_len == 0) {
        return 0;
    }
    
    int index = find_word(list, word, word_len);
    if (index >= 0) {
        list->words[index].count++;
        return 1;
    }

    if (list->size >= list->capacity) {
        if (!resize_word_list(list)) {
            return 0;
        }
    }

    char *new_word = malloc(word_len + 1);
    if (new_word == NULL) {
        return 0;
    }
    
    if (word_len > 0 && word_len <= MAX_WORD_LEN) {
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(new_word, word, word_len);
        new_word[word_len] = '\0';
    } else {
        free(new_word);
        return 0;
    }
    
    list->words[list->size].word = new_word;
    list->words[list->size].word_len = word_len;
    list->words[list->size].count = 1;
    list->size++;
    return 1;
}

int compare_word_count(const void *a, const void *b) {
    if (a == NULL || b == NULL) {
        return 0;
    }
    const WordCount *wa = (const WordCount *)a;
    const WordCount *wb = (const WordCount *)b;
    if (wb->count > wa->count) {
        return 1;
    } else if (wb->count < wa->count) {
        return -1;
    }
    return 0;
}

int process_text(WordList *list, const char *text, size_t text_len) {
    if (list == NULL || text == NULL || text_len == 0) {
        return 0;
    }
    
    char *buffer = malloc(MAX_WORD_LEN);
    if (buffer == NULL) {
        return 0;
    }
    
    size_t buf_index = 0;
    int result = 1;

    for (size_t i = 0; i < text_len && result; i++) {
        char c = text[i];
        if (isalnum((unsigned char)c)) {
            if (buf_index < MAX_WORD_LEN - 1) {
                buffer[buf_index++] = c;
            }
        } else {
            if (buf_index > 0) {
                buffer[buf_index] = '\0';
                to_lower(buffer, buf_index);
                if (!add_word(list, buffer, buf_index)) {
                    result = 0;
                }
                buf_index = 0;
            }
        }
    }

    if (result && buf_index > 0) {
        buffer[buf_index] = '\0';
        to_lower(buffer, buf_index);
        if (!add_word(list, buffer, buf_index)) {
            result = 0;
        }
    }

    free(buffer);
    return result;
}

void print_top_words(WordList *list, int n) {
    if (list == NULL || list->words == NULL || n <= 0) {
        return;
    }
    
    qsort(list->words, list->size, sizeof(WordCount), compare_word_count);

    size_t limit = (size_t)n < list->size ? (size_t)n : list->size;
    for (size_t i = 0; i < limit; i++) {
        printf("%s: %d\n", list->words[i].word, list->words[i].count);
    }
}

int main(void) {
    const char *text = "The quick brown fox jumps over the lazy dog. The dog was not amused by the fox.";
    
    size_t text_len = strnlen(text, MAX_TEXT_LEN);
    if (text_len == 0) {
        fprintf(stderr, "Empty text\n");
        return EXIT_FAILURE;
    }

    WordList list;
    if (!init_word_list(&list)) {
        fprintf(stderr, "Failed to initialize word list\n");
        return EXIT_FAILURE;
    }

    if (!process_text(&list, text, text_len)) {
        fprintf(stderr, "Failed to process text\n");
        free_word_list(&list);
        return EXIT_FAILURE;
    }

    int n = 5;
    printf("Top %d most common words:\n", n);
    print_top_words(&list, n);

    free_word_list(&list);
    return EXIT_SUCCESS;
}