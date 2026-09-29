#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char **words;
    size_t size;
    size_t capacity;
} WordCollection;

static char *safe_strdup(const char *src) {
    if (!src) {
        return NULL;
    }
    
    size_t len = 0;
    while (src[len] != '\0') {
        len++;
    }
    
    char *dst = (char *)malloc(len + 1);
    if (dst) {
        for (size_t i = 0; i <= len; i++) {
            dst[i] = src[i];
        }
    }
    return dst;
}

static bool init_collection(WordCollection *col, size_t capacity) {
    if (!col || capacity == 0) {
        return false;
    }
    col->words = (char **)malloc(capacity * sizeof(char *));
    if (!col->words) {
        return false;
    }
    col->size = 0;
    col->capacity = capacity;
    return true;
}

static void free_collection(WordCollection *col) {
    if (!col) {
        return;
    }
    for (size_t i = 0; i < col->size; i++) {
        free(col->words[i]);
    }
    free(col->words);
    col->words = NULL;
    col->size = 0;
    col->capacity = 0;
}

static bool collection_contains(const WordCollection *col, const char *word) {
    if (!col || !word || !col->words) {
        return false;
    }
    for (size_t i = 0; i < col->size; i++) {
        if (strcmp(col->words[i], word) == 0) {
            return true;
        }
    }
    return false;
}

static bool collection_add(WordCollection *col, const char *word) {
    if (!col || !word) {
        return false;
    }
    if (col->size == col->capacity) {
        size_t new_cap = col->capacity * 2;
        char **new_words = (char **)realloc(col->words, new_cap * sizeof(char *));
        if (!new_words) {
            return false;
        }
        col->words = new_words;
        col->capacity = new_cap;
    }
    char *word_copy = safe_strdup(word);
    if (!word_copy) {
        return false;
    }
    col->words[col->size] = word_copy;
    col->size++;
    return true;
}

char *remove_duplicate_words(const char *input) {
    if (!input) {
        return NULL;
    }

    char *input_copy = safe_strdup(input);
    if (!input_copy) {
        return NULL;
    }

    WordCollection col;
    if (!init_collection(&col, 16)) {
        free(input_copy);
        return NULL;
    }

    size_t expected_length = 1;
    char *token = strtok(input_copy, " \t\n");
    
    while (token) {
        if (!collection_contains(&col, token)) {
            if (!collection_add(&col, token)) {
                free_collection(&col);
                free(input_copy);
                return NULL;
            }
            size_t token_len = 0;
            while (token[token_len] != '\0') {
                token_len++;
            }
            expected_length += token_len + 1;
        }
        token = strtok(NULL, " \t\n");
    }

    char *result = (char *)malloc(expected_length);
    if (!result) {
        free_collection(&col);
        free(input_copy);
        return NULL;
    }
    
    char *cursor = result;
    for (size_t i = 0; i < col.size; i++) {
        const char *w = col.words[i];
        while (*w != '\0') {
            *cursor++ = *w++;
        }
        if (i < col.size - 1) {
            *cursor++ = ' ';
        }
    }
    *cursor = '\0';

    free_collection(&col);
    free(input_copy);
    return result;
}

int main(void) {
    const char *text = "hello world hello C programmer world C";
    char *unique_text = remove_duplicate_words(text);
    
    if (unique_text) {
        printf("Original: %s\n", text);
        printf("Unique:   %s\n", unique_text);
        free(unique_text);
    } else {
        fprintf(stderr, "Memory allocation failed or invalid input.\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}