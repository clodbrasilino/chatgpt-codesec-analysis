#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char **words;
    size_t count;
    size_t capacity;
} WordCollection;

bool init_collection(WordCollection *collection, size_t initial_capacity) {
    if (!collection || initial_capacity == 0) {
        return false;
    }
    collection->words = malloc(initial_capacity * sizeof(char *));
    if (!collection->words) {
        return false;
    }
    collection->count = 0;
    collection->capacity = initial_capacity;
    return true;
}

void free_collection(WordCollection *collection) {
    if (collection) {
        for (size_t i = 0; i < collection->count; i++) {
            free(collection->words[i]);
        }
        free(collection->words);
        collection->words = NULL;
        collection->count = 0;
        collection->capacity = 0;
    }
}

bool contains_word(const WordCollection *collection, const char *word) {
    if (!collection || !word) {
        return false;
    }
    for (size_t i = 0; i < collection->count; i++) {
        if (strcmp(collection->words[i], word) == 0) {
            return true;
        }
    }
    return false;
}

bool add_word(WordCollection *collection, const char *word) {
    if (!collection || !word) {
        return false;
    }
    if (collection->count >= collection->capacity) {
        size_t new_capacity = collection->capacity * 2;
        char **new_words = realloc(collection->words, new_capacity * sizeof(char *));
        if (!new_words) {
            return false;
        }
        collection->words = new_words;
        collection->capacity = new_capacity;
    }
    
    char *word_copy = strdup(word);
    if (!word_copy) {
        return false;
    }
    
    collection->words[collection->count++] = word_copy;
    return true;
}

char *remove_duplicate_words(const char *input) {
    if (!input) {
        return NULL;
    }

    char *input_copy = strdup(input);
    if (!input_copy) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    char *result = calloc(input_len + 1, sizeof(char));
    if (!result) {
        free(input_copy);
        return NULL;
    }

    WordCollection seen_words;
    if (!init_collection(&seen_words, 10)) {
        free(input_copy);
        free(result);
        return NULL;
    }

    char *saveptr = NULL;
    char *token = strtok_r(input_copy, " \t\n", &saveptr);
    bool first_word = true;

    while (token != NULL) {
        if (!contains_word(&seen_words, token)) {
            if (!add_word(&seen_words, token)) {
                free_collection(&seen_words);
                free(input_copy);
                free(result);
                return NULL;
            }
            if (!first_word) {
                /* Possible weaknesses found:
                 * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                 * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. Risk is low because the source is a constant character. (risk 1, buffer)
                 */
                strncat(result, " ", input_len - strlen(result));
            }
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            strncat(result, token, input_len - strlen(result));
            first_word = false;
        }
        token = strtok_r(NULL, " \t\n", &saveptr);
    }

    free_collection(&seen_words);
    free(input_copy);
    return result;
}

int main(void) {
    const char *input_string = "hello world hello C programming world C";
    
    char *unique_string = remove_duplicate_words(input_string);
    if (!unique_string) {
        fprintf(stderr, "Memory allocation failed or invalid input.\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", input_string);
    printf("Unique:   %s\n", unique_string);

    free(unique_string);
    return EXIT_SUCCESS;
}