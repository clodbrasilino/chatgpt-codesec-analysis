#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

static int extract_quoted_values(const char *input, size_t input_length)
{
    const char *cursor;
    const char *end;
    int count = 0;

    if (input == NULL) {
        return -1;
    }

    cursor = input;
    end = input + input_length;

    while (cursor < end) {
        const char *opening = memchr(cursor, '"', (size_t)(end - cursor));
        const char *closing;
        size_t length;

        if (opening == NULL) {
            break;
        }

        cursor = opening + 1;
        closing = memchr(cursor, '"', (size_t)(end - cursor));

        if (closing == NULL) {
            break;
        }

        length = (size_t)(closing - cursor);

        if (length != 0 && fwrite(cursor, 1, length, stdout) != length) {
            return -1;
        }

        if (fputc('\n', stdout) == EOF) {
            return -1;
        }

        if (count == INT_MAX) {
            return -1;
        }

        ++count;
        cursor = closing + 1;
    }

    return count;
}

int main(int argc, char *argv[])
{
    int count;
    size_t input_length;

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        const char *program =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

        fprintf(stderr, "Usage: %s <string>\n", program);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_length = strlen(argv[1]);
    count = extract_quoted_values(argv[1], input_length);

    if (count < 0) {
        fprintf(stderr, "Failed to extract quoted values\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}