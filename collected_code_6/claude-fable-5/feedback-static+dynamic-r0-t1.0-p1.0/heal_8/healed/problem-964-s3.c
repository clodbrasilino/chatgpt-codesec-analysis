#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define BUFFER_SIZE 256U

static bool is_word_length_even(const char *word, size_t max_len)
{
    size_t len;

    if (word == NULL) {
        return false;
    }

    len = strnlen(word, max_len);
    return (len % 2U) == 0U;
}

static bool discard_remaining_input(FILE *stream)
{
    int ch;
    bool truncated = false;

    if (stream == NULL) {
        return false;
    }

    do {
        ch = fgetc(stream);
        if (ch != '\n' && ch != EOF) {
            truncated = true;
        }
    } while (ch != '\n' && ch != EOF);

    return truncated;
}

int main(void)
{
    char buffer[BUFFER_SIZE] = {0};
    size_t len;

    printf("Enter a word: ");
    fflush(stdout);

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1U] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if (len > 0U && buffer[len - 1U] == '\n') {
        buffer[len - 1U] = '\0';
        len--;
    }

    if (len == 0U) {
        fprintf(stderr, "No word entered\n");
        return EXIT_FAILURE;
    }

    if (len == (sizeof(buffer) - 1U)) {
        if (discard_remaining_input(stdin)) {
            fprintf(stderr, "Input too long: maximum %zu characters allowed\n",
                    sizeof(buffer) - 1U);
            return EXIT_FAILURE;
        }
    }

    if (is_word_length_even(buffer, sizeof(buffer))) {
        printf("The word \"%s\" has an even length (%zu)\n", buffer, len);
    } else {
        printf("The word \"%s\" has an odd length (%zu)\n", buffer, len);
    }

    return EXIT_SUCCESS;
}