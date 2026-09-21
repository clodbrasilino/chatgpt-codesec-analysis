#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char chunk[1024];
    size_t total_len = 0;
    size_t alloc_size = 1024;
    char *buffer = malloc(alloc_size);

    if (buffer == NULL) {
        return NULL;
    }
    buffer[0] = '\0';

    while (fgets(chunk, (int)sizeof(chunk), stdin) != NULL) {
        size_t chunk_len = strlen(chunk);
        int has_newline = 0;

        if (chunk_len > 0 && chunk[chunk_len - 1] == '\n') {
            chunk[--chunk_len] = '\0';
            has_newline = 1;
        }

        if (total_len > SIZE_MAX - chunk_len - 1) {
            free(buffer);
            return NULL;
        }

        size_t needed = total_len + chunk_len + 1;
        if (needed > alloc_size) {
            size_t new_size = alloc_size;
            while (new_size < needed) {
                if (new_size > SIZE_MAX / 2) {
                    free(buffer);
                    return NULL;
                }
                new_size *= 2;
            }

            char *tmp = realloc(buffer, new_size);
            if (tmp == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = tmp;
            alloc_size = new_size;
        }

        memcpy(buffer + total_len, chunk, chunk_len);
        total_len += chunk_len;

        if (has_newline) {
            break;
        }
    }

    if (total_len == 0 && !feof(stdin)) {
        free(buffer);
        return NULL;
    }

    buffer[total_len] = '\0';
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