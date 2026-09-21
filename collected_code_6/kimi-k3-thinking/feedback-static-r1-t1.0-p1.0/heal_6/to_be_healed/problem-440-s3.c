#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_ADVERBS 128
#define INITIAL_LINE_CAPACITY 128

typedef struct {
    char *word;
    size_t word_position;
    size_t char_offset;
} Adverb;

static int ends_with_ly(const char *word, size_t len)
{
    if (word == NULL || len < 3) {
        return 0;
    }
    return tolower((unsigned char)word[len - 2]) == 'l' &&
           tolower((unsigned char)word[len - 1]) == 'y';
}

static size_t find_adverbs(const char *sentence, Adverb *results, size_t capacity)
{
    size_t count = 0;
    size_t word_pos = 0;
    size_t i = 0;

    if (sentence == NULL || results == NULL || capacity == 0) {
        return 0;
    }

    while (sentence[i] != '\0') {
        if (isalpha((unsigned char)sentence[i])) {
            size_t start = i;
            size_t wlen;

            while (isalpha((unsigned char)sentence[i]) || sentence[i] == '\'') {
                i++;
            }
            wlen = i - start;
            word_pos++;

            if (ends_with_ly(sentence + start, wlen) && count < capacity) {
                char *word;

                if (wlen >= SIZE_MAX - 1) {
                    break;
                }
                word = malloc(wlen + 1);
                if (word == NULL) {
                    break;
                }

                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(word, sentence + start, wlen);
                word[wlen] = '\0';

                results[count].word = word;
                results[count].word_position = word_pos;
                results[count].char_offset = start;
                count++;
            }
        } else {
            i++;
        }
    }

    return count;
}

static char *read_line(FILE *stream)
{
    size_t capacity = INITIAL_LINE_CAPACITY;
    size_t length = 0;
    char *buffer;
    int c;

    if (stream == NULL || INITIAL_LINE_CAPACITY < 2) {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = fgetc(stream)) != EOF && c != '\n') {
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *tmp;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }
            new_capacity = capacity * 2;
            if (new_capacity <= capacity) {
                free(buffer);
                return NULL;
            }
            tmp = realloc(buffer, new_capacity);
            if (tmp == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = tmp;
            capacity = new_capacity;
        }
        if (length + 1 >= capacity) {
            free(buffer);
            return NULL;
        }
        buffer[length] = (char)c;
        length++;
    }

    if (ferror(stream) || (c == EOF && length == 0)) {
        free(buffer);
        return NULL;
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        length--;
    }

    if (length >= capacity) {
        free(buffer);
        return NULL;
    }
    buffer[length] = '\0';

    return buffer;
}

int main(void)
{
    char *sentence;
    Adverb results[MAX_ADVERBS];
    size_t count;
    size_t k;

    printf("Enter a sentence: ");
    fflush(stdout);

    sentence = read_line(stdin);
    if (sentence == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return EXIT_FAILURE;
    }

    if (sentence[0] == '\0') {
        fprintf(stderr, "Error: empty sentence.\n");
        free(sentence);
        return EXIT_FAILURE;
    }

    count = find_adverbs(sentence, results, MAX_ADVERBS);

    if (count == 0) {
        printf("No adverbs found.\n");
    } else {
        printf("Found %zu adverb(s):\n", count);
        for (k = 0; k < count; k++) {
            printf("  Word #%zu at character %zu: %s\n",
                   results[k].word_position,
                   results[k].char_offset,
                   results[k].word);
        }
    }

    for (k = 0; k < count; k++) {
        free(results[k].word);
    }
    free(sentence);

    return EXIT_SUCCESS;
}