#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char **items;
    size_t size;
    size_t capacity;
} StringCollection;

int collection_init(StringCollection *col, size_t initial_capacity) {
    col->items = NULL;
    if (initial_capacity > 0) {
        col->items = malloc(initial_capacity * sizeof(char *));
        if (!col->items) return 0;
    }
    col->size = 0;
    col->capacity = initial_capacity;
    return 1;
}

int collection_contains(StringCollection *col, const char *word) {
    for (size_t i = 0; i < col->size; i++) {
        if (strcmp(col->items[i], word) == 0) return 1;
    }
    return 0;
}

int collection_add(StringCollection *col, const char *word) {
    if (collection_contains(col, word)) return 1;
    if (col->size == col->capacity) {
        size_t new_capacity = col->capacity == 0 ? 4 : col->capacity * 2;
        if (new_capacity / 2 != col->capacity && col->capacity != 0) return 0;
        char **new_items = realloc(col->items, new_capacity * sizeof(char *));
        if (!new_items) return 0;
        col->items = new_items;
        col->capacity = new_capacity;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t word_len = strlen(word);
    char *word_copy = malloc(word_len + 1);
    if (!word_copy) return 0;
    snprintf(word_copy, word_len + 1, "%s", word);
    col->items[col->size++] = word_copy;
    return 2;
}

void collection_free(StringCollection *col) {
    for (size_t i = 0; i < col->size; i++) {
        free(col->items[i]);
    }
    free(col->items);
    col->items = NULL;
    col->size = 0;
    col->capacity = 0;
}

char *remove_duplicate_words(const char *input) {
    if (!input) return NULL;

    StringCollection col;
    if (!collection_init(&col, 16)) return NULL;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    char *input_copy = malloc(input_len + 1);
    if (!input_copy) {
        collection_free(&col);
        return NULL;
    }
    snprintf(input_copy, input_len + 1, "%s", input);

    size_t result_capacity = input_len + 1;
    char *result = malloc(result_capacity);
    if (!result) {
        free(input_copy);
        collection_free(&col);
        return NULL;
    }
    result[0] = '\0';
    size_t result_len = 0;

    const char *delim = " \t\n\r";
    char *token = strtok(input_copy, delim);
    while (token != NULL) {
        int add_res = collection_add(&col, token);
        if (add_res == 0) {
            free(input_copy);
            free(result);
            collection_free(&col);
            return NULL;
        } else if (add_res == 2) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t token_len = strlen(token);
            size_t space_needed = token_len;
            if (result_len > 0) {
                if (space_needed == SIZE_MAX) {
                    free(input_copy);
                    free(result);
                    collection_free(&col);
                    return NULL;
                }
                space_needed++;
            }

            if (result_len > SIZE_MAX - space_needed - 1) {
                free(input_copy);
                free(result);
                collection_free(&col);
                return NULL;
            }

            if (result_len + space_needed + 1 > result_capacity) {
                size_t new_cap = result_capacity * 2;
                if (new_cap / 2 != result_capacity) {
                    free(input_copy);
                    free(result);
                    collection_free(&col);
                    return NULL;
                }
                while (result_len + space_needed + 1 > new_cap) {
                    size_t next_cap = new_cap * 2;
                    if (next_cap / 2 != new_cap) {
                        free(input_copy);
                        free(result);
                        collection_free(&col);
                        return NULL;
                    }
                    new_cap = next_cap;
                }
                char *new_result = realloc(result, new_cap);
                if (!new_result) {
                    free(input_copy);
                    free(result);
                    collection_free(&col);
                    return NULL;
                }
                result = new_result;
                result_capacity = new_cap;
            }

            if (result_len > 0) {
                result[result_len++] = ' ';
            }
            snprintf(result + result_len, result_capacity - result_len, "%s", token);
            result_len += token_len;
        }
        token = strtok(NULL, delim);
    }

    free(input_copy);
    collection_free(&col);

    char *final_result = realloc(result, result_len + 1);
    if (final_result) {
        return final_result;
    }
    return result;
}

int main(void) {
    const char *text = "hello world hello there world C programming C code";
    char *unique_text = remove_duplicate_words(text);

    if (unique_text) {
        printf("Original: %s\n", text);
        printf("No duplicates: %s\n", unique_text);
        free(unique_text);
    } else {
        fprintf(stderr, "Error processing string.\n");
        return 1;
    }

    return 0;
}