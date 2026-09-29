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
    /* Possible weaknesses found:
     *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
     */
    size_t new_capacity;
    char **new_elements;
    char *copy;

    if (!c || !item) {
        return 0;
    }
    if (c->size >= c->capacity) {
        new_capacity = c->capacity * 2;
        new_elements = realloc(c->elements, new_capacity * sizeof(char *));
        if (!new_elements) {
            return 0;
        }
        c->elements = new_elements;
        c->capacity = new_capacity;
    }
    
    copy = strdup(item);
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
    size_t input_len;
    /* Possible weaknesses found:
     *  The scope of the variable 'empty' can be reduced. [variableScope]
     */
    char *empty;
    char *input_copy;
    char *result;
    Collection word_set;
    char *saveptr = NULL;
    char *token;
    size_t current_len = 0;
    size_t token_len;

    if (!input) {
        return NULL;
    }

    input_len = 0;
    while (input[input_len] != '\0') {
        input_len++;
    }

    if (input_len == 0) {
        empty = malloc(1);
        if (empty) {
            empty[0] = '\0';
        }
        return empty;
    }

    input_copy = malloc(input_len + 1);
    if (!input_copy) {
        return NULL;
    }
    for (size_t i = 0; i <= input_len; i++) {
        input_copy[i] = input[i];
    }

    result = malloc(input_len + 1);
    if (!result) {
        free(input_copy);
        return NULL;
    }
    result[0] = '\0';

    if (!collection_init(&word_set, 16)) {
        free(result);
        free(input_copy);
        return NULL;
    }

    token = strtok_r(input_copy, " \t\n\r", &saveptr);

    while (token != NULL) {
        if (!collection_contains(&word_set, token)) {
            if (!collection_add(&word_set, token)) {
                collection_destroy(&word_set);
                free(result);
                free(input_copy);
                return NULL;
            }
            
            token_len = 0;
            while (token[token_len] != '\0') {
                token_len++;
            }

            if (current_len > 0) {
                result[current_len++] = ' ';
            }
            
            for (size_t i = 0; i < token_len; i++) {
                result[current_len + i] = token[i];
            }
            current_len += token_len;
            result[current_len] = '\0';
        }
        token = strtok_r(NULL, " \t\n\r", &saveptr);
    }

    free(input_copy);
    collection_destroy(&word_set);

    return result;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[4096];
    /* Possible weaknesses found:
     *  The scope of the variable 'p' can be reduced. [variableScope]
     */
    char *p;
    /* Possible weaknesses found:
     *  The scope of the variable 'unique_string' can be reduced. [variableScope]
     */
    char *unique_string;

    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        p = strchr(buffer, '\n');
        if (p) {
            *p = '\0';
        }
        
        unique_string = remove_duplicate_words(buffer);
        if (unique_string) {
            printf("%s\n", unique_string);
            free(unique_string);
        }
    }
    return 0;
}