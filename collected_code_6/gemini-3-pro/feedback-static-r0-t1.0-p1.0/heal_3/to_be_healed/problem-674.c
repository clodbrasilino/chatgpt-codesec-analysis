#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **elements;
    size_t size;
    size_t capacity;
} Collection;

static int collection_init(Collection *c, size_t initial_capacity) {
    if (!c || initial_capacity == 0) {
        return 0;
    }
    c->elements = malloc(initial_capacity * sizeof(char *));
    if (!c->elements) {
        return 0;
    }
    c->size = 0;
    c->capacity = initial_capacity;
    return 1;
}

static int collection_contains(const Collection *c, const char *item) {
    if (!c || !item) {
        return 0;
    }
    for (size_t i = 0; i < c->size; i++) {
        if (strcmp(c->elements[i], item) == 0) {
            return 1;
        }
    }
    return 0;
}

static int collection_add(Collection *c, const char *item) {
    if (!c || !item) {
        return 0;
    }
    if (c->size >= c->capacity) {
        size_t new_capacity = c->capacity * 2;
        char **new_elements = realloc(c->elements, new_capacity * sizeof(char *));
        if (!new_elements) {
            return 0;
        }
        c->elements = new_elements;
        c->capacity = new_capacity;
    }
    
    char *copy = strdup(item);
    if (!copy) {
        return 0;
    }
    c->elements[c->size++] = copy;
    return 1;
}

static void collection_destroy(Collection *c) {
    if (!c || !c->elements) {
        return;
    }
    for (size_t i = 0; i < c->size; i++) {
        free(c->elements[i]);
    }
    free(c->elements);
    c->elements = NULL;
    c->size = 0;
    c->capacity = 0;
}

char *remove_duplicate_words(const char *input) {
    if (!input) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    if (input_len == 0) {
        char *empty = malloc(1);
        if (empty) {
            empty[0] = '\0';
        }
        return empty;
    }

    char *input_copy = strdup(input);
    if (!input_copy) {
        return NULL;
    }

    char *result = malloc(input_len + 1);
    if (!result) {
        free(input_copy);
        return NULL;
    }
    result[0] = '\0';

    Collection word_set;
    if (!collection_init(&word_set, 16)) {
        free(result);
        free(input_copy);
        return NULL;
    }

    char *saveptr = NULL;
    char *token = strtok_r(input_copy, " \t\n\r", &saveptr);
    size_t current_len = 0;

    while (token != NULL) {
        if (!collection_contains(&word_set, token)) {
            if (!collection_add(&word_set, token)) {
                collection_destroy(&word_set);
                free(result);
                free(input_copy);
                return NULL;
            }
            
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t token_len = strlen(token);
            
            if (current_len > 0) {
                result[current_len++] = ' ';
            }
            
            if (current_len + token_len <= input_len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + current_len, token, token_len);
                current_len += token_len;
                result[current_len] = '\0';
            }
        }
        token = strtok_r(NULL, " \t\n\r", &saveptr);
    }

    free(input_copy);
    collection_destroy(&word_set);

    return result;
}

int main(void) {
    const char *test_string = "hello world hello C programming world C";
    
    char *unique_string = remove_duplicate_words(test_string);
    if (!unique_string) {
        fprintf(stderr, "Error processing string or memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", test_string);
    printf("Unique:   %s\n", unique_string);

    free(unique_string);
    return EXIT_SUCCESS;
}