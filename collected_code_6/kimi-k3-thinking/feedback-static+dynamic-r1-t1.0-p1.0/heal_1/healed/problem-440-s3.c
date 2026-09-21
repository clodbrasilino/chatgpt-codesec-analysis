#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ADVERBS 128

typedef struct {
    char *word;
    size_t word_position;
    size_t char_offset;
} Adverb;

static int ends_with_ly(const char *word, size_t len)
{
    if (len < 3) {
        return 0;
    }
    return tolower((unsigned char)word[len - 2]) == 'l' &&
           tolower((unsigned char)word[len - 1]) == 'y';
}

static char *copy_word(const char *src, size_t len)
{
    char *dst = malloc(len + 1);

    if (dst == NULL) {
        return NULL;
    }
    if (len > 0) {
        memcpy(dst, src, len);
    }
    dst[len] = '\0';
    return dst;
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
                char *word = copy_word(sentence + start, wlen);
                if (word == NULL) {
                    break;
                }
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
    size_t capacity = 128;
    size_t len = 0;
    char *buffer = malloc(capacity);
    int c;

    if (buffer == NULL) {
        return NULL;
    }

    while ((c = fgetc(stream)) != EOF && c != '\n') {
        if (len + 1 >= capacity) {
            size_t new_capacity = capacity * 2;
            char *resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = resized;
            capacity = new_capacity;
        }
        buffer[len++] = (char)c;
    }

    if (c == EOF && len == 0) {
        free(buffer);
        return NULL;
    }

    buffer[len] = '\0';
    return buffer;
}

static void free_adverbs(Adverb *results, size_t count)
{
    for (size_t i = 0; i < count; i++) {
        free(results[i].word);
    }
}

int main(void)
{
    Adverb results[MAX_ADVERBS];
    char *sentence;
    size_t count;

    printf("Enter a sentence: ");
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
        for (size_t k = 0; k < count; k++) {
            printf("  Word #%zu at character %zu: %s\n",
                   results[k].word_position,
                   results[k].char_offset,
                   results[k].word);
        }
    }

    free_adverbs(results, count);
    free(sentence);

    return EXIT_SUCCESS;
}