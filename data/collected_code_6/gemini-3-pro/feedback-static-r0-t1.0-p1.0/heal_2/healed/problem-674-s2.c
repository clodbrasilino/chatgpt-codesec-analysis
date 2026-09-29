#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char **words;
    size_t count;
    size_t capacity;
} WordCollection;

int init_collection(WordCollection *col, size_t initial_capacity) {
    if (!col || initial_capacity == 0) return 0;
    col->words = malloc(initial_capacity * sizeof(char *));
    if (!col->words) return 0;
    col->count = 0;
    col->capacity = initial_capacity;
    return 1;
}

void free_collection(WordCollection *col) {
    if (!col) return;
    for (size_t i = 0; i < col->count; i++) {
        free(col->words[i]);
    }
    free(col->words);
    col->words = NULL;
    col->count = 0;
    col->capacity = 0;
}

int add_word_if_unique(WordCollection *col, const char *word) {
    if (!col || !word) return 0;

    for (size_t i = 0; i < col->count; i++) {
        if (strcmp(col->words[i], word) == 0) {
            return 1;
        }
    }

    if (col->count >= col->capacity) {
        size_t new_cap = col->capacity * 2;
        char **new_words = realloc(col->words, new_cap * sizeof(char *));
        if (!new_words) return 0;
        col->words = new_words;
        col->capacity = new_cap;
    }

    col->words[col->count] = strdup(word);
    if (!col->words[col->count]) return 0;
    col->count++;
    return 1;
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

    WordCollection col;
    if (!init_collection(&col, 16)) {
        free(input_copy);
        return NULL;
    }

    size_t out_len = 0;
    char *token = strtok(input_copy, " \t\n\r");
    while (token != NULL) {
        size_t old_count = col.count;
        if (!add_word_if_unique(&col, token)) {
            free_collection(&col);
            free(input_copy);
            return NULL;
        }
        if (col.count > old_count) {
            size_t token_len = 0;
            while (token[token_len] != '\0') {
                token_len++;
            }
            out_len += token_len + 1;
        }
        token = strtok(NULL, " \t\n\r");
    }

    char *result = NULL;
    if (out_len > 0) {
        result = malloc(out_len);
        if (result) {
            char *ptr = result;
            size_t remaining = out_len;
            for (size_t i = 0; i < col.count; i++) {
                size_t len = 0;
                while (col.words[i][len] != '\0') {
                    len++;
                }
                
                if (len < remaining) {
                    for (size_t j = 0; j < len; j++) {
                        *ptr++ = col.words[i][j];
                    }
                    remaining -= len;
                    
                    if (i < col.count - 1 && remaining > 1) {
                        *ptr++ = ' ';
                        remaining--;
                    }
                }
            }
            *ptr = '\0';
        }
    } else {
        result = malloc(1);
        if (result) {
            result[0] = '\0';
        }
    }

    free_collection(&col);
    free(input_copy);
    return result;
}

int main(void) {
    const char *test_string = "hello world hello C programming C world";
    
    char *result = remove_duplicate_words(test_string);
    if (result) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Memory allocation failed or invalid input.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}