#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

static int extract_quoted_values(const char *input)
{
    const char *cursor;
    int count = 0;

    if (input == NULL) {
        return -1;
    }

    cursor = input;

    while (*cursor != '\0') {
        const char *opening = strchr(cursor, '"');
        const char *closing;
        size_t length;

        if (opening == NULL) {
            break;
        }

        cursor = opening + 1;
        closing = strchr(cursor, '"');

        if (closing == NULL) {
            break;
        }

        length = (size_t)(closing - cursor);

        if (length > 0 && fwrite(cursor, 1, length, stdout) != length) {
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

int main(int argc, const char *const argv[])
{
    const char *program = "program";
    int count;

    if (argc > 0 && argv != NULL && argv[0] != NULL) {
        program = argv[0];
    }

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <string>\n", program);
        return EXIT_FAILURE;
    }

    count = extract_quoted_values(argv[1]);

    if (count < 0) {
        fprintf(stderr, "Failed to extract quoted values\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}