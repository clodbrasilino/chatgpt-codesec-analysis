#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_WORD_LEN 100
#define INITIAL_CAPACITY 16

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LEN];
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
    free(list->words);
    list->words = NULL;
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
    if (list == NULL || word == NULL || word_len == 0 || word_len >= MAX_WORD_LEN) {
        return -1;
    }
    for (size_t i = 0; i < list->size; i++) {
        if (strncmp(list->words[i].word, word, word_len) == 0 && 
            list->words[i].word[word_len] == '\0') {
            return (int)i;
        }
    }
    return -1;
}

int add_word(WordList *list, const char *word, size_t word_len) {
    if (list == NULL || word == NULL || word_len == 0 || word_len >= MAX_WORD_LEN) {
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

    size_t copy_len = word_len < MAX_WORD_LEN - 1 ? word_len : MAX_WORD_LEN - 1;
    if (copy_len >= MAX_WORD_LEN) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(list->words[list->size].word, word, copy_len);
    list->words[list->size].word[copy_len] = '\0';
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
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_WORD_LEN];
    size_t buf_index = 0;

    for (size_t i = 0; i < text_len; i++) {
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
                    return 0;
                }
                buf_index = 0;
            }
        }
    }

    if (buf_index > 0) {
        buffer[buf_index] = '\0';
        to_lower(buffer, buf_index);
        if (!add_word(list, buffer, buf_index)) {
            return 0;
        }
    }

    return 1;
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
    /* Possible weaknesses found:
     *  Assignment 'text="The quick brown fox jumps over the lazy dog. The dog was not amused by the fox."', assigned value is "The quick brown fox jumps over the lazy dog. The dog was not amused by the fox."
     */
    const char *text = "The quick brown fox jumps over the lazy dog. The dog was not amused by the fox.";
    /* Possible weaknesses found:
     *  Condition 'text==NULL' is always false
     *  Condition 'text==NULL' is always false [knownConditionTrueFalse]
     */
    if (text == NULL) {
        fprintf(stderr, "Invalid text input\n");
        return EXIT_FAILURE;
    }
    
    size_t text_len = strnlen(text, 10000);
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