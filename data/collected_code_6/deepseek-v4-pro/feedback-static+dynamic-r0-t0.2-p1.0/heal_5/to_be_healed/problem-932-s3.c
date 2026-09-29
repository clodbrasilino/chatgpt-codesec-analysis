#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 16

typedef struct {
    char **words;
    size_t count;
    size_t capacity;
} WordList;

static int word_exists(WordList *list, const char *word, size_t word_len) {
    size_t i;
    for (i = 0; i < list->count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (strlen(list->words[i]) == word_len &&
            memcmp(list->words[i], word, word_len) == 0) {
            return 1;
        }
    }
    return 0;
}

static int add_word(WordList *list, const char *word, size_t word_len) {
    char *copy;

    if (word == NULL) {
        return -1;
    }

    if (word_exists(list, word, word_len)) {
        return 0;
    }

    if (list->count == list->capacity) {
        size_t new_capacity = list->capacity * 2;
        size_t new_size;
        char **new_words;

        if (new_capacity < list->capacity ||
            new_capacity > SIZE_MAX / sizeof(char *)) {
            return -1;
        }
        new_size = new_capacity * sizeof(char *);
        new_words = realloc(list->words, new_size);
        if (new_words == NULL) {
            return -1;
        }
        list->words = new_words;
        list->capacity = new_capacity;
    }

    if (word_len > SIZE_MAX - 1) {
        return -1;
    }

    copy = malloc(word_len + 1);
    if (copy == NULL) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, word, word_len);
    copy[word_len] = '\0';
    list->words[list->count] = copy;
    list->count++;
    return 0;
}

static void free_word_list(WordList *list) {
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;
    if (list->words != NULL) {
        for (i = 0; i < list->count; i++) {
            free(list->words[i]);
        }
        free(list->words);
    }
    list->words = NULL;
    list->count = 0;
    list->capacity = 0;
}

static size_t strnlen_safe(const char *str, size_t maxlen) {
    size_t i;
    for (i = 0; i < maxlen; i++) {
        if (str[i] == '\0') {
            return i;
        }
    }
    return maxlen;
}

char **remove_duplicate_words(char **words, int word_count, int *result_count) {
    WordList unique;
    int i;
    char **result;

    if (words == NULL || word_count <= 0 || result_count == NULL) {
        if (result_count != NULL) {
            *result_count = 0;
        }
        return NULL;
    }

    unique.words = malloc(INITIAL_CAPACITY * sizeof(char *));
    if (unique.words == NULL) {
        *result_count = 0;
        return NULL;
    }
    unique.count = 0;
    unique.capacity = INITIAL_CAPACITY;

    for (i = 0; i < word_count; i++) {
        size_t word_len;
        if (words[i] == NULL) {
            continue;
        }
        word_len = strnlen_safe(words[i], SIZE_MAX - 1);
        if (add_word(&unique, words[i], word_len) != 0) {
            free_word_list(&unique);
            *result_count = 0;
            return NULL;
        }
    }

    if (unique.count > 0) {
        result = malloc(unique.count * sizeof(char *));
        if (result == NULL) {
            free_word_list(&unique);
            *result_count = 0;
            return NULL;
        }
    } else {
        result = NULL;
    }

    for (i = 0; i < (int)unique.count; i++) {
        result[i] = unique.words[i];
    }

    free(unique.words);
    unique.words = NULL;
    *result_count = (int)unique.count;
    return result;
}

int main(void) {
    char *words[] = {"apple", "banana", "apple", "cherry", "banana", "date", "apple"};
    int word_count = sizeof(words) / sizeof(words[0]);
    int result_count = 0;
    char **unique_words;
    int i;

    unique_words = remove_duplicate_words(words, word_count, &result_count);

    if (unique_words == NULL && result_count > 0) {
        fprintf(stderr, "Failed to remove duplicate words\n");
        return 1;
    }

    printf("Unique words (%d):\n", result_count);
    for (i = 0; i < result_count; i++) {
        printf("%s\n", unique_words[i]);
    }

    for (i = 0; i < result_count; i++) {
        free(unique_words[i]);
    }
    free(unique_words);

    return 0;
}