#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
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

char *read_input_line(void)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer = malloc(capacity);
    int c;

    if (buffer == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != EOF && c != '\n') {
        if (length + 1 >= capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }
            capacity *= 2;
            char *tmp = realloc(buffer, capacity);
            if (tmp == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = tmp;
        }
        buffer[length++] = (char)c;
    }

    if (c == EOF && length == 0) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input = read_input_line();
    const char *word;
    size_t word_len = 0;

    if (input == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    word = find_first_max_even_word(input, &word_len);

    if (word != NULL) {
        printf("First maximum even word: ");
        fwrite(word, 1, word_len, stdout);
        printf(" (length %zu)\n", word_len);
    } else {
        printf("No even word found.\n");
    }

    free(input);
    return 0;
}