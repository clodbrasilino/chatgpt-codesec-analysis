#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t start;
    size_t length;
    size_t word_position;
} AdverbPosition;

typedef struct {
    const char *text;
    size_t length;
} WordEntry;

typedef enum {
    STATUS_OK,
    STATUS_INVALID_ARGUMENT,
    STATUS_OUT_OF_MEMORY,
    STATUS_INPUT_ERROR
} Status;

#define WORD_ENTRY(text) { (text), sizeof(text) - 1U }

static bool word_equals_ignore_case(const char *word, size_t word_length,
                                    const char *candidate,
                                    size_t candidate_length)
{
    if (word == NULL || candidate == NULL ||
        word_length != candidate_length) {
        return false;
    }

    for (size_t i = 0; i < word_length; ++i) {
        if (tolower((unsigned char)word[i]) !=
            tolower((unsigned char)candidate[i])) {
            return false;
        }
    }

    return true;
}

static bool is_adverb(const char *word, size_t length)
{
    static const WordEntry irregular_adverbs[] = {
        WORD_ENTRY("again"),
        WORD_ENTRY("almost"),
        WORD_ENTRY("always"),
        WORD_ENTRY("away"),
        WORD_ENTRY("back"),
        WORD_ENTRY("enough"),
        WORD_ENTRY("ever"),
        WORD_ENTRY("far"),
        WORD_ENTRY("fast"),
        WORD_ENTRY("hard"),
        WORD_ENTRY("here"),
        WORD_ENTRY("just"),
        WORD_ENTRY("late"),
        WORD_ENTRY("never"),
        WORD_ENTRY("now"),
        WORD_ENTRY("often"),
        WORD_ENTRY("perhaps"),
        WORD_ENTRY("quite"),
        WORD_ENTRY("rather"),
        WORD_ENTRY("sometimes"),
        WORD_ENTRY("soon"),
        WORD_ENTRY("still"),
        WORD_ENTRY("then"),
        WORD_ENTRY("there"),
        WORD_ENTRY("together"),
        WORD_ENTRY("too"),
        WORD_ENTRY("very"),
        WORD_ENTRY("well"),
        WORD_ENTRY("yet")
    };

    if (word == NULL) {
        return false;
    }

    if (length >= 2U &&
        tolower((unsigned char)word[length - 2U]) == 'l' &&
        tolower((unsigned char)word[length - 1U]) == 'y') {
        return true;
    }

    for (size_t i = 0;
         i < sizeof irregular_adverbs / sizeof irregular_adverbs[0];
         ++i) {
        if (word_equals_ignore_case(word, length,
                                    irregular_adverbs[i].text,
                                    irregular_adverbs[i].length)) {
            return true;
        }
    }

    return false;
}

Status find_adverbs(const char *sentence, AdverbPosition **positions,
                    size_t *count)
{
    AdverbPosition *results = NULL;
    size_t result_count = 0;
    size_t capacity = 0;
    size_t index = 0;
    size_t word_position = 0;

    if (sentence == NULL || positions == NULL || count == NULL) {
        return STATUS_INVALID_ARGUMENT;
    }

    *positions = NULL;
    *count = 0;

    while (sentence[index] != '\0') {
        size_t start;
        size_t length;

        while (sentence[index] != '\0' &&
               !isalpha((unsigned char)sentence[index])) {
            ++index;
        }

        if (sentence[index] == '\0') {
            break;
        }

        start = index;
        ++word_position;

        while (sentence[index] != '\0' &&
               isalpha((unsigned char)sentence[index])) {
            ++index;
        }

        length = index - start;

        if (!is_adverb(sentence + start, length)) {
            continue;
        }

        if (result_count == capacity) {
            size_t new_capacity;
            AdverbPosition *new_results;

            if (capacity == 0U) {
                new_capacity = 8U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(results);
                    return STATUS_OUT_OF_MEMORY;
                }

                new_capacity = capacity * 2U;
            }

            if (new_capacity > SIZE_MAX / sizeof *new_results) {
                free(results);
                return STATUS_OUT_OF_MEMORY;
            }

            new_results = realloc(
                results, new_capacity * sizeof *new_results);

            if (new_results == NULL) {
                free(results);
                return STATUS_OUT_OF_MEMORY;
            }

            results = new_results;
            capacity = new_capacity;
        }

        results[result_count].start = start;
        results[result_count].length = length;
        results[result_count].word_position = word_position;
        ++result_count;
    }

    *positions = results;
    *count = result_count;

    return STATUS_OK;
}

static Status read_sentence(FILE *stream, char **sentence)
{
    char *buffer;
    size_t length = 0;
    size_t capacity = 256U;
    int character;

    if (stream == NULL || sentence == NULL) {
        return STATUS_INVALID_ARGUMENT;
    }

    *sentence = NULL;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return STATUS_OUT_OF_MEMORY;
    }

    while ((character = fgetc(stream)) != EOF) {
        if (character == '\0') {
            free(buffer);
            return STATUS_INPUT_ERROR;
        }

        if (length >= capacity - 1U) {
            char *new_buffer;
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return STATUS_OUT_OF_MEMORY;
            }

            new_capacity = capacity * 2U;
            new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return STATUS_OUT_OF_MEMORY;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length] = (char)character;
        ++length;
    }

    if (ferror(stream)) {
        free(buffer);
        return STATUS_INPUT_ERROR;
    }

    buffer[length] = '\0';
    *sentence = buffer;

    return STATUS_OK;
}

int main(void)
{
    char *sentence = NULL;
    AdverbPosition *positions = NULL;
    size_t count = 0;
    int result = EXIT_SUCCESS;
    Status status;

    status = read_sentence(stdin, &sentence);
    if (status != STATUS_OK) {
        fputs("Failed to read the sentence.\n", stderr);
        return EXIT_FAILURE;
    }

    status = find_adverbs(sentence, &positions, &count);
    if (status != STATUS_OK) {
        fputs("Failed to find adverbs.\n", stderr);
        free(sentence);
        return EXIT_FAILURE;
    }

    if (count == 0U) {
        if (fputs("No adverbs found.\n", stdout) == EOF) {
            result = EXIT_FAILURE;
        }
    } else {
        for (size_t i = 0; i < count; ++i) {
            if (fwrite(sentence + positions[i].start, 1U,
                       positions[i].length, stdout) != positions[i].length ||
                printf(": word %zu, character %zu\n",
                       positions[i].word_position,
                       positions[i].start + 1U) < 0) {
                result = EXIT_FAILURE;
                break;
            }
        }
    }

    if (fflush(stdout) == EOF) {
        result = EXIT_FAILURE;
    }

    free(positions);
    free(sentence);

    return result;
}