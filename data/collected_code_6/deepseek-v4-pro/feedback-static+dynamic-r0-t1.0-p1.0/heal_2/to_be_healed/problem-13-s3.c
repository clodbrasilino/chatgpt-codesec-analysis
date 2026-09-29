#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INITIAL_CAPACITY 100
#define MAX_WORD_LENGTH 100

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LENGTH];
    int count;
} WordCount;

typedef struct {
    WordCount *items;
    int size;
    int capacity;
} WordCountList;

static void init_list(WordCountList *list) {
    if (list == NULL) return;
    list->capacity = INITIAL_CAPACITY;
    list->size = 0;
    list->items = (WordCount *)calloc((size_t)list->capacity, sizeof(WordCount));
    if (list->items == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
}

static void free_list(WordCountList *list) {
    if (list == NULL) return;
    free(list->items);
    list->items = NULL;
    list->size = 0;
    list->capacity = 0;
}

static void resize_list(WordCountList *list) {
    if (list == NULL) return;
    int new_capacity = list->capacity * 2;
    WordCount *new_items = (WordCount *)realloc(list->items, (size_t)new_capacity * sizeof(WordCount));
    if (new_items == NULL) {
        fprintf(stderr, "Memory reallocation failed\n");
        free_list(list);
        exit(1);
    }
    list->items = new_items;
    list->capacity = new_capacity;
}

static int find_word(WordCountList *list, const char *word) {
    if (list == NULL || word == NULL) return -1;
    for (int i = 0; i < list->size; i++) {
        if (strcmp(list->items[i].word, word) == 0) {
            return i;
        }
    }
    return -1;
}

static void add_word(WordCountList *list, const char *word) {
    if (list == NULL || word == NULL) return;
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t word_len = strlen(word);
    if (word_len >= MAX_WORD_LENGTH) return;
    
    int index = find_word(list, word);
    if (index != -1) {
        list->items[index].count++;
        return;
    }
    
    if (list->size >= list->capacity) {
        resize_list(list);
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(list->items[list->size].word, word, word_len + 1);
    list->items[list->size].count = 1;
    list->size++;
}

static void count_words(const char *text, WordCountList *list) {
    if (text == NULL || list == NULL) return;
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LENGTH];
    int len = 0;
    
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha((unsigned char)text[i])) {
            if (len < MAX_WORD_LENGTH - 1) {
                word[len++] = (char)tolower((unsigned char)text[i]);
            }
        } else {
            if (len > 0) {
                word[len] = '\0';
                add_word(list, word);
                len = 0;
            }
        }
    }
    
    if (len > 0) {
        word[len] = '\0';
        add_word(list, word);
    }
}

static void print_word_counts(WordCountList *list) {
    if (list == NULL) return;
    for (int i = 0; i < list->size; i++) {
        printf("%s: %d\n", list->items[i].word, list->items[i].count);
    }
}

int main(void) {
    const char *dictionary_text = "The quick brown fox jumps over the lazy dog. The dog barks at the fox.";
    
    WordCountList word_counts;
    init_list(&word_counts);
    
    count_words(dictionary_text, &word_counts);
    print_word_counts(&word_counts);
    
    free_list(&word_counts);
    
    return 0;
}