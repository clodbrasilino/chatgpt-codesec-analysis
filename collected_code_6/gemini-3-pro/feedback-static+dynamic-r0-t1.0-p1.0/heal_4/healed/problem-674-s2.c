#define _POSIX_C_SOURCE 200809L
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

    size_t input_max_len = strnlen(input, (size_t)-1);
    char *input_copy = strdup(input);
    if (!input_copy) return NULL;

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
            out_len += strnlen(token, input_max_len) + 1;
        }
        token = strtok(NULL, " \t\n\r");
    }

    char *result = NULL;
    if (out_len > 0) {
        result = malloc(out_len);
        if (result) {
            size_t offset = 0;
            for (size_t i = 0; i < col.count; i++) {
                size_t len = strnlen(col.words[i], input_max_len);
                if (offset + len <= out_len) {
                    for (size_t j = 0; j < len; j++) {
                        result[offset + j] = col.words[i][j];
                    }
                    offset += len;
                }
                if (i < col.count - 1 && offset < out_len) {
                    result[offset++] = ' ';
                }
            }
            if (offset < out_len) {
                result[offset] = '\0';
            } else {
                result[out_len - 1] = '\0';
            }
        }
    } else {
        result = strdup("");
    }

    free_collection(&col);
    free(input_copy);
    return result;
}

int main(void) {
    char *buffer = NULL;
    size_t capacity = 0;
    ssize_t read_len;

    while ((read_len = getline(&buffer, &capacity, stdin)) != -1) {
        if (read_len > 0 && buffer[read_len - 1] == '\n') {
            buffer[read_len - 1] = '\0';
        } else {
            char *n = strchr(buffer, '\n');
            if (n) *n = '\0';
        }
        
        char *result = remove_duplicate_words(buffer);
        if (result) {
            printf("%s\n", result);
            free(result);
        }
    }

    free(buffer);
    return EXIT_SUCCESS;
}