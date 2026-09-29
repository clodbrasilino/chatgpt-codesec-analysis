#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 100
#define INITIAL_CAPACITY 100

typedef struct {
    char *word;
    int count;
} WordCount;

typedef struct {
    WordCount *items;
    int size;
    int capacity;
} WordCountArray;

static void init_array(WordCountArray *arr) {
    arr->capacity = INITIAL_CAPACITY;
    arr->size = 0;
    arr->items = malloc(arr->capacity * sizeof(WordCount));
    if (!arr->items) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}

static void free_array(WordCountArray *arr) {
    for (int i = 0; i < arr->size; i++) {
        free(arr->items[i].word);
    }
    free(arr->items);
    arr->items = NULL;
    arr->size = 0;
    arr->capacity = 0;
}

static void add_word(WordCountArray *arr, const char *word) {
    for (int i = 0; i < arr->size; i++) {
        if (strcmp(arr->items[i].word, word) == 0) {
            arr->items[i].count++;
            return;
        }
    }
    
    if (arr->size >= arr->capacity) {
        arr->capacity *= 2;
        WordCount *new_items = realloc(arr->items, arr->capacity * sizeof(WordCount));
        if (!new_items) {
            fprintf(stderr, "Memory reallocation failed\n");
            free_array(arr);
            exit(EXIT_FAILURE);
        }
        arr->items = new_items;
    }
    
    arr->items[arr->size].word = malloc(strlen(word) + 1);
    if (!arr->items[arr->size].word) {
        fprintf(stderr, "Memory allocation failed\n");
        free_array(arr);
        exit(EXIT_FAILURE);
    }
    strcpy(arr->items[arr->size].word, word);
    arr->items[arr->size].count = 1;
    arr->size++;
}

static void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

static void find_most_common(const char *text, WordCountArray *result) {
    init_array(result);
    
    char word[MAX_WORD_LEN];
    int word_len = 0;
    int i = 0;
    
    while (text[i]) {
        if (isalpha((unsigned char)text[i])) {
            if (word_len < MAX_WORD_LEN - 1) {
                word[word_len++] = text[i];
            }
        } else {
            if (word_len > 0) {
                word[word_len] = '\0';
                to_lowercase(word);
                add_word(result, word);
                word_len = 0;
            }
        }
        i++;
    }
    
    if (word_len > 0) {
        word[word_len] = '\0';
        to_lowercase(word);
        add_word(result, word);
    }
    
    if (result->size == 0) {
        return;
    }
    
    int max_count = 0;
    for (int j = 0; j < result->size; j++) {
        if (result->items[j].count > max_count) {
            max_count = result->items[j].count;
        }
    }
    
    WordCountArray filtered;
    init_array(&filtered);
    
    for (int j = 0; j < result->size; j++) {
        if (result->items[j].count == max_count) {
            add_word(&filtered, result->items[j].word);
            filtered.items[filtered.size - 1].count = max_count;
        }
    }
    
    free_array(result);
    *result = filtered;
}

int main(void) {
    const char *text = "The quick brown fox jumps over the lazy dog. The dog barks, and the fox runs away.";
    WordCountArray result;
    
    find_most_common(text, &result);
    
    printf("Most common word(s) and their counts:\n");
    for (int i = 0; i < result.size; i++) {
        printf("%s: %d\n", result.items[i].word, result.items[i].count);
    }
    
    free_array(&result);
    
    return 0;
}