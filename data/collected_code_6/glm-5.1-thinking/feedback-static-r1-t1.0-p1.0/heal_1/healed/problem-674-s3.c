#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char **items;
    size_t size;
    size_t capacity;
} WordCollection;

WordCollection *collection_create(void) {
    WordCollection *c = malloc(sizeof(WordCollection));
    if (!c) return NULL;
    c->size = 0;
    c->capacity = 16;
    c->items = malloc(c->capacity * sizeof(char *));
    if (!c->items) {
        free(c);
        return NULL;
    }
    return c;
}

int collection_contains(const WordCollection *c, const char *word) {
    if (!c || !word) return 0;
    for (size_t i = 0; i < c->size; i++) {
        if (strcmp(c->items[i], word) == 0) return 1;
    }
    return 0;
}

int collection_add(WordCollection *c, const char *word) {
    if (!c || !word) return 0;
    if (collection_contains(c, word)) return 1;
    if (c->size == c->capacity) {
        size_t new_cap = c->capacity * 2;
        char **new_items = realloc(c->items, new_cap * sizeof(char *));
        if (!new_items) return 0;
        c->items = new_items;
        c->capacity = new_cap;
    }
    char *word_copy = strdup(word);
    if (!word_copy) return 0;
    c->items[c->size++] = word_copy;
    return 1;
}

void collection_free(WordCollection *c) {
    if (!c) return;
    for (size_t i = 0; i < c->size; i++) {
        free(c->items[i]);
    }
    free(c->items);
    free(c);
}

char *remove_duplicate_words(const char *str) {
    if (!str) return NULL;

    size_t max_len = 65536;
    size_t len = strnlen(str, max_len);
    
    WordCollection *c = collection_create();
    if (!c) return NULL;

    char *result = malloc(len + 1);
    if (!result) {
        collection_free(c);
        return NULL;
    }
    
    size_t res_len = 0;
    result[0] = '\0';

    char *temp = malloc(len + 1);
    if (!temp) {
        free(result);
        collection_free(c);
        return NULL;
    }
    memcpy(temp, str, len);
    temp[len] = '\0';

    char *token = strtok(temp, " \t\n\r");
    while (token != NULL) {
        if (!collection_contains(c, token)) {
            if (!collection_add(c, token)) {
                free(temp);
                free(result);
                collection_free(c);
                return NULL;
            }
            size_t tok_len = strnlen(token, len + 1);
            size_t space_needed = (res_len > 0) ? tok_len + 1 : tok_len;
            if (res_len + space_needed <= len) {
                if (res_len > 0) {
                    result[res_len++] = ' ';
                }
                memcpy(result + res_len, token, tok_len);
                res_len += tok_len;
                result[res_len] = '\0';
            }
        }
        token = strtok(NULL, " \t\n\r");
    }

    free(temp);
    collection_free(c);
    
    char *final_result = realloc(result, res_len + 1);
    if (!final_result) return result;
    
    return final_result;
}

int main(void) {
    const char *input = "hello world hello C world programming C code";
    char *output = remove_duplicate_words(input);
    
    if (output) {
        printf("Input: %s\n", input);
        printf("Output: %s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Failed to process string.\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}