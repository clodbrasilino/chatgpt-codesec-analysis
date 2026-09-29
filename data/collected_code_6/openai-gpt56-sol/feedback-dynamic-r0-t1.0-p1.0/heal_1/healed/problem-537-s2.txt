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

        new_items = realloc(list->items, new_capacity * sizeof(*new_items));
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

static int find_first_repeated_word(const char *text, char **result)
{
    WordList words = {NULL, 0, 0};
    const char *cursor;

    if (result == NULL) {
        return -1;
    }

    *result = NULL;

    if (text == NULL) {
        return 0;
    }

    cursor = text;

    while (*cursor != '\0') {
        const char *start;
        size_t length;
        size_t i;

        while (*cursor != '\0' && !isalnum((unsigned char)*cursor)) {
            ++cursor;
        }

        if (*cursor == '\0') {
            break;
        }

        start = cursor;

        while (*cursor != '\0' && isalnum((unsigned char)*cursor)) {
            ++cursor;
        }

        length = (size_t)(cursor - start);

        for (i = 0; i < words.count; ++i) {
            if (strlen(words.items[i]) == length &&
                memcmp(words.items[i], start, length) == 0) {
                char *copy = malloc(length + 1);

                if (copy == NULL) {
                    free_word_list(&words);
                    return -1;
                }

                memcpy(copy, start, length);
                copy[length] = '\0';
                *result = copy;
                free_word_list(&words);
                return 1;
            }
        }

        if (!add_word(&words, start, length)) {
            free_word_list(&words);
            return -1;
        }
    }

    free_word_list(&words);
    return 0;
}

int main(void)
{
    char input[4096];
    char *repeated_word = NULL;
    int status;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        if (ferror(stdin)) {
            fprintf(stderr, "Failed to read input.\n");
            return EXIT_FAILURE;
        }

        printf("None\n");
        return EXIT_SUCCESS;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        fprintf(stderr, "Input is too long.\n");
        return EXIT_FAILURE;
    }

    status = find_first_repeated_word(input, &repeated_word);

    if (status < 0) {
        fprintf(stderr, "Failed to process input.\n");
        return EXIT_FAILURE;
    }

    if (status == 1) {
        printf("%s\n", repeated_word);
        free(repeated_word);
    } else {
        printf("None\n");
    }

    return EXIT_SUCCESS;
}