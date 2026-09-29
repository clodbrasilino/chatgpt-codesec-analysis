#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct word_entry {
    const char *text;
    size_t length;
};

#define WORD_ENTRY(value) { (value), sizeof(value) - 1 }
#define ARRAY_LENGTH(array) (sizeof(array) / sizeof((array)[0]))

static bool token_equals(const char *token, size_t token_length,
                         const struct word_entry *word)
{
    size_t i;

    if (token == NULL || word == NULL || word->text == NULL ||
        token_length != word->length) {
        return false;
    }

    for (i = 0; i < token_length; ++i) {
        if (tolower((unsigned char)token[i]) !=
            tolower((unsigned char)word->text[i])) {
            return false;
        }
    }

    return true;
}

static bool is_adverb(const char *word, size_t length)
{
    static const struct word_entry irregular_adverbs[] = {
        WORD_ENTRY("again"),
        WORD_ENTRY("almost"),
        WORD_ENTRY("already"),
        WORD_ENTRY("also"),
        WORD_ENTRY("always"),
        WORD_ENTRY("anywhere"),
        WORD_ENTRY("away"),
        WORD_ENTRY("back"),
        WORD_ENTRY("downstairs"),
        WORD_ENTRY("early"),
        WORD_ENTRY("enough"),
        WORD_ENTRY("ever"),
        WORD_ENTRY("everywhere"),
        WORD_ENTRY("far"),
        WORD_ENTRY("fast"),
        WORD_ENTRY("hard"),
        WORD_ENTRY("here"),
        WORD_ENTRY("how"),
        WORD_ENTRY("however"),
        WORD_ENTRY("just"),
        WORD_ENTRY("late"),
        WORD_ENTRY("less"),
        WORD_ENTRY("more"),
        WORD_ENTRY("most"),
        WORD_ENTRY("much"),
        WORD_ENTRY("near"),
        WORD_ENTRY("never"),
        WORD_ENTRY("not"),
        WORD_ENTRY("now"),
        WORD_ENTRY("often"),
        WORD_ENTRY("once"),
        WORD_ENTRY("only"),
        WORD_ENTRY("outside"),
        WORD_ENTRY("quite"),
        WORD_ENTRY("rather"),
        WORD_ENTRY("seldom"),
        WORD_ENTRY("sometimes"),
        WORD_ENTRY("soon"),
        WORD_ENTRY("still"),
        WORD_ENTRY("then"),
        WORD_ENTRY("there"),
        WORD_ENTRY("today"),
        WORD_ENTRY("together"),
        WORD_ENTRY("tomorrow"),
        WORD_ENTRY("too"),
        WORD_ENTRY("upstairs"),
        WORD_ENTRY("very"),
        WORD_ENTRY("well"),
        WORD_ENTRY("when"),
        WORD_ENTRY("where"),
        WORD_ENTRY("why"),
        WORD_ENTRY("yesterday"),
        WORD_ENTRY("yet")
    };
    size_t i;

    if (word == NULL) {
        return false;
    }

    if (length > 2 &&
        tolower((unsigned char)word[length - 2]) == 'l' &&
        tolower((unsigned char)word[length - 1]) == 'y') {
        return true;
    }

    for (i = 0; i < ARRAY_LENGTH(irregular_adverbs); ++i) {
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

    for (;;) {
        unsigned char ch;
        size_t items_read = fread(&ch, sizeof(ch), 1, stream);

        if (items_read == 0) {
            if (ferror(stream)) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (ch == (unsigned char)'\n') {
            break;
        }

        if (ch == (unsigned char)'\0') {
            free(buffer);
            return NULL;
        }

        if (length == capacity - 1) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';
    return buffer;
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