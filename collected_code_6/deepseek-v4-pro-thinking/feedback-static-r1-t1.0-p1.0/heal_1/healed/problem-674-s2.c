#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **words;
    size_t count;
    size_t capacity;
} WordCollection;

static void collection_init(WordCollection *collection) {
    collection->words = NULL;
    collection->count = 0;
    collection->capacity = 0;
}

static void collection_free(WordCollection *collection) {
    free(collection->words);
    collection->words = NULL;
    collection->count = 0;
    collection->capacity = 0;
}

static int collection_contains(const WordCollection *collection, const char *word) {
    size_t i;
    for (i = 0; i < collection->count; ++i) {
        if (strcmp(collection->words[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

static int collection_add(WordCollection *collection, char *word) {
    if (collection->count == collection->capacity) {
        size_t new_capacity = collection->capacity == 0 ? 8 : collection->capacity * 2;
        char **new_words = realloc(collection->words, new_capacity * sizeof(char *));
        if (new_words == NULL) {
            return 0;
        }
        collection->words = new_words;
        collection->capacity = new_capacity;
    }
    collection->words[collection->count] = word;
    collection->count++;
    return 1;
}

static int append_word(char **result, size_t *length, size_t *capacity, const char *word) {
    size_t word_length = strlen(word);
    size_t needed = *length + word_length + 2;
    if (needed > *capacity) {
        size_t new_capacity = *capacity == 0 ? 64 : *capacity * 2;
        while (new_capacity < needed) {
            new_capacity *= 2;
        }
        char *new_result = realloc(*result, new_capacity);
        if (new_result == NULL) {
            return 0;
        }
        *result = new_result;
        *capacity = new_capacity;
    }
    if (*length > 0) {
        (*result)[(*length)++] = ' ';
    }
    memcpy(*result + *length, word, word_length);
    *length += word_length;
    (*result)[*length] = '\0';
    return 1;
}

char *remove_duplicate_words(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    char *copy = malloc(strlen(str) + 1);
    if (copy == NULL) {
        return NULL;
    }
    strcpy(copy, str);

    WordCollection seen;
    collection_init(&seen);

    char *result = NULL;
    size_t result_length = 0;
    size_t result_capacity = 0;

    char *p = copy;
    while (*p != '\0') {
        while (isspace((unsigned char)*p)) {
            p++;
        }
        if (*p == '\0') {
            break;
        }

        char *word = p;
        while (*p != '\0' && !isspace((unsigned char)*p)) {
            p++;
        }
        if (*p != '\0') {
            *p = '\0';
            p++;
        }

        if (!collection_contains(&seen, word)) {
            if (!append_word(&result, &result_length, &result_capacity, word)) {
                free(copy);
                collection_free(&seen);
                free(result);
                return NULL;
            }
            if (!collection_add(&seen, word)) {
                free(copy);
                collection_free(&seen);
                free(result);
                return NULL;
            }
        }
    }

    free(copy);
    collection_free(&seen);

    if (result == NULL) {
        result = malloc(1);
        if (result == NULL) {
            return NULL;
        }
        result[0] = '\0';
    }

    return result;
}

int main(void) {
    const char str[] = "this is a test this is only a test";
    char *result = remove_duplicate_words(str);
    if (result == NULL) {
        return 1;
    }
    printf("%s\n", result);
    free(result);
    return 0;
}