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
        free(list->items[i].data);
    }

    free(list->items);
    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
}

static int word_equals(const Word *stored, const char *word, size_t length)
{
    if (stored == NULL || word == NULL || stored->length != length) {
        return 0;
    }

    return length == 0 || memcmp(stored->data, word, length) == 0;
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
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, word, length);
    }
    copy[length] = '\0';

    return copy;
}

static int reserve_words(WordList *list, size_t required)
{
    size_t new_capacity;
    Word *new_items;

    if (list == NULL) {
        return 0;
    }

    if (required <= list->capacity) {
        return 1;
    }

    new_capacity = list->capacity == 0 ? 8 : list->capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }
        new_capacity *= 2;
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

    if (list == NULL || word == NULL || list->count == SIZE_MAX) {
        return 0;
    }

    if (!reserve_words(list, list->count + 1)) {
        return 0;
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

        while (*cursor != '\0' && !isalnum((unsigned char)*cursor)) {
            ++cursor;
        }

        start = cursor;

        while (*cursor != '\0' && isalnum((unsigned char)*cursor)) {
            ++cursor;
        }

        length = (size_t)(cursor - start);
        if (length == 0) {
            continue;
        }

        for (i = 0; i < words.count; ++i) {
            if (word_equals(&words.items[i], start, length)) {
                *result = duplicate_word(start, length);
                free_word_list(&words);
                return *result == NULL ? FIND_ERROR : FIND_FOUND;
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

    new_capacity = *capacity == 0 ? 4096 : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }
        new_capacity *= 2;
    }

    new_buffer = realloc(*buffer, new_capacity);
    if (new_buffer == NULL) {
        return 0;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return 1;
}

static char *read_all_input(FILE *stream)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;

    if (stream == NULL) {
        return NULL;
    }

    for (;;) {
        size_t available;
        size_t bytes_read;

        if (capacity - length < 2) {
            if (length == SIZE_MAX) {
                free(buffer);
                return NULL;
            }

            if (!grow_buffer(&buffer, &capacity, length + 2)) {
                free(buffer);
                return NULL;
            }
        }

        available = capacity - length - 1;
        bytes_read = fread(buffer + length, 1, available, stream);
        length += bytes_read;

        if (bytes_read < available) {
            if (ferror(stream)) {
                free(buffer);
                return NULL;
            }

            if (feof(stream)) {
                break;
            }
        }
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input;
    char *repeated = NULL;
    FindResult status;

    input = read_all_input(stdin);
    if (input == NULL) {
        fprintf(stderr, "Failed to read or allocate input.\n");
        return EXIT_FAILURE;
    }

    status = find_first_repeated_word(input, &repeated);
    free(input);

    if (status == FIND_ERROR) {
        free(repeated);
        fprintf(stderr, "Failed to process input.\n");
        return EXIT_FAILURE;
    }

    if (status == FIND_FOUND) {
        printf("%s\n", repeated);
        free(repeated);
    } else {
        puts("None");
    }

    return EXIT_SUCCESS;
}