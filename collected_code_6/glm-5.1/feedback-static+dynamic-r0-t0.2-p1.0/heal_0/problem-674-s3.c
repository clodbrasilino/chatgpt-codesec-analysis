#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char **items;
    size_t size;
    size_t capacity;
} Collection;

void collection_init(Collection *col, size_t initial_capacity) {
    col->items = (char **)malloc(initial_capacity * sizeof(char *));
    if (col->items == NULL) {
        exit(EXIT_FAILURE);
    }
    col->size = 0;
    col->capacity = initial_capacity;
}

void collection_push(Collection *col, const char *item) {
    if (col->size == col->capacity) {
        col->capacity *= 2;
        char **new_items = (char **)realloc(col->items, col->capacity * sizeof(char *));
        if (new_items == NULL) {
            exit(EXIT_FAILURE);
        }
        col->items = new_items;
    }
    col->items[col->size] = (char *)malloc(strlen(item) + 1);
    if (col->items[col->size] == NULL) {
        exit(EXIT_FAILURE);
    }
    strcpy(col->items[col->size], item);
    col->size++;
}

bool collection_contains(Collection *col, const char *item) {
    for (size_t i = 0; i < col->size; i++) {
        if (strcmp(col->items[i], item) == 0) {
            return true;
        }
    }
    return false;
}

void collection_free(Collection *col) {
    for (size_t i = 0; i < col->size; i++) {
        free(col->items[i]);
    }
    free(col->items);
    col->items = NULL;
    col->size = 0;
    col->capacity = 0;
}

char *remove_duplicate_words(const char *str) {
    Collection unique_words;
    collection_init(&unique_words, 8);

    size_t len = strlen(str);
    char *temp = (char *)malloc(len + 1);
    if (temp == NULL) {
        exit(EXIT_FAILURE);
    }
    strcpy(temp, str);

    size_t result_len = 0;
    char *token = strtok(temp, " \t\n\r");
    while (token != NULL) {
        if (!collection_contains(&unique_words, token)) {
            collection_push(&unique_words, token);
            result_len += strlen(token) + 1;
        }
        token = strtok(NULL, " \t\n\r");
    }
    free(temp);

    char *result = (char *)malloc(result_len > 0 ? result_len : 1);
    if (result == NULL) {
        collection_free(&unique_words);
        exit(EXIT_FAILURE);
    }
    result[0] = '\0';

    for (size_t i = 0; i < unique_words.size; i++) {
        strcat(result, unique_words.items[i]);
        if (i < unique_words.size - 1) {
            strcat(result, " ");
        }
    }

    collection_free(&unique_words);
    return result;
}

int main(void) {
    const char *input = "hello world hello universe world code code";
    char *output = remove_duplicate_words(input);

    printf("Input: %s\n", input);
    printf("Output: %s\n", output);

    free(output);

    return 0;
}