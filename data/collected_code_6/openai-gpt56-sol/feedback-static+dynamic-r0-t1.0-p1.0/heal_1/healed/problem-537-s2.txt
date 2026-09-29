#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *data;
    size_t length;
} Word;

typedef struct {
    Word *items;
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
        free(list->items[i].data);
    }

    free(list->items);
    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
}

static char *duplicate_word(const char *word, size_t length)
{
    char *copy;

    if (word == NULL || length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    if (length != 0) {
        memcpy(copy, word, length);
    }
    copy[length] = '\0';

    return copy;
}

static int add_word(WordList *list, const char *word, size_t length)
{
    char *copy;

    if (list == NULL || word == NULL) {
        return 0;
    }

    if (list->count == list->capacity) {
        size_t new_capacity;
        Word *new_items;

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

    copy = duplicate_word(word, length);
    if (copy == NULL) {
        return 0;
    }

    list->items[list->count].data = copy;
    list->items[list->count].length = length;
    ++list->count;

    return 1;
}

static char *find_first_repeated_word(const char *text)
{
    WordList words = {NULL, 0, 0};
    const char *cursor;

    if (text == NULL) {
        return NULL;
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

        if (*cursor == '\0') {
            break;
        }

        start = cursor;

        while (*cursor != '\0' &&
               isalnum((unsigned char)*cursor)) {
            ++cursor;
        }

        length = (size_t)(cursor - start);

        for (i = 0; i < words.count; ++i) {
            if (words.items[i].length == length &&
                memcmp(words.items[i].data, start, length) == 0) {
                char *result = duplicate_word(start, length);

                free_word_list(&words);
                return result;
            }
        }

        if (!add_word(&words, start, length)) {
            free_word_list(&words);
            return NULL;
        }
    }

    free_word_list(&words);
    return NULL;
}

static char *read_line(FILE *stream, int *status)
{
    char *buffer;
    size_t length = 0;
    size_t capacity = 128;
    int ch;

    if (stream == NULL || status == NULL) {
        return NULL;
    }

    *status = 0;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        *status = -1;
        return NULL;
    }

    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (length == SIZE_MAX - 1) {
            free(buffer);
            *status = -1;
            return NULL;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                *status = -1;
                return NULL;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                *status = -1;
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ferror(stream)) {
        free(buffer);
        *status = -1;
        return NULL;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    *status = 1;
    return buffer;
}

int main(void)
{
    char *input;
    char *repeated_word;
    int status;

    input = read_line(stdin, &status);
    if (input == NULL) {
        if (status < 0) {
            fprintf(stderr, "Failed to read input.\n");
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    repeated_word = find_first_repeated_word(input);
    free(input);

    if (repeated_word != NULL) {
        puts(repeated_word);
        free(repeated_word);
    } else {
        puts("No repeated word found.");
    }

    return EXIT_SUCCESS;
}