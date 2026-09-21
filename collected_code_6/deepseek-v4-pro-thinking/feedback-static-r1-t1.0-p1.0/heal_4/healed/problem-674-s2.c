#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN ((size_t)1 << 30)

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

static int append_word(char **result, size_t *length, size_t *capacity,
                       const char *word, size_t word_len) {
    size_t needed = *length + word_len + 2;
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
    if (*length + word_len > *capacity) {
        return 0;
    }
    memmove(*result + *length, word, word_len);
    *length += word_len;
    (*result)[*length] = '\0';
    return 1;
}

char *remove_duplicate_words(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    char *copy = NULL;
    size_t copy_capacity = 0;
    size_t copy_length = 0;

    const char *p = str;
    while (*p != '\0') {
        if (copy_length >= MAX_INPUT_LEN) {
            free(copy);
            return NULL;
        }
        if (copy_length + 1 > copy_capacity) {
            size_t new_cap = copy_capacity == 0 ? 64 : copy_capacity * 2;
            if (new_cap < copy_length + 1) {
                new_cap = copy_length + 1;
            }
            char *new_copy = realloc(copy, new_cap);
            if (new_copy == NULL) {
                free(copy);
                return NULL;
            }
            copy = new_copy;
            copy_capacity = new_cap;
        }
        copy[copy_length++] = *p++;
    }
    if (copy_length + 1 > copy_capacity) {
        size_t new_cap = copy_capacity == 0 ? 1 : copy_capacity * 2;
        if (new_cap < copy_length + 1) {
            new_cap = copy_length + 1;
        }
        char *new_copy = realloc(copy, new_cap);
        if (new_copy == NULL) {
            free(copy);
            return NULL;
        }
        copy = new_copy;
        copy_capacity = new_cap;
    }
    copy[copy_length] = '\0';

    WordCollection seen;
    collection_init(&seen);

    char *result = NULL;
    size_t result_length = 0;
    size_t result_capacity = 0;

    char *token_p = copy;
    while (*token_p != '\0') {
        while (isspace((unsigned char)*token_p)) {
            token_p++;
        }
        if (*token_p == '\0') {
            break;
        }

        char *word = token_p;
        while (*token_p != '\0' && !isspace((unsigned char)*token_p)) {
            token_p++;
        }
        size_t word_len = (size_t)(token_p - word);
        if (*token_p != '\0') {
            *token_p = '\0';
            token_p++;
        }

        if (!collection_contains(&seen, word)) {
            if (!append_word(&result, &result_length, &result_capacity,
                             word, word_len)) {
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