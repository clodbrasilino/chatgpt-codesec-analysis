#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_WORD_LEN 128
#define FLUSH_GUARD_LIMIT 1048576U

bool is_word_length_even(const char *word, size_t max_len)
{
    size_t len;

    if (word == NULL || max_len == 0U) {
        return false;
    }

    len = strnlen(word, max_len);
    return (len % 2U) == 0U;
}

static bool flush_stdin(void)
{
    int c;
    size_t guard = 0U;

    do {
        c = getchar();
        guard++;
    } while (c != '\n' && c != EOF && guard < FLUSH_GUARD_LIMIT);

    return (c == '\n' || c == EOF);
}

static bool read_word(char *buffer, size_t buffer_size, size_t *out_len)
{
    size_t len;

    if (buffer == NULL || out_len == NULL || buffer_size < 2U) {
        return false;
    }

    if (fgets(buffer, (int)buffer_size, stdin) == NULL) {
        return false;
    }

    buffer[buffer_size - 1U] = '\0';
    len = strnlen(buffer, buffer_size);

    if (len > 0U && buffer[len - 1U] == '\n') {
        buffer[len - 1U] = '\0';
        len--;
    } else if (len == buffer_size - 1U) {
        if (!flush_stdin()) {
            return false;
        }
        return false;
    }

    *out_len = len;
    return true;
}

int main(void)
{
    char buffer[MAX_WORD_LEN] = { 0 };
    size_t len = 0U;

    printf("Enter a word: ");

    if (!read_word(buffer, sizeof(buffer), &len)) {
        fprintf(stderr, "Error: failed to read input or input too long (maximum %u characters).\n",
                (unsigned int)(MAX_WORD_LEN - 1U));
        return EXIT_FAILURE;
    }

    if (len == 0U) {
        fprintf(stderr, "Error: no word entered.\n");
        return EXIT_FAILURE;
    }

    if (is_word_length_even(buffer, sizeof(buffer))) {
        printf("The word \"%s\" has an even length (%zu).\n", buffer, len);
    } else {
        printf("The word \"%s\" has an odd length (%zu).\n", buffer, len);
    }

    return EXIT_SUCCESS;
}