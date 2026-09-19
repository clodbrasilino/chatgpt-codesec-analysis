#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
    size_t capacity;
} WordList;

typedef enum {
    FIND_ERROR = -1,
    FIND_NONE = 0,
    FIND_FOUND = 1
} FindResult;

static void free_word_list(WordList *list)
{
    size_t i;

    if (list == NULL) {
        return;
    }

    for (i = 0; i < list->count; ++i) {
        free(list->items[i]);
    }

    free(list->items);
    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
}

static int word_equals(const char *stored, const char *word, size_t length)
{
    return strlen(stored) == length && memcmp(stored, word, length) == 0;
}

static int add_word(WordList *list, const char *word, size_t length)
{
    char *copy;

    if (list == NULL || word == NULL || length == SIZE_MAX) {
        return 0;
    }

    if (list->count == list->capacity) {
        size_t new_capacity;
        char **new_items;

        if (list->capacity == 0) {
            new_capacity = 8;
        } else {
            if (list->capacity > SIZE_MAX / 2) {
                return 0;
            }
            new_capacity = list->capacity * 2;
        }

        if (new_capacity > SIZE_MAX / sizeof(*new_items)) {
            return 0;
        }

        new_items = realloc(list->items,
                            new_capacity * sizeof(*new_items));
        if (new_items == NULL) {
            return 0;
        }

        list->items = new_items;
        list->capacity = new_capacity;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return 0;
    }

    memcpy(copy, word, length);
    copy[length] = '\0';
    list->items[list->count++] = copy;

    return 1;
}

static FindResult find_first_repeated_word(const char *text, char **result)
{
    WordList words = {NULL, 0, 0};
    const char *cursor;

    if (result == NULL) {
        return FIND_ERROR;
    }

    *result = NULL;

    if (text == NULL) {
        return FIND_ERROR;
    }

    cursor = text;

    while (*cursor != '\0') {
        const char *start;
        size_t length;
        size_t i;

        while (*cursor != '\0' &&
               !isalnum((unsigned char)*cursor)) {
            ++cursor;
        }

        start = cursor;

        while (*cursor != '\0' &&
               isalnum((unsigned char)*cursor)) {
            ++cursor;
        }

        length = (size_t)(cursor - start);
        if (length == 0) {
            continue;
        }

        for (i = 0; i < words.count; ++i) {
            if (word_equals(words.items[i], start, length)) {
                char *copy;

                if (length == SIZE_MAX) {
                    free_word_list(&words);
                    return FIND_ERROR;
                }

                copy = malloc(length + 1);
                if (copy == NULL) {
                    free_word_list(&words);
                    return FIND_ERROR;
                }

                memcpy(copy, start, length);
                copy[length] = '\0';
                *result = copy;
                free_word_list(&words);
                return FIND_FOUND;
            }
        }

        if (!add_word(&words, start, length)) {
            free_word_list(&words);
            return FIND_ERROR;
        }
    }

    free_word_list(&words);
    return FIND_NONE;
}

int main(void)
{
    char input[4096];
    char *repeated = NULL;
    FindResult status;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        if (ferror(stdin)) {
            fprintf(stderr, "Failed to read input.\n");
            return EXIT_FAILURE;
        }

        printf("None\n");
        return EXIT_SUCCESS;
    }

    status = find_first_repeated_word(input, &repeated);

    if (status == FIND_FOUND) {
        printf("%s\n", repeated);
        free(repeated);
    } else if (status == FIND_NONE) {
        printf("None\n");
    } else {
        fprintf(stderr, "Unable to process input.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}