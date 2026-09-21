#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char **words;
    size_t size;
    size_t capacity;
} CollectionSet;

bool collection_set_init(CollectionSet *set, size_t capacity);
bool collection_set_contains(const CollectionSet *set, const char *word);
bool collection_set_add(CollectionSet *set, const char *word);
void collection_set_destroy(CollectionSet *set);
char *remove_duplicate_words(const char *input);

bool collection_set_init(CollectionSet *set, size_t capacity) {
    if (!set || capacity == 0) return false;
    
    set->words = calloc(capacity, sizeof(char *));
    if (!set->words) return false;
    
    set->size = 0;
    set->capacity = capacity;
    return true;
}

bool collection_set_contains(const CollectionSet *set, const char *word) {
    if (!set || !word) return false;
    
    for (size_t i = 0; i < set->size; i++) {
        if (strcmp(set->words[i], word) == 0) {
            return true;
        }
    }
    return false;
}

bool collection_set_add(CollectionSet *set, const char *word) {
    if (!set || !word) return false;
    
    if (collection_set_contains(set, word)) {
        return true;
    }

    if (set->size == set->capacity) {
        size_t new_capacity = set->capacity * 2;
        char **new_words = realloc(set->words, new_capacity * sizeof(char *));
        if (!new_words) return false;
        
        set->words = new_words;
        set->capacity = new_capacity;
    }

    char *word_copy = strdup(word);
    if (!word_copy) return false;

    set->words[set->size++] = word_copy;
    return true;
}

void collection_set_destroy(CollectionSet *set) {
    if (!set) return;
    
    for (size_t i = 0; i < set->size; i++) {
        free(set->words[i]);
    }
    free(set->words);
    
    set->words = NULL;
    set->size = 0;
    set->capacity = 0;
}

char *remove_duplicate_words(const char *input) {
    if (!input) return NULL;

    size_t input_len = 0;
    while (input[input_len] != '\0') {
        input_len++;
    }

    char *input_copy = malloc(input_len + 1);
    if (!input_copy) return NULL;
    for (size_t i = 0; i <= input_len; i++) {
        input_copy[i] = input[i];
    }

    CollectionSet set;
    if (!collection_set_init(&set, 16)) {
        free(input_copy);
        return NULL;
    }

    char *result = calloc(input_len + 1, sizeof(char));
    if (!result) {
        collection_set_destroy(&set);
        free(input_copy);
        return NULL;
    }

    const char *delim = " \t\n\r";
    char *saveptr = NULL;
    char *token = strtok_r(input_copy, delim, &saveptr);
    bool first_word = true;
    size_t current_len = 0;

    while (token != NULL) {
        if (!collection_set_contains(&set, token)) {
            if (!collection_set_add(&set, token)) {
                free(result);
                collection_set_destroy(&set);
                free(input_copy);
                return NULL;
            }
            
            size_t token_len = 0;
            while (token[token_len] != '\0') {
                token_len++;
            }

            if (!first_word && current_len < input_len) {
                result[current_len++] = ' ';
            }
            
            if (current_len + token_len <= input_len) {
                for (size_t i = 0; i < token_len; i++) {
                    result[current_len++] = token[i];
                }
                result[current_len] = '\0';
            }
            
            first_word = false;
        }
        token = strtok_r(NULL, delim, &saveptr);
    }

    collection_set_destroy(&set);
    free(input_copy);

    char *final_result = realloc(result, current_len + 1);
    if (!final_result) {
        return result;
    }
    
    return final_result;
}

int main(void) {
    const char *input_string = "hello world hello C programmer world C";
    char *unique_words_string = remove_duplicate_words(input_string);
    
    if (unique_words_string) {
        printf("%s\n", unique_words_string);
        free(unique_words_string);
        return EXIT_SUCCESS;
    }
    
    return EXIT_FAILURE;
}