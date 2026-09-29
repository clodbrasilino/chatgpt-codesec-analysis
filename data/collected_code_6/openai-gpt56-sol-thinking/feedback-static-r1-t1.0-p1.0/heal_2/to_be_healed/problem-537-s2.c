#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *start;
    size_t length;
} Word;

enum FindResult {
    FIND_ERROR = -1,
    FIND_NOT_FOUND = 0,
    FIND_FOUND = 1
};

static int is_word_character(unsigned char character)
{
    return isalnum(character) != 0 || character == '_';
}

static int words_equal(const Word *word, const char *start, size_t length)
{
    size_t index;

    if (word->length != length) {
        return 0;
    }

    for (index = 0; index < length; ++index) {
        if (word->start[index] != start[index]) {
            return 0;
        }
    }

    return 1;
}

static char *copy_word(const char *start, size_t length)
{
    char *copy;
    size_t index;

    if (length == SIZE_MAX) {
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

int find_first_repeated_word(const char *text, char **result)
{
    const char *cursor;
    Word *words = NULL;
    size_t word_count = 0;
    size_t capacity = 0;

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
        size_t index;

        while (*cursor != '\0' &&
               !is_word_character((unsigned char)*cursor)) {
            ++cursor;
        }

        if (*cursor == '\0') {
            break;
        }

        start = cursor;

        while (*cursor != '\0' &&
               is_word_character((unsigned char)*cursor)) {
            ++cursor;
        }

        length = (size_t)(cursor - start);

        for (index = 0; index < word_count; ++index) {
            if (words_equal(&words[index], start, length)) {
                char *repeated = copy_word(start, length);

                if (repeated == NULL) {
                    free(words);
                    return FIND_ERROR;
                }

                *result = repeated;
                free(words);
                return FIND_FOUND;
            }
        }

        if (word_count == capacity) {
            size_t new_capacity;
            Word *new_words;

            if (capacity == 0) {
                new_capacity = 8;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(words);
                    return FIND_ERROR;
                }

                new_capacity = capacity * 2;
            }

            if (new_capacity > SIZE_MAX / sizeof(*words)) {
                free(words);
                return FIND_ERROR;
            }

            new_words = realloc(words, new_capacity * sizeof(*words));
            if (new_words == NULL) {
                free(words);
                return FIND_ERROR;
            }

            words = new_words;
            capacity = new_capacity;
        }

        words[word_count].start = start;
        words[word_count].length = length;
        ++word_count;
    }

    free(words);
    return FIND_NOT_FOUND;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char *argv[const])
{
    const char *program_name;
    char *repeated_word = NULL;
    int result;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2) {
        if (fprintf(stderr, "Usage: %s \"text\"\n", program_name) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    result = find_first_repeated_word(argv[1], &repeated_word);

    if (result == FIND_ERROR) {
        if (fputs("Unable to process the input.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (result == FIND_FOUND) {
        int print_result = printf("%s\n", repeated_word);

        free(repeated_word);

        if (print_result < 0) {
            return EXIT_FAILURE;
        }
    } else if (puts("No repeated word found.") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}