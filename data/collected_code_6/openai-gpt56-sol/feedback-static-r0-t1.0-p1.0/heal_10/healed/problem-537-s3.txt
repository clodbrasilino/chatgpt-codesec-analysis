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
    SEARCH_ERROR = -1,
    SEARCH_NOT_FOUND = 0,
    SEARCH_FOUND = 1
} SearchResult;

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

    if (length == 0) {
        return 1;
    }

    return stored->data != NULL &&
           memcmp(stored->data, word, length) == 0;
}

static char *duplicate_word(const char *word, size_t length)
{
    char *copy;

    if (word == NULL || length > SIZE_MAX - 1) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    if (length > 0) {
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

    if (list->count < list->capacity) {
        return 1;
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

    copy = duplicate_word(word, length);
    if (copy == NULL) {
        return 0;
    }

    if (!grow_word_list(list)) {
        free(copy);
        return 0;
    }

    list->items[list->count].data = copy;
    list->items[list->count].length = length;
    ++list->count;

    return 1;
}

static SearchResult find_first_repeated_word(const char *text, char **result)
{
    WordList words = {NULL, 0, 0};
    const unsigned char *cursor;

    if (result == NULL) {
        return SEARCH_ERROR;
    }

    *result = NULL;

    if (text == NULL) {
        return SEARCH_ERROR;
    }

    cursor = (const unsigned char *)text;

    while (*cursor != '\0') {
        const unsigned char *start;
        size_t length;
        size_t i;

        while (*cursor != '\0' && !isalnum((int)*cursor)) {
            ++cursor;
        }

        start = cursor;

        while (*cursor != '\0' && isalnum((int)*cursor)) {
            ++cursor;
        }

        length = (size_t)(cursor - start);
        if (length == 0) {
            continue;
        }

        for (i = 0; i < words.count; ++i) {
            if (word_equals(&words.items[i], (const char *)start, length)) {
                char *copy = duplicate_word((const char *)start, length);

                if (copy == NULL) {
                    free_word_list(&words);
                    return SEARCH_ERROR;
                }

                free_word_list(&words);
                *result = copy;
                return SEARCH_FOUND;
            }
        }

        if (!add_word(&words, (const char *)start, length)) {
            free_word_list(&words);
            return SEARCH_ERROR;
        }
    }

    free_word_list(&words);
    return SEARCH_NOT_FOUND;
}

static int read_line(FILE *stream, char **result)
{
    char *buffer;
    size_t length = 0;
    size_t capacity = 128;

    if (stream == NULL || result == NULL) {
        return -1;
    }

    *result = NULL;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        int ch;

        if (length >= capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            if (new_capacity <= length + 1 ||
                new_capacity > SIZE_MAX / sizeof(*buffer)) {
                free(buffer);
                return -1;
            }

            new_buffer = realloc(buffer, new_capacity * sizeof(*buffer));
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream)) {
                free(buffer);
                return -1;
            }

            if (length == 0) {
                free(buffer);
                return 0;
            }

            break;
        }

        if (ch == '\n') {
            break;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *result = buffer;
    return 1;
}

int main(void)
{
    char *input = NULL;
    char *repeated = NULL;
    int read_status;
    SearchResult search_status;

    read_status = read_line(stdin, &input);
    if (read_status < 0) {
        fputs("Failed to read input or allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    if (read_status == 0) {
        return EXIT_SUCCESS;
    }

    search_status = find_first_repeated_word(input, &repeated);
    free(input);

    if (search_status == SEARCH_ERROR) {
        fputs("Failed to process input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (search_status == SEARCH_FOUND) {
        int print_status = printf("%s\n", repeated);

        free(repeated);

        if (print_status < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (puts("No repeated word found.") == EOF) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}