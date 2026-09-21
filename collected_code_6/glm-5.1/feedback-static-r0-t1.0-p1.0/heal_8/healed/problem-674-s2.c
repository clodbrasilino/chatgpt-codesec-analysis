#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char **items;
    size_t size;
    size_t capacity;
} Collection;

bool collection_init(Collection *col) {
    col->capacity = 8;
    col->items = malloc(col->capacity * sizeof(char *));
    if (col->items == NULL) {
        return false;
    }
    col->size = 0;
    return true;
}

bool collection_append(Collection *col, const char *item) {
    if (col->size == col->capacity) {
        size_t new_capacity = col->capacity * 2;
        if (new_capacity == 0) return false;
        char **new_items = realloc(col->items, new_capacity * sizeof(char *));
        if (new_items == NULL) {
            return false;
        }
        col->items = new_items;
        col->capacity = new_capacity;
    }
    col->items[col->size] = strdup(item);
    if (col->items[col->size] == NULL) {
        return false;
    }
    col->size++;
    return true;
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
    if (col == NULL) return;
    for (size_t i = 0; i < col->size; i++) {
        free(col->items[i]);
    }
    free(col->items);
    col->items = NULL;
    col->size = 0;
    col->capacity = 0;
}

char *remove_duplicate_words(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    Collection seen;
    if (!collection_init(&seen)) {
        return NULL;
    }

    size_t str_len = strnlen(str, SIZE_MAX);
    size_t result_cap = str_len + 1;
    char *result = malloc(result_cap);
    if (result == NULL) {
        collection_free(&seen);
        return NULL;
    }
    result[0] = '\0';

    char *temp_str = strndup(str, str_len);
    if (temp_str == NULL) {
        collection_free(&seen);
        free(result);
        return NULL;
    }

    const char *delim = " \t\n\r";
    char *saveptr;
    char *token = strtok_r(temp_str, delim, &saveptr);
    char *current_ptr = result;

    while (token != NULL) {
        if (!collection_contains(&seen, token)) {
            if (!collection_append(&seen, token)) {
                free(temp_str);
                collection_free(&seen);
                free(result);
                return NULL;
            }
            size_t token_len = strnlen(token, SIZE_MAX);
            size_t current_len = current_ptr - result;
            size_t space_needed = (current_len > 0) ? 1 : 0;
            size_t needed = current_len + space_needed + token_len + 1;
            if (needed > result_cap) {
                size_t new_result_cap = needed * 2;
                char *new_result = realloc(result, new_result_cap);
                if (new_result == NULL) {
                    free(temp_str);
                    collection_free(&seen);
                    free(result);
                    return NULL;
                }
                current_ptr = new_result + current_len;
                result = new_result;
                result_cap = new_result_cap;
            }
            if (current_ptr != result) {
                *current_ptr++ = ' ';
            }
            if (token_len > 0 && current_ptr + token_len <= result + result_cap) {
                memcpy(current_ptr, token, token_len);
            }
            current_ptr += token_len;
            *current_ptr = '\0';
        }
        token = strtok_r(NULL, delim, &saveptr);
    }

    free(temp_str);
    collection_free(&seen);

    size_t final_len = strnlen(result, result_cap);
    char *final_result = malloc(final_len + 1);
    if (final_result == NULL) {
        free(result);
        return NULL;
    }
    if (final_len > 0) {
        memcpy(final_result, result, final_len);
    }
    final_result[final_len] = '\0';
    free(result);
    
    return final_result;
}

int main() {
    const char input[] = "hello world hello universe world again";
    char *output = remove_duplicate_words(input);

    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }

    return 0;
}