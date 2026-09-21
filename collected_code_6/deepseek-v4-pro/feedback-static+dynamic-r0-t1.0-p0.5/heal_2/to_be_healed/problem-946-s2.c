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
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t word_len = strlen(word);
    list->items[list->size].word = malloc(word_len + 1);
    if (list->items[list->size].word == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free_list(list);
        exit(EXIT_FAILURE);
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(list->items[list->size].word, word, word_len + 1);
    list->items[list->size].count = 1;
    list->size++;
}

void find_most_common(const char *text, WordCountList *result) {
    init_list(result);
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LEN];
    int word_len = 0;
    size_t i = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t text_len = strlen(text);
    
    /* Possible weaknesses found:
     *  Condition 'text[i]!='\0'' is always true [knownConditionTrueFalse]
     */
    while (i < text_len && text[i] != '\0') {
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