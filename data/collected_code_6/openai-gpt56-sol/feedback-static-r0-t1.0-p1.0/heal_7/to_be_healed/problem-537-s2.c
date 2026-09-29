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

static char *copy_word(const char *word, size_t length)
{
    char *copy;

    if (word == NULL || length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    if (length > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, word, length);
    }

    copy[length] = '\0';
    return copy;
}

static int grow_word_list(WordList *list)
{
    size_t new_capacity;
    Word *new_items;

    if (list == NULL) {
        return 0;
    }

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
    return 1;
}

static int add_word(WordList *list, const char *word, size_t length)
{
    char *copy;

    if (list == NULL || word == NULL) {
        return 0;
    }

    if (list->count == list->capacity && !grow_word_list(list)) {
        return 0;
    }

    if (list->count >= list->capacity) {
        return 0;
    }

    copy = copy_word(word, length);
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
    WordList words = { NULL, 0, 0 };
    const unsigned char *cursor;

    if (text == NULL) {
        return NULL;
    }

    cursor = (const unsigned char *)text;

    while (*cursor != '\0') {
        const unsigned char *start;
        size_t length;
        size_t i;

        while (*cursor != '\0' && !isalnum((int)*cursor)) {
            ++cursor;
        }

        if (*cursor == '\0') {
            break;
        }

        start = cursor;

        while (*cursor != '\0' && isalnum((int)*cursor)) {
            ++cursor;
        }

        length = (size_t)(cursor - start);

        for (i = 0; i < words.count; ++i) {
            if (words.items[i].length == length &&
                memcmp(words.items[i].data, start, length) == 0) {
                char *result = copy_word((const char *)start, length);
                free_word_list(&words);
                return result;
            }
        }

        if (!add_word(&words, (const char *)start, length)) {
            free_word_list(&words);
            return NULL;
        }
    }

    free_word_list(&words);
    return NULL;
}

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *new_buffer;

    if (buffer == NULL || capacity == NULL) {
        return 0;
    }

    if (required <= *capacity) {
        return 1;
    }

    new_capacity = (*capacity == 0) ? 128 : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }
        new_capacity *= 2;
    }

    if (new_capacity < required) {
        return 0;
    }

    new_buffer = realloc(*buffer, new_capacity);
    if (new_buffer == NULL) {
        return 0;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return 1;
}

static char *read_line(FILE *stream)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    if (stream == NULL) {
        return NULL;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (length > SIZE_MAX - 2) {
            free(buffer);
            return NULL;
        }

        if (!grow_buffer(&buffer, &capacity, length + 2)) {
            free(buffer);
            return NULL;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    if (ch == EOF && ferror(stream)) {
        free(buffer);
        return NULL;
    }

    if (!grow_buffer(&buffer, &capacity, length + 1)) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input;
    char *repeated_word;

    input = read_line(stdin);
    if (input == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
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