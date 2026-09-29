#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 1048576

typedef struct {
    char **words;
    size_t size;
    size_t capacity;
} WordCollection;

int init_collection(WordCollection *collection, size_t capacity) {
    if (!collection || capacity == 0) return 0;
    collection->words = malloc(capacity * sizeof(char *));
    if (!collection->words) return 0;
    collection->size = 0;
    collection->capacity = capacity;
    return 1;
}

int contains_word(WordCollection *collection, const char *word) {
    if (!collection || !word) return 0;
    for (size_t i = 0; i < collection->size; i++) {
        if (strcmp(collection->words[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

int add_word(WordCollection *collection, const char *word) {
    if (!collection || !word) return 0;
    if (collection->size >= collection->capacity) {
        size_t new_capacity = collection->capacity * 2;
        char **new_words = realloc(collection->words, new_capacity * sizeof(char *));
        if (!new_words) return 0;
        collection->words = new_words;
        collection->capacity = new_capacity;
    }
    collection->words[collection->size++] = (char *)word;
    return 1;
}

void free_collection(WordCollection *collection) {
    if (collection) {
        free(collection->words);
        collection->words = NULL;
        collection->size = 0;
        collection->capacity = 0;
    }
}

char *remove_duplicate_words(const char *input) {
    if (!input) return NULL;

    size_t len = strnlen(input, MAX_INPUT_LENGTH);
    if (len >= MAX_INPUT_LENGTH) return NULL;

    char *input_copy = malloc(len + 1);
    if (!input_copy) return NULL;
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(input_copy, input, len);
    input_copy[len] = '\0';

    char *result = malloc(len + 1);
    if (!result) {
        free(input_copy);
        return NULL;
    }
    result[0] = '\0';
    size_t result_len = 0;

    WordCollection seen_words;
    if (!init_collection(&seen_words, 16)) {
        free(input_copy);
        free(result);
        return NULL;
    }

    const char *delim = " \t\n\r";
    char *token = strtok(input_copy, delim);
    int first_word = 1;

    while (token != NULL) {
        if (!contains_word(&seen_words, token)) {
            if (!add_word(&seen_words, token)) {
                free(input_copy);
                free(result);
                free_collection(&seen_words);
                return NULL;
            }
            
            if (!first_word) {
                if (result_len < len) {
                    result[result_len++] = ' ';
                }
            }
            
            size_t token_len = strnlen(token, len);
            
            if (result_len + token_len <= len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + result_len, token, token_len);
                result_len += token_len;
                result[result_len] = '\0';
            }
            
            first_word = 0;
        }
        token = strtok(NULL, delim);
    }

    free_collection(&seen_words);
    free(input_copy);

    return result;
}

int main(void) {
    char *text = malloc(MAX_INPUT_LENGTH);
    if (!text) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }
    
    if (fgets(text, MAX_INPUT_LENGTH, stdin)) {
        size_t len = strnlen(text, MAX_INPUT_LENGTH);
        if (len > 0 && text[len - 1] == '\n') {
            text[len - 1] = '\0';
        }
        
        char *unique_text = remove_duplicate_words(text);
        
        if (unique_text) {
            printf("%s\n", unique_text);
            free(unique_text);
        } else {
            fprintf(stderr, "Memory allocation failed or invalid input.\n");
            free(text);
            return EXIT_FAILURE;
        }
    }
    
    free(text);
    return EXIT_SUCCESS;
}