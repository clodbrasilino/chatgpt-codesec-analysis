#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool token_equals(const char *token, size_t length, const char *word)
{
    size_t i;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(word) != length) {
        return false;
    }

    for (i = 0; i < length; ++i) {
        if (tolower((unsigned char)token[i]) !=
            tolower((unsigned char)word[i])) {
            return false;
        }
    }

    return true;
}

static bool is_adverb(const char *word, size_t length)
{
    static const char *const irregular_adverbs[] = {
        "again", "almost", "already", "also", "always", "anywhere",
        "away", "back", "downstairs", "early", "enough", "ever",
        "everywhere", "far", "fast", "hard", "here", "how", "however",
        "just", "late", "less", "more", "most", "much", "near", "never",
        "not", "now", "often", "once", "only", "outside", "quite",
        "rather", "seldom", "sometimes", "soon", "still", "then",
        "there", "today", "together", "tomorrow", "too", "upstairs",
        "very", "well", "when", "where", "why", "yesterday", "yet"
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
        if (token_equals(word, length, irregular_adverbs[i])) {
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
                printf(", word position: %zu, character position: %zu\n",
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
    char *buffer = malloc(capacity);
    int ch;

    if (buffer == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        char *resized;

        if (ch == '\0') {
            free(buffer);
            return NULL;
        }

        if (length == capacity - 1) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }

            capacity *= 2;
            resized = realloc(buffer, capacity);
            if (resized == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = resized;
        }

        buffer[length++] = (char)ch;
    }

    if (ferror(stream)) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *sentence;
    size_t adverb_count;

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

    if (adverb_count == 0 && fputs("No adverbs found.\n", stdout) == EOF) {
        free(sentence);
        return EXIT_FAILURE;
    }

    free(sentence);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}