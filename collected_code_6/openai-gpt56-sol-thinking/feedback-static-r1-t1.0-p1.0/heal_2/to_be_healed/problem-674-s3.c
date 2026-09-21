#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    const char *word;
    size_t length;
    size_t hash;
    int used;
} WordEntry;

typedef struct {
    WordEntry *entries;
    size_t capacity;
    size_t count;
} WordSet;

static int is_word_separator(unsigned char c)
{
    return c == ' ' || c == '\t' || c == '\r' ||
           c == '\n' || c == '\v' || c == '\f';
}

static size_t hash_word(const char *word, size_t length)
{
    size_t hash = (size_t)5381;
    size_t i;

    for (i = 0; i < length; ++i) {
        hash = ((hash << 5) + hash) ^ (unsigned char)word[i];
    }

    return hash;
}

static int word_set_init(WordSet *set)
{
    set->capacity = 16;
    set->count = 0;
    set->entries = calloc(set->capacity, sizeof(*set->entries));

    return set->entries != NULL;
}

static void word_set_destroy(WordSet *set)
{
    free(set->entries);
    set->entries = NULL;
    set->capacity = 0;
    set->count = 0;
}

static int word_set_resize(WordSet *set, size_t new_capacity)
{
    WordEntry *new_entries;
    size_t i;

    if (new_capacity > SIZE_MAX / sizeof(*new_entries)) {
        return 0;
    }

    new_entries = calloc(new_capacity, sizeof(*new_entries));
    if (new_entries == NULL) {
        return 0;
    }

    for (i = 0; i < set->capacity; ++i) {
        size_t index;

        if (!set->entries[i].used) {
            continue;
        }

        index = set->entries[i].hash & (new_capacity - 1);

        while (new_entries[index].used) {
            index = (index + 1) & (new_capacity - 1);
        }

        new_entries[index] = set->entries[i];
    }

    free(set->entries);
    set->entries = new_entries;
    set->capacity = new_capacity;

    return 1;
}

static int word_set_add(WordSet *set, const char *word, size_t length)
{
    size_t hash;
    size_t index;

    hash = hash_word(word, length);
    index = hash & (set->capacity - 1);

    while (set->entries[index].used) {
        if (set->entries[index].hash == hash &&
            set->entries[index].length == length &&
            memcmp(set->entries[index].word, word, length) == 0) {
            return 0;
        }

        index = (index + 1) & (set->capacity - 1);
    }

    if (set->count >= set->capacity - set->capacity / 4) {
        size_t new_capacity;

        if (set->capacity > SIZE_MAX / 2) {
            return -1;
        }

        new_capacity = set->capacity * 2;

        if (!word_set_resize(set, new_capacity)) {
            return -1;
        }

        index = hash & (set->capacity - 1);

        while (set->entries[index].used) {
            index = (index + 1) & (set->capacity - 1);
        }
    }

    set->entries[index].word = word;
    set->entries[index].length = length;
    set->entries[index].hash = hash;
    set->entries[index].used = 1;
    ++set->count;

    return 1;
}

char *remove_duplicate_words(const char *input)
{
    WordSet seen;
    char *output;
    size_t input_length;
    size_t input_position;
    size_t output_length;

    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_length = strlen(input);

    if (input_length == SIZE_MAX) {
        return NULL;
    }

    output = malloc(input_length + 1);
    if (output == NULL) {
        return NULL;
    }

    if (!word_set_init(&seen)) {
        free(output);
        return NULL;
    }

    input_position = 0;
    output_length = 0;

    while (input_position < input_length) {
        size_t word_start;
        size_t word_length;
        size_t required;
        int added;

        while (input_position < input_length &&
               is_word_separator((unsigned char)input[input_position])) {
            ++input_position;
        }

        if (input_position == input_length) {
            break;
        }

        word_start = input_position;

        while (input_position < input_length &&
               !is_word_separator((unsigned char)input[input_position])) {
            ++input_position;
        }

        word_length = input_position - word_start;
        added = word_set_add(&seen, input + word_start, word_length);

        if (added < 0) {
            word_set_destroy(&seen);
            free(output);
            return NULL;
        }

        if (added == 0) {
            continue;
        }

        required = word_length + (output_length != 0 ? 1 : 0);

        if (required > input_length - output_length) {
            word_set_destroy(&seen);
            free(output);
            return NULL;
        }

        if (output_length != 0) {
            output[output_length++] = ' ';
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(output + output_length, input + word_start, word_length);
        output_length += word_length;
    }

    output[output_length] = '\0';
    word_set_destroy(&seen);

    return output;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *input;
    char *result;
    size_t input_length;
    size_t position;
    int i;
    int status;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    input_length = 0;

    for (i = 1; i < argc; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t argument_length = strlen(argv[i]);

        if (argument_length > SIZE_MAX - input_length) {
            fprintf(stderr, "Input is too large\n");
            return EXIT_FAILURE;
        }

        input_length += argument_length;

        if (i + 1 < argc) {
            if (input_length == SIZE_MAX) {
                fprintf(stderr, "Input is too large\n");
                return EXIT_FAILURE;
            }

            ++input_length;
        }
    }

    if (input_length == SIZE_MAX) {
        fprintf(stderr, "Input is too large\n");
        return EXIT_FAILURE;
    }

    input = malloc(input_length + 1);
    if (input == NULL) {
        fprintf(stderr, "Failed to allocate input buffer\n");
        return EXIT_FAILURE;
    }

    position = 0;

    for (i = 1; i < argc; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t argument_length = strlen(argv[i]);

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(input + position, argv[i], argument_length);
        position += argument_length;

        if (i + 1 < argc) {
            input[position++] = ' ';
        }
    }

    input[position] = '\0';

    result = remove_duplicate_words(input);
    free(input);

    if (result == NULL) {
        fprintf(stderr, "Failed to process the input string\n");
        return EXIT_FAILURE;
    }

    status = EXIT_SUCCESS;

    if (fputs(result, stdout) == EOF ||
        fputc('\n', stdout) == EOF ||
        fflush(stdout) == EOF) {
        status = EXIT_FAILURE;
    }

    free(result);
    return status;
}