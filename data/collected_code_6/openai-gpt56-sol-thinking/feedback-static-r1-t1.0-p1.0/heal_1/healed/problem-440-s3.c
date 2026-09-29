#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t character_position;
    size_t word_position;
    size_t length;
} AdverbOccurrence;

static int is_adverb(const char *word, size_t length)
{
    if (word == NULL || length < 3) {
        return 0;
    }

    return tolower((unsigned char)word[length - 2]) == 'l' &&
           tolower((unsigned char)word[length - 1]) == 'y';
}

static int find_adverbs(const char *sentence, size_t sentence_length,
                        AdverbOccurrence **occurrences,
                        size_t *occurrence_count)
{
    size_t candidate_count = 0;
    size_t word_position = 0;
    size_t position = 0;
    size_t result_index = 0;
    AdverbOccurrence *results;

    if (sentence == NULL || occurrences == NULL || occurrence_count == NULL) {
        return -1;
    }

    *occurrences = NULL;
    *occurrence_count = 0;

    while (position < sentence_length) {
        size_t start;
        size_t length;

        while (position < sentence_length &&
               !isalpha((unsigned char)sentence[position])) {
            ++position;
        }

        if (position == sentence_length) {
            break;
        }

        start = position;

        while (position < sentence_length &&
               isalpha((unsigned char)sentence[position])) {
            ++position;
        }

        length = position - start;

        if (is_adverb(sentence + start, length)) {
            ++candidate_count;
        }
    }

    if (candidate_count == 0) {
        return 0;
    }

    if (candidate_count > SIZE_MAX / sizeof(*results)) {
        return -1;
    }

    results = malloc(candidate_count * sizeof(*results));
    if (results == NULL) {
        return -1;
    }

    position = 0;

    while (position < sentence_length) {
        size_t start;
        size_t length;

        while (position < sentence_length &&
               !isalpha((unsigned char)sentence[position])) {
            ++position;
        }

        if (position == sentence_length) {
            break;
        }

        start = position;
        ++word_position;

        while (position < sentence_length &&
               isalpha((unsigned char)sentence[position])) {
            ++position;
        }

        length = position - start;

        if (is_adverb(sentence + start, length)) {
            if (result_index >= candidate_count) {
                free(results);
                return -1;
            }

            results[result_index].character_position = start + 1;
            results[result_index].word_position = word_position;
            results[result_index].length = length;
            ++result_index;
        }
    }

    *occurrences = results;
    *occurrence_count = result_index;
    return 0;
}

static int read_line(FILE *stream, char **line, size_t *line_length)
{
    size_t capacity = 256;
    size_t length = 0;
    char *buffer;
    int character;

    if (stream == NULL || line == NULL || line_length == NULL) {
        return -1;
    }

    *line = NULL;
    *line_length = 0;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    while ((character = fgetc(stream)) != '\n' && character != EOF) {
        if (length == capacity - 1) {
            char *expanded_buffer;
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            expanded_buffer = realloc(buffer, new_capacity);
            if (expanded_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = expanded_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)character;
    }

    if (character == EOF && ferror(stream)) {
        free(buffer);
        return -1;
    }

    if (character == EOF && length == 0) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *line = buffer;
    *line_length = length;
    return 1;
}

int main(void)
{
    char *sentence = NULL;
    size_t sentence_length = 0;
    AdverbOccurrence *occurrences = NULL;
    size_t occurrence_count = 0;
    size_t index;
    int read_status;
    int status = EXIT_SUCCESS;

    read_status = read_line(stdin, &sentence, &sentence_length);
    if (read_status < 0) {
        fprintf(stderr, "Failed to read the sentence.\n");
        return EXIT_FAILURE;
    }

    if (read_status == 0) {
        return EXIT_SUCCESS;
    }

    if (find_adverbs(sentence, sentence_length, &occurrences,
                     &occurrence_count) != 0) {
        fprintf(stderr, "Failed to find adverbs.\n");
        free(sentence);
        return EXIT_FAILURE;
    }

    for (index = 0; index < occurrence_count; ++index) {
        const AdverbOccurrence *occurrence = &occurrences[index];

        if (fwrite(sentence + occurrence->character_position - 1, 1,
                   occurrence->length, stdout) != occurrence->length ||
            printf(": word %zu, character %zu\n",
                   occurrence->word_position,
                   occurrence->character_position) < 0) {
            status = EXIT_FAILURE;
            break;
        }
    }

    free(occurrences);
    free(sentence);

    if (status == EXIT_SUCCESS && fflush(stdout) == EOF) {
        status = EXIT_FAILURE;
    }

    return status;
}