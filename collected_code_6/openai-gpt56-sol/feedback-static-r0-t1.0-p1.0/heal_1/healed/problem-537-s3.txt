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

static int word_equals(const Word *stored, const char *word, size_t length)
{
    return stored != NULL &&
           stored->length == length &&
           (length == 0 || memcmp(stored->data, word, length) == 0);
}

static int add_word(WordList *list, const char *word, size_t length)
{
    char *copy;

    if (list == NULL || word == NULL || length == SIZE_MAX) {
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

    copy = malloc(length + 1);
    if (copy == NULL) {
        return 0;
    }

    if (length != 0) {
        memcpy(copy, word, length);
    }
    copy[length] = '\0';

    list->items[list->count].data = copy;
    list->items[list->count].length = length;
    ++list->count;

    return 1;
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

    if (length != 0) {
        memcpy(copy, word, length);
    }
    copy[length] = '\0';

    return copy;
}

static char *find_first_repeated_word(const char *text)
{
    WordList words = {NULL, 0, 0};
    const unsigned char *cursor;

    if (text == NULL) {
        return NULL;
    }

    cursor = (const unsigned char *)text;

    while (*cursor != '\0') {
        const unsigned char *start;
        size_t length;
        size_t i;

        while (*cursor != '\0' && !isalnum(*cursor)) {
            ++cursor;
        }

        start = cursor;

        while (*cursor != '\0' && isalnum(*cursor)) {
            ++cursor;
        }

        length = (size_t)(cursor - start);
        if (length == 0) {
            continue;
        }

        for (i = 0; i < words.count; ++i) {
            if (word_equals(&words.items[i],
                            (const char *)start,
                            length)) {
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

static char *read_line(FILE *stream)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    if (stream == NULL) {
        return NULL;
    }

    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        char *new_buffer;
        size_t new_capacity;

        if (length == SIZE_MAX - 1) {
            free(buffer);
            return NULL;
        }

        if (length + 1 >= capacity) {
            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(buffer);
                    return NULL;
                }
                new_capacity = capacity * 2;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ferror(stream)) {
        free(buffer);
        return NULL;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return NULL;
    }

    if (length == SIZE_MAX) {
        free(buffer);
        return NULL;
    }

    if (length + 1 > capacity) {
        char *new_buffer = realloc(buffer, length + 1);

        if (new_buffer == NULL) {
            free(buffer);
            return NULL;
        }

        buffer = new_buffer;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input;
    char *repeated;

    input = read_line(stdin);
    if (input == NULL) {
        if (ferror(stdin)) {
            fprintf(stderr, "Failed to read input.\n");
            return EXIT_FAILURE;
        }

        if (feof(stdin)) {
            return EXIT_SUCCESS;
        }

        fprintf(stderr, "Failed to allocate memory.\n");
        return EXIT_FAILURE;
    }

    repeated = find_first_repeated_word(input);
    free(input);

    if (repeated != NULL) {
        printf("%s\n", repeated);
        free(repeated);
    } else {
        printf("No repeated word found.\n");
    }

    return EXIT_SUCCESS;
}