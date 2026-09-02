#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 10000
#define MAX_WORD_LEN 100
#define INITIAL_CAPACITY 1000

typedef struct {
    char *word;
    int count;
} WordCount;

typedef struct {
    WordCount *items;
    int size;
    int capacity;
} WordCountList;

char *strdup_lower(const char *s) {
    if (!s) return NULL;
    int len = strlen(s);
    char *result = malloc((len + 1) * sizeof(char));
    if (!result) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < len; i++) {
        result[i] = tolower((unsigned char)s[i]);
    }
    result[len] = '\0';
    return result;
}

void init_list(WordCountList *list) {
    list->items = malloc(INITIAL_CAPACITY * sizeof(WordCount));
    if (!list->items) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    list->size = 0;
    list->capacity = INITIAL_CAPACITY;
}

void destroy_list(WordCountList *list) {
    for (int i = 0; i < list->size; i++) {
        free(list->items[i].word);
    }
    free(list->items);
    list->items = NULL;
    list->size = 0;
    list->capacity = 0;
}

int find_word(WordCountList *list, const char *word) {
    for (int i = 0; i < list->size; i++) {
        if (strcmp(list->items[i].word, word) == 0) {
            return i;
        }
    }
    return -1;
}

void add_word(WordCountList *list, const char *word) {
    int idx = find_word(list, word);
    if (idx != -1) {
        list->items[idx].count++;
        return;
    }
    
    if (list->size >= list->capacity) {
        int new_capacity = list->capacity * 2;
        WordCount *new_items = realloc(list->items, new_capacity * sizeof(WordCount));
        if (!new_items) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        list->items = new_items;
        list->capacity = new_capacity;
    }
    
    list->items[list->size].word = strdup_lower(word);
    list->items[list->size].count = 1;
    list->size++;
}

int compare_counts(const void *a, const void *b) {
    const WordCount *wa = (const WordCount *)a;
    const WordCount *wb = (const WordCount *)b;
    if (wa->count != wb->count) {
        return wb->count - wa->count;
    }
    return strcmp(wa->word, wb->word);
}

void find_top_words(const char *text, int n) {
    if (!text || n <= 0) {
        return;
    }
    
    WordCountList list;
    init_list(&list);
    
    char word[MAX_WORD_LEN + 1];
    int word_len = 0;
    int text_len = strlen(text);
    
    for (int i = 0; i <= text_len; i++) {
        char c = (i < text_len) ? text[i] : '\0';
        
        if (isalnum((unsigned char)c)) {
            if (word_len < MAX_WORD_LEN) {
                word[word_len++] = tolower((unsigned char)c);
            }
        } else {
            if (word_len > 0) {
                word[word_len] = '\0';
                add_word(&list, word);
                word_len = 0;
            }
        }
    }
    
    qsort(list.items, list.size, sizeof(WordCount), compare_counts);
    
    int num_to_print = (n < list.size) ? n : list.size;
    for (int i = 0; i < num_to_print; i++) {
        printf("%s: %d\n", list.items[i].word, list.items[i].count);
    }
    
    destroy_list(&list);
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 'text' can be declared as const array [constVariable]
     */
    char text[] = "The quick brown fox jumps over the lazy dog. The dog barks, and the fox runs away quickly. The quick fox is very quick.";
    int n = 3;
    
    printf("Top %d most common words:\n", n);
    find_top_words(text, n);
    
    return 0;
}