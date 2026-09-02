#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 16

typedef struct {
    char **words;
    size_t count;
    size_t capacity;
} WordList;

static int word_exists(WordList *list, const char *word) {
    size_t i;
    for (i = 0; i < list->count; i++) {
        if (strcmp(list->words[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

static int add_word(WordList *list, const char *word) {
    char *copy;
    char **new_words;
    size_t new_capacity;

    if (word_exists(list, word)) {
        return 0;
    }

    if (list->count == list->capacity) {
        new_capacity = list->capacity * 2;
        new_words = realloc(list->words, new_capacity * sizeof(char *));
        if (new_words == NULL) {
            return -1;
        }
        list->words = new_words;
        list->capacity = new_capacity;
    }

    copy = malloc(strlen(word) + 1);
    if (copy == NULL) {
        return -1;
    }
    strcpy(copy, word);
    list->words[list->count] = copy;
    list->count++;
    return 0;
}

static void free_word_list(WordList *list) {
    size_t i;
    for (i = 0; i < list->count; i++) {
        free(list->words[i]);
    }
    free(list->words);
    list->words = NULL;
    list->count = 0;
    list->capacity = 0;
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
        if (words[i] == NULL) {
            continue;
        }
        if (add_word(&unique, words[i]) != 0) {
            free_word_list(&unique);
            *result_count = 0;
            return NULL;
        }
    }

    result = malloc(unique.count * sizeof(char *));
    if (result == NULL && unique.count > 0) {
        free_word_list(&unique);
        *result_count = 0;
        return NULL;
    }

    for (i = 0; i < (int)unique.count; i++) {
        result[i] = unique.words[i];
    }

    free(unique.words);
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

    if (unique_words == NULL) {
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