#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    FIND_SUCCESS,
    FIND_NOT_FOUND,
    FIND_INVALID_ARGUMENT,
    FIND_OUT_OF_MEMORY
} FindResult;

typedef struct {
    const char *text;
    size_t length;
} Word;

static int is_word_character(unsigned char character)
{
    return isalnum(character) != 0 || character == '_';
}

static size_t string_length(const char *string)
{
    const char *current = string;

    while (*current != '\0') {
        ++current;
    }

    return (size_t)(current - string);
}

static char *duplicate_range(const char *start, size_t length)
{
    char *copy;
    size_t index;

    if (start == NULL || length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    for (index = 0; index < length; ++index) {
        copy[index] = start[index];
    }

    copy[length] = '\0';
    return copy;
}

FindResult find_first_repeated_word(const char *input, char **repeated_word)
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
            size_t character_index;

            if (words[index].length != length) {
                continue;
            }

            for (character_index = 0;
                 character_index < length;
                 ++character_index) {
                if (words[index].text[character_index] !=
                    input[start + character_index]) {
                    break;
                }
            }

            if (character_index == length) {
                *repeated_word = duplicate_range(input + start, length);
                if (*repeated_word == NULL) {
                    free(words);
                    return FIND_OUT_OF_MEMORY;
                }

                free(words);
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
                    free(words);
                    return FIND_OUT_OF_MEMORY;
                }

                new_capacity = capacity * 2;
            }

            if (new_capacity > SIZE_MAX / sizeof(*words)) {
                free(words);
                return FIND_OUT_OF_MEMORY;
            }

            new_words = realloc(words, new_capacity * sizeof(*words));
            if (new_words == NULL) {
                free(words);
                return FIND_OUT_OF_MEMORY;
            }

            words = new_words;
            capacity = new_capacity;
        }

        words[word_count].text = input + start;
        words[word_count].length = length;
        ++word_count;
    }

    free(words);
    return FIND_NOT_FOUND;
}

static char *join_arguments(int argc, char *const argv[])
{
    size_t total_size = 1;
    size_t offset = 0;
    char *input;
    int argument_index;

    if (argc < 1 || argv == NULL) {
        return NULL;
    }

    for (argument_index = 1; argument_index < argc; ++argument_index) {
        size_t length;

        if (argv[argument_index] == NULL) {
            return NULL;
        }

        length = string_length(argv[argument_index]);

        if (length > SIZE_MAX - total_size) {
            return NULL;
        }

        total_size += length;

        if (argument_index < argc - 1) {
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

    for (argument_index = 1; argument_index < argc; ++argument_index) {
        const char *argument = argv[argument_index];

        while (*argument != '\0') {
            input[offset++] = *argument++;
        }

        if (argument_index < argc - 1) {
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
    int exit_status;

    if (argc < 2) {
        (void)fprintf(stderr, "Usage: %s <text>\n",
                      argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    input = join_arguments(argc, argv);
    if (input == NULL) {
        (void)fprintf(stderr, "Unable to allocate or construct input.\n");
        return EXIT_FAILURE;
    }

    result = find_first_repeated_word(input, &repeated_word);

    switch (result) {
        case FIND_SUCCESS:
            exit_status = printf("%s\n", repeated_word) < 0
                              ? EXIT_FAILURE
                              : EXIT_SUCCESS;
            break;

        case FIND_NOT_FOUND:
            exit_status = printf("No repeated word found.\n") < 0
                              ? EXIT_FAILURE
                              : EXIT_SUCCESS;
            break;

        case FIND_OUT_OF_MEMORY:
            (void)fprintf(stderr, "Unable to allocate memory.\n");
            exit_status = EXIT_FAILURE;
            break;

        case FIND_INVALID_ARGUMENT:
        default:
            (void)fprintf(stderr, "Invalid argument.\n");
            exit_status = EXIT_FAILURE;
            break;
    }

    free(repeated_word);
    free(input);

    return exit_status;
}