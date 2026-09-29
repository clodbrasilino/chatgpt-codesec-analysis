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
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, word, length);
    }
    copy[length] = '\0';

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
            if (word_equals(&words.items[i], start, length)) {
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

                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
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

static char *read_all_input(FILE *stream)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char chunk[4096];

    for (;;) {
        size_t bytes_read = fread(chunk, 1, sizeof(chunk), stream);

        if (bytes_read != 0) {
            size_t required;

            if (length > SIZE_MAX - bytes_read - 1) {
                free(buffer);
                return NULL;
            }

            required = length + bytes_read + 1;

            if (required > capacity) {
                size_t new_capacity = capacity == 0 ? 4096 : capacity;
                char *new_buffer;

                while (new_capacity < required) {
                    if (new_capacity > SIZE_MAX / 2) {
                        new_capacity = required;
                        break;
                    }
                    new_capacity *= 2;
                }

                new_buffer = realloc(buffer, new_capacity);
                if (new_buffer == NULL) {
                    free(buffer);
                    return NULL;
                }

                buffer = new_buffer;
                capacity = new_capacity;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(buffer + length, chunk, bytes_read);
            length += bytes_read;
        }

        if (bytes_read < sizeof(chunk)) {
            if (ferror(stream)) {
                free(buffer);
                return NULL;
            }
            break;
        }
    }

    if (buffer == NULL) {
        buffer = malloc(1);
        if (buffer == NULL) {
            return NULL;
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
        fprintf(stderr, "Failed to process input.\n");
        return EXIT_FAILURE;
    }

    if (status == FIND_FOUND) {
        printf("%s\n", repeated);
        free(repeated);
    } else {
        printf("None\n");
    }

    return EXIT_SUCCESS;
}