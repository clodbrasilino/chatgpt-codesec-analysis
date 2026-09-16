#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *duplicate_string(const char *s) {
    if (s == NULL) {
        return NULL;
    }

    size_t len = strlen(s);
    char *copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, s, len + 1);
    return copy;
}

static int string_in_list(const char *str, const char *const *list, size_t count) {
    if (str == NULL || list == NULL) {
        return 0;
    }

    for (size_t i = 0; i < count; i++) {
        if (list[i] != NULL && strcmp(str, list[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

int remove_specific_words(char ***word_list, size_t *word_count,
                          const char *const *remove_words, size_t remove_count) {
    if (word_list == NULL || word_count == NULL) {
        return -1;
    }

    if (*word_list == NULL && *word_count != 0) {
        return -1;
    }

    if (remove_words == NULL && remove_count != 0) {
        return -1;
    }

    char **words = *word_list;
    size_t count = *word_count;
    size_t write = 0;

    for (size_t i = 0; i < count; i++) {
        if (words[i] != NULL && string_in_list(words[i], remove_words, remove_count)) {
            free(words[i]);
            words[i] = NULL;
        } else {
            if (write != i) {
                words[write] = words[i];
                words[i] = NULL;
            }
            write++;
        }
    }

    *word_count = write;

    if (write == 0) {
        free(words);
        *word_list = NULL;
        return 0;
    }

    char **new_words = realloc(words, write * sizeof(*words));
    if (new_words != NULL) {
        *word_list = new_words;
    }

    return 0;
}

int main(void) {
    const char *initial[] = {
        "apple", "banana", "cherry", "date", "banana", "elderberry"
    };
    size_t count = sizeof(initial) / sizeof(initial[0]);

    char **words = malloc(count * sizeof(*words));
    if (words == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        words[i] = duplicate_string(initial[i]);
        if (words[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(words[j]);
            }
            free(words);
            return EXIT_FAILURE;
        }
    }

    const char *remove_words[] = { "banana", "date" };
    size_t remove_count = sizeof(remove_words) / sizeof(remove_words[0]);

    if (remove_specific_words(&words, &count, remove_words, remove_count) != 0) {
        fprintf(stderr, "Error removing words\n");
        for (size_t i = 0; i < count; i++) {
            free(words[i]);
        }
        free(words);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", words[i] != NULL ? words[i] : "(null)");
    }

    for (size_t i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);

    return EXIT_SUCCESS;
}