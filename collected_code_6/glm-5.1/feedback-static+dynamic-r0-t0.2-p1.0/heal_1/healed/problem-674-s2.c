#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char **items;
    size_t size;
    size_t capacity;
} Collection;

void collection_free(Collection *col);

void collection_init(Collection *col, size_t initial_capacity) {
    col->items = (char **)malloc(initial_capacity * sizeof(char *));
    if (col->items == NULL) {
        exit(EXIT_FAILURE);
    }
    col->size = 0;
    col->capacity = initial_capacity;
}

void collection_append(Collection *col, const char *item) {
    if (col->size == col->capacity) {
        col->capacity *= 2;
        char **new_items = (char **)realloc(col->items, col->capacity * sizeof(char *));
        if (new_items == NULL) {
            collection_free(col);
            exit(EXIT_FAILURE);
        }
        col->items = new_items;
    }
    col->items[col->size] = (char *)malloc(strlen(item) + 1);
    if (col->items[col->size] == NULL) {
        collection_free(col);
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
    if (col->items != NULL) {
        for (size_t i = 0; i < col->size; i++) {
            free(col->items[i]);
        }
        free(col->items);
        col->items = NULL;
    }
    col->size = 0;
    col->capacity = 0;
}

char *remove_duplicate_words(const char *str) {
    Collection unique_words;
    collection_init(&unique_words, 16);

    size_t len = strlen(str);
    char *temp = (char *)malloc(len + 1);
    if (temp == NULL) {
        collection_free(&unique_words);
        exit(EXIT_FAILURE);
    }
    strcpy(temp, str);

    size_t result_capacity = len + 1;
    char *result = (char *)malloc(result_capacity);
    if (result == NULL) {
        free(temp);
        collection_free(&unique_words);
        exit(EXIT_FAILURE);
    }
    result[0] = '\0';

    char *token = strtok(temp, " \t\n\r");
    while (token != NULL) {
        if (!collection_contains(&unique_words, token)) {
            collection_append(&unique_words, token);
            if (strlen(result) > 0) {
                strcat(result, " ");
            }
            strcat(result, token);
        }
        token = strtok(NULL, " \t\n\r");
    }

    free(temp);
    collection_free(&unique_words);

    char *final_result = (char *)realloc(result, strlen(result) + 1);
    if (final_result == NULL) {
        free(result);
        return NULL;
    }

    return final_result;
}

int main(void) {
    const char input[] = "hello world hello universe world";
    char *output = remove_duplicate_words(input);

    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }

    return 0;
}