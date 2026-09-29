#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_WORD_LEN 256U

static bool is_word_length_even(const char *word, size_t max_len)
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

static bool discard_remaining_input(FILE *stream)
{
    int ch;
    size_t guard = 0U;

    if (stream == NULL) {
        return false;
    }

    while ((ch = getc(stream)) != '\n' && ch != EOF) {
        guard++;
        if (guard > 1000000U) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    char buffer[MAX_WORD_LEN];
    char *newline = NULL;

    memset(buffer, 0, sizeof(buffer));

    if (printf("Enter a word: ") < 0) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) != 0) {
        return EXIT_FAILURE;
    }

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        (void)fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1U] = '\0';

    newline = strchr(buffer, '\n');
    if (newline != NULL) {
        *newline = '\0';
    } else {
        if (!discard_remaining_input(stdin)) {
            (void)fprintf(stderr, "Error discarding excess input.\n");
            return EXIT_FAILURE;
        }
    }

    if (buffer[0] == '\0') {
        (void)fprintf(stderr, "No word entered.\n");
        return EXIT_FAILURE;
    }

    if (is_word_length_even(buffer, sizeof(buffer))) {
        (void)printf("The word \"%s\" has an even length.\n", buffer);
    } else {
        (void)printf("The word \"%s\" has an odd length.\n", buffer);
    }

    return EXIT_SUCCESS;
}