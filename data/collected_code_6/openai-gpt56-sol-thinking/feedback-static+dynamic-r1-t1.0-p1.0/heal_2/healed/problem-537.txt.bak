#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    FIND_SUCCESS,
    FIND_NOT_FOUND,
    FIND_INVALID_ARGUMENT,
    FIND_OUT_OF_MEMORY
} FindResult;

typedef struct {
    char *text;
    size_t length;
} Word;

static int is_word_character(unsigned char character)
{
    return isalnum(character) != 0 || character == '_';
}

static char *duplicate_range(const char *start, size_t length)
{
    char *copy;

    if (length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, start, length);
    copy[length] = '\0';

    return copy;
}

static void free_words(Word *words, size_t count)
{
    size_t index;

    for (index = 0; index < count; ++index) {
        free(words[index].text);
    }

    free(words);
}

static FindResult find_first_repeated_word(
    const char *input,
    char **repeated_word)
{
    Word *words = NULL;
    size_t word_count = 0;
    size_t capacity = 0;
    size_t position = 0;

    if (input == NULL || repeated_word == NULL) {
        return FIND_INVALID_ARGUMENT;
    }

    *repeated_word = NULL;

    while (input[position] != '\0') {
        size_t start;
        size_t length;
        size_t index;

        while (input[position] != '\0' &&
               !is_word_character((unsigned char)input[position])) {
            ++position;
        }

        if (input[position] == '\0') {
            break;
        }

        start = position;

        while (input[position] != '\0' &&
               is_word_character((unsigned char)input[position])) {
            ++position;
        }

        length = position - start;

        for (index = 0; index < word_count; ++index) {
            if (words[index].length == length &&
                memcmp(words[index].text, input + start, length) == 0) {
                *repeated_word = duplicate_range(input + start, length);

                if (*repeated_word == NULL) {
                    free_words(words, word_count);
                    return FIND_OUT_OF_MEMORY;
                }

                free_words(words, word_count);
                return FIND_SUCCESS;
            }
        }

        if (word_count == capacity) {
            size_t new_capacity;
            Word *new_words;

            if (capacity == 0) {
                new_capacity = 16;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free_words(words, word_count);
                    return FIND_OUT_OF_MEMORY;
                }

                new_capacity = capacity * 2;
            }

            if (new_capacity > SIZE_MAX / sizeof(*words)) {
                free_words(words, word_count);
                return FIND_OUT_OF_MEMORY;
            }

            new_words = realloc(words, new_capacity * sizeof(*words));
            if (new_words == NULL) {
                free_words(words, word_count);
                return FIND_OUT_OF_MEMORY;
            }

            words = new_words;
            capacity = new_capacity;
        }

        words[word_count].text = duplicate_range(input + start, length);
        if (words[word_count].text == NULL) {
            free_words(words, word_count);
            return FIND_OUT_OF_MEMORY;
        }

        words[word_count].length = length;
        ++word_count;
    }

    free_words(words, word_count);
    return FIND_NOT_FOUND;
}

static char *join_arguments(int argc, char *const argv[const])
{
    size_t total_size = 1;
    size_t offset = 0;
    char *input;
    int index;

    for (index = 1; index < argc; ++index) {
        size_t length = strlen(argv[index]);

        if (length > SIZE_MAX - total_size) {
            return NULL;
        }

        total_size += length;

        if (index < argc - 1) {
            if (total_size == SIZE_MAX) {
                return NULL;
            }

            ++total_size;
        }
    }

    input = malloc(total_size);
    if (input == NULL) {
        return NULL;
    }

    for (index = 1; index < argc; ++index) {
        size_t length = strlen(argv[index]);

        memcpy(input + offset, argv[index], length);
        offset += length;

        if (index < argc - 1) {
            input[offset++] = ' ';
        }
    }

    input[offset] = '\0';
    return input;
}

int main(int argc, char *argv[])
{
    char *input;
    char *repeated_word = NULL;
    FindResult result;
    int exit_status = EXIT_SUCCESS;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <text>\n", argv[0]);
        return EXIT_FAILURE;
    }

    input = join_arguments(argc, argv);
    if (input == NULL) {
        fprintf(stderr, "Unable to allocate memory for input.\n");
        return EXIT_FAILURE;
    }

    result = find_first_repeated_word(input, &repeated_word);

    switch (result) {
        case FIND_SUCCESS:
            if (printf("%s\n", repeated_word) < 0) {
                exit_status = EXIT_FAILURE;
            }
            break;

        case FIND_NOT_FOUND:
            if (printf("No repeated word found.\n") < 0) {
                exit_status = EXIT_FAILURE;
            }
            break;

        case FIND_OUT_OF_MEMORY:
            fprintf(stderr, "Unable to allocate memory.\n");
            exit_status = EXIT_FAILURE;
            break;

        case FIND_INVALID_ARGUMENT:
        default:
            fprintf(stderr, "Invalid argument.\n");
            exit_status = EXIT_FAILURE;
            break;
    }

    free(repeated_word);
    free(input);

    return exit_status;
}