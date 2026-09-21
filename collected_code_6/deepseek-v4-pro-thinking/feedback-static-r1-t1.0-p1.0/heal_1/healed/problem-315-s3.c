#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

const char *find_first_max_even_word(const char *str, size_t *word_len)
{
    const char *best = NULL;
    size_t best_len = 0;
    const char *word_start = NULL;
    size_t current_len = 0;
    const char *p;

    if (word_len != NULL) {
        *word_len = 0;
    }

    if (str == NULL) {
        return NULL;
    }

    for (p = str; ; ++p) {
        if (*p != '\0' && !isspace((unsigned char)*p)) {
            if (word_start == NULL) {
                word_start = p;
                current_len = 1;
            } else {
                ++current_len;
            }
        } else {
            if (word_start != NULL) {
                if (current_len % 2 == 0 && current_len > best_len) {
                    best = word_start;
                    best_len = current_len;
                }
                word_start = NULL;
                current_len = 0;
            }
            if (*p == '\0') {
                break;
            }
        }
    }

    if (word_len != NULL) {
        *word_len = best_len;
    }

    return best;
}

int main(void)
{
    size_t capacity = 256;
    char *buffer = malloc(capacity);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        return 1;
    }

    size_t total = 0;
    int done = 0;
    while (!done) {
        size_t to_read = capacity - total;
        size_t bytes = fread(buffer + total, 1, to_read, stdin);
        total += bytes;
        if (ferror(stdin)) {
            free(buffer);
            fprintf(stderr, "Error reading input.\n");
            return 1;
        }
        if (bytes < to_read) {
            done = 1;
        } else {
            capacity *= 2;
            char *newbuf = realloc(buffer, capacity);
            if (newbuf == NULL) {
                free(buffer);
                fprintf(stderr, "Memory allocation error.\n");
                return 1;
            }
            buffer = newbuf;
        }
    }
    buffer[total] = '\0';

    const char *word;
    size_t word_len = 0;

    word = find_first_max_even_word(buffer, &word_len);

    if (word != NULL) {
        printf("First maximum even word: ");
        fwrite(word, 1, word_len, stdout);
        printf(" (length %zu)\n", word_len);
    } else {
        printf("No even word found.\n");
    }

    free(buffer);
    return 0;
}