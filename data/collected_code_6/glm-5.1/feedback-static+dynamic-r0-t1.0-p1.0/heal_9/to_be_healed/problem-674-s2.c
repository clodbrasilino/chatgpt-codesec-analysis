#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char **items;
    size_t size;
    size_t capacity;
} Collection;

void collection_init(Collection *col) {
    col->capacity = 8;
    col->items = malloc(col->capacity * sizeof(char *));
    if (col->items == NULL) {
        exit(EXIT_FAILURE);
    }
    col->size = 0;
}

void collection_append(Collection *col, const char *item) {
    if (col->size == col->capacity) {
        col->capacity *= 2;
        char **new_items = realloc(col->items, col->capacity * sizeof(char *));
        if (new_items == NULL) {
            exit(EXIT_FAILURE);
        }
        col->items = new_items;
    }
    col->items[col->size] = strdup(item);
    if (col->items[col->size] == NULL) {
        exit(EXIT_FAILURE);
    }
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
    if (str == NULL || str[0] == '\0') {
        return strdup("");
    }

    Collection seen;
    collection_init(&seen);

    size_t input_len = strnlen(str, SIZE_MAX);
    size_t result_cap = input_len + 1;
    char *result = malloc(result_cap);
    if (result == NULL) {
        exit(EXIT_FAILURE);
    }
    result[0] = '\0';

    char *temp_str = strndup(str, input_len);
    if (temp_str == NULL) {
        free(result);
        exit(EXIT_FAILURE);
    }

    const char *delim = " \t\n\r";
    char *saveptr;
    char *token = strtok_r(temp_str, delim, &saveptr);
    char *current_ptr = result;
    size_t remaining_cap = result_cap;

    while (token != NULL) {
        if (!collection_contains(&seen, token)) {
            collection_append(&seen, token);
            size_t token_len = strnlen(token, SIZE_MAX);
            size_t required_space = token_len + (current_ptr != result ? 1 : 0);
            
            while (required_space + 1 > remaining_cap) {
                size_t offset = current_ptr - result;
                result_cap = offset + required_space + 1;
                char *new_result = realloc(result, result_cap);
                if (new_result == NULL) {
                    free(temp_str);
                    collection_free(&seen);
                    free(result);
                    exit(EXIT_FAILURE);
                }
                result = new_result;
                current_ptr = result + offset;
                remaining_cap = result_cap - offset;
            }

            if (current_ptr != result) {
                *current_ptr++ = ' ';
                remaining_cap--;
            }
            if (remaining_cap >= token_len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(current_ptr, token, token_len);
            }
            current_ptr += token_len;
            remaining_cap -= token_len;
            *current_ptr = '\0';
        }
        token = strtok_r(NULL, delim, &saveptr);
    }

    free(temp_str);
    collection_free(&seen);

    size_t final_len = current_ptr - result;
    if (final_len == 0) {
        free(result);
        return strdup("");
    }
    
    char *final_result = malloc(final_len + 1);
    if (final_result == NULL) {
        free(result);
        exit(EXIT_FAILURE);
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(final_result, result, final_len + 1);
    
    free(result);
    return final_result;
}

int main() {
    const char input[] = "Python Exercises Practice Solution Python Exercises";
    char *output = remove_duplicate_words(input);

    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }

    return 0;
}