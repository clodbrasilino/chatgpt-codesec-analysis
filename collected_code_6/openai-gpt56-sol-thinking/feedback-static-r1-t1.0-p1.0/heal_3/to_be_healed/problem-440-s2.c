#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct adverb_entry {
    const char *word;
    size_t length;
};

#define ADVERB_ENTRY(value) { (value), sizeof(value) - 1 }

static bool token_equals(const char *token, size_t token_length,
                         const struct adverb_entry *entry)
{
    size_t i;

    if (token_length != entry->length) {
        return false;
    }

    for (i = 0; i < token_length; ++i) {
        if (tolower((unsigned char)token[i]) !=
            tolower((unsigned char)entry->word[i])) {
            return false;
        }
    }

    return true;
}

static bool is_adverb(const char *word, size_t length)
{
    static const struct adverb_entry irregular_adverbs[] = {
        ADVERB_ENTRY("again"),
        ADVERB_ENTRY("almost"),
        ADVERB_ENTRY("already"),
        ADVERB_ENTRY("also"),
        ADVERB_ENTRY("always"),
        ADVERB_ENTRY("anywhere"),
        ADVERB_ENTRY("away"),
        ADVERB_ENTRY("back"),
        ADVERB_ENTRY("downstairs"),
        ADVERB_ENTRY("early"),
        ADVERB_ENTRY("enough"),
        ADVERB_ENTRY("ever"),
        ADVERB_ENTRY("everywhere"),
        ADVERB_ENTRY("far"),
        ADVERB_ENTRY("fast"),
        ADVERB_ENTRY("hard"),
        ADVERB_ENTRY("here"),
        ADVERB_ENTRY("how"),
        ADVERB_ENTRY("however"),
        ADVERB_ENTRY("just"),
        ADVERB_ENTRY("late"),
        ADVERB_ENTRY("less"),
        ADVERB_ENTRY("more"),
        ADVERB_ENTRY("most"),
        ADVERB_ENTRY("much"),
        ADVERB_ENTRY("near"),
        ADVERB_ENTRY("never"),
        ADVERB_ENTRY("not"),
        ADVERB_ENTRY("now"),
        ADVERB_ENTRY("often"),
        ADVERB_ENTRY("once"),
        ADVERB_ENTRY("only"),
        ADVERB_ENTRY("outside"),
        ADVERB_ENTRY("quite"),
        ADVERB_ENTRY("rather"),
        ADVERB_ENTRY("seldom"),
        ADVERB_ENTRY("sometimes"),
        ADVERB_ENTRY("soon"),
        ADVERB_ENTRY("still"),
        ADVERB_ENTRY("then"),
        ADVERB_ENTRY("there"),
        ADVERB_ENTRY("today"),
        ADVERB_ENTRY("together"),
        ADVERB_ENTRY("tomorrow"),
        ADVERB_ENTRY("too"),
        ADVERB_ENTRY("upstairs"),
        ADVERB_ENTRY("very"),
        ADVERB_ENTRY("well"),
        ADVERB_ENTRY("when"),
        ADVERB_ENTRY("where"),
        ADVERB_ENTRY("why"),
        ADVERB_ENTRY("yesterday"),
        ADVERB_ENTRY("yet")
    };
    size_t i;

    if (length > 2 &&
        tolower((unsigned char)word[length - 2]) == 'l' &&
        tolower((unsigned char)word[length - 1]) == 'y') {
        return true;
    }

    for (i = 0;
         i < sizeof(irregular_adverbs) / sizeof(irregular_adverbs[0]);
         ++i) {
        if (token_equals(word, length, &irregular_adverbs[i])) {
            return true;
        }
    }

    return false;
}

int find_adverbs(const char *sentence, size_t *adverb_count)
{
    size_t index = 0;
    size_t word_position = 0;
    size_t count = 0;

    if (sentence == NULL || adverb_count == NULL) {
        return -1;
    }

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

        while (sentence[index] != '\0' &&
               isalpha((unsigned char)sentence[index])) {
            ++index;
        }

        length = index - start;
        ++word_position;

        if (is_adverb(sentence + start, length)) {
            if (fputs("Adverb: ", stdout) == EOF ||
                fwrite(sentence + start, 1, length, stdout) != length ||
                fprintf(stdout,
                        ", word position: %zu, character position: %zu\n",
                        word_position, start + 1) < 0) {
                return -1;
            }

            ++count;
        }
    }

    *adverb_count = count;
    return 0;
}

static bool append_character(char **buffer, size_t *length, size_t *capacity,
                             unsigned char character)
{
    size_t required;

    if (buffer == NULL || *buffer == NULL ||
        length == NULL || capacity == NULL ||
        *length > SIZE_MAX - 2) {
        return false;
    }

    required = *length + 2;

    if (required > *capacity) {
        size_t new_capacity = *capacity;
        char *resized;

        if (new_capacity == 0) {
            new_capacity = 1;
        }

        while (new_capacity < required) {
            if (new_capacity > SIZE_MAX / 2) {
                new_capacity = required;
                break;
            }

            new_capacity *= 2;
        }

        resized = realloc(*buffer, new_capacity);
        if (resized == NULL) {
            return false;
        }

        *buffer = resized;
        *capacity = new_capacity;
    }

    (*buffer)[*length] = (char)character;
    ++*length;
    (*buffer)[*length] = '\0';

    return true;
}

static char *read_sentence(FILE *stream)
{
    size_t capacity = 256;
    size_t length = 0;
    char *buffer;

    if (stream == NULL) {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    buffer[0] = '\0';

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int input = fgetc(stream);

        if (input == EOF) {
            if (ferror(stream)) {
                free(buffer);
                return NULL;
            }

            return buffer;
        }

        if (input == '\n') {
            return buffer;
        }

        if (input == '\0') {
            free(buffer);
            return NULL;
        }

        if (!append_character(&buffer, &length, &capacity,
                              (unsigned char)input)) {
            free(buffer);
            return NULL;
        }
    }
}

int main(void)
{
    char *sentence;
    size_t adverb_count = 0;

    sentence = read_sentence(stdin);
    if (sentence == NULL) {
        fputs("Failed to read the sentence.\n", stderr);
        return EXIT_FAILURE;
    }

    if (find_adverbs(sentence, &adverb_count) != 0) {
        free(sentence);
        fputs("Failed to process the sentence.\n", stderr);
        return EXIT_FAILURE;
    }

    if (adverb_count == 0 &&
        fputs("No adverbs found.\n", stdout) == EOF) {
        free(sentence);
        return EXIT_FAILURE;
    }

    free(sentence);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}