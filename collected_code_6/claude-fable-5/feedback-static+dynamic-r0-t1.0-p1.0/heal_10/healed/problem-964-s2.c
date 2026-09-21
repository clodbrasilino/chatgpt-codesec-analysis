#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_WORD_LEN 256U

bool is_word_length_even(const char *word, size_t max_len)
{
    size_t len;

    if (word == NULL || max_len == 0U) {
        return false;
    }

    len = strnlen(word, max_len);
    if (len >= max_len) {
        return false;
    }

    return (len % 2U) == 0U;
}

static void flush_stdin(void)
{
    int ch;
    size_t guard = 0U;
    const size_t guard_limit = (size_t)1U << 20;

    do {
        ch = fgetc(stdin);
        guard++;
    } while (ch != '\n' && ch != EOF && guard < guard_limit);
}

int main(void)
{
    char buffer[MAX_WORD_LEN] = {0};
    char *newline = NULL;

    printf("Enter a word: ");
    if (fflush(stdout) != 0) {
        return EXIT_FAILURE;
    }

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1U] = '\0';

    newline = memchr(buffer, '\n', sizeof(buffer));
    if (newline != NULL) {
        *newline = '\0';
    } else if (strnlen(buffer, sizeof(buffer)) == sizeof(buffer) - 1U) {
        flush_stdin();
    }

    if (buffer[0] == '\0') {
        fprintf(stderr, "No word entered.\n");
        return EXIT_FAILURE;
    }

    if (is_word_length_even(buffer, sizeof(buffer))) {
        printf("The word \"%s\" has an even length.\n", buffer);
    } else {
        printf("The word \"%s\" has an odd length.\n", buffer);
    }

    return EXIT_SUCCESS;
}