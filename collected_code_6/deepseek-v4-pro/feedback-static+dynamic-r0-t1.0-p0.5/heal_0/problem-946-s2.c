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
} WordCountList;

void init_list(WordCountList *list) {
    list->capacity = INITIAL_CAPACITY;
    list->size = 0;
    list->items = malloc(sizeof(WordCount) * list->capacity);
    if (list->items == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}

void free_list(WordCountList *list) {
    for (int i = 0; i < list->size; i++) {
        free(list->items[i].word);
    }
    free(list->items);
    list->items = NULL;
    list->size = 0;
    list->capacity = 0;
}

void add_word(WordCountList *list, const char *word) {
    for (int i = 0; i < list->size; i++) {
        if (strcmp(list->items[i].word, word) == 0) {
            list->items[i].count++;
            return;
        }
    }
    
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        WordCount *new_items = realloc(list->items, sizeof(WordCount) * list->capacity);
        if (new_items == NULL) {
            fprintf(stderr, "Memory reallocation failed\n");
            free_list(list);
            exit(EXIT_FAILURE);
        }
        list->items = new_items;
    }
    
    list->items[list->size].word = malloc(strlen(word) + 1);
    if (list->items[list->size].word == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free_list(list);
        exit(EXIT_FAILURE);
    }
    strcpy(list->items[list->size].word, word);
    list->items[list->size].count = 1;
    list->size++;
}

void find_most_common(const char *text, WordCountList *result) {
    init_list(result);
    
    char word[MAX_WORD_LEN];
    int word_len = 0;
    int i = 0;
    
    while (text[i] != '\0') {
        if (isalpha((unsigned char)text[i])) {
            if (word_len < MAX_WORD_LEN - 1) {
                word[word_len++] = tolower((unsigned char)text[i]);
            }
        } else {
            if (word_len > 0) {
                word[word_len] = '\0';
                add_word(result, word);
                word_len = 0;
            }
        }
        i++;
    }
    
    if (word_len > 0) {
        word[word_len] = '\0';
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
    
    WordCountList filtered;
    init_list(&filtered);
    
    for (int j = 0; j < result->size; j++) {
        if (result->items[j].count == max_count) {
            add_word(&filtered, result->items[j].word);
            filtered.items[filtered.size - 1].count = max_count;
        }
    }
    
    free_list(result);
    *result = filtered;
}

int main(void) {
    const char *text = "The quick brown fox jumps over the lazy dog. The dog barks, and the fox runs away.";
    WordCountList result;
    
    find_most_common(text, &result);
    
    printf("Most common word(s) and their counts:\n");
    for (int i = 0; i < result.size; i++) {
        printf("%s: %d\n", result.items[i].word, result.items[i].count);
    }
    
    free_list(&result);
    
    return 0;
}