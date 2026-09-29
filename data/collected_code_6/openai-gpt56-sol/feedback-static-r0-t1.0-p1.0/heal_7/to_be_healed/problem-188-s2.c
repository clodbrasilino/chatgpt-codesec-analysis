#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum { MAX_INPUT_LENGTH = 4096 };

static bool is_perfect_square(uint64_t number)
{
    uint64_t low = 0;
    uint64_t high = number < UINT32_MAX ? number : UINT32_MAX;

    while (low <= high) {
        uint64_t middle = low + (high - low) / 2;

        if (middle != 0 && middle > number / middle) {
            high = middle - 1;
        } else {
            uint64_t square = middle * middle;

            if (square == number) {
                return true;
            }

            low = middle + 1;
        }
    }

    return false;
}

static bool discard_line(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n') {
        if (ch == EOF) {
            return !ferror(stdin);
        }
    }

    return true;
}

static bool read_line(char **line)
{
    char *buffer;
    size_t length;

    if (line == NULL) {
        return false;
    }

    *line = NULL;

    buffer = malloc((size_t)MAX_INPUT_LENGTH + 2U);
    if (buffer == NULL) {
        return false;
    }

    if (fgets(buffer, MAX_INPUT_LENGTH + 2, stdin) == NULL) {
        free(buffer);
        return false;
    }

    for (length = 0; length <= MAX_INPUT_LENGTH; ++length) {
        if (buffer[length] == '\n') {
            buffer[length] = '\0';
            *line = buffer;
            return true;
        }

        if (buffer[length] == '\0') {
            if (feof(stdin) && length <= MAX_INPUT_LENGTH) {
                *line = buffer;
                return true;
            }

            free(buffer);
            return false;
        }
    }

    discard_line();
    free(buffer);
    return false;
}

int main(void)
{
    char *input = NULL;
    char *end = NULL;
    uintmax_t value;

    if (!read_line(&input)) {
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || value > UINT64_MAX) {
        free(input);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    puts(is_perfect_square((uint64_t)value) ? "Yes" : "No");

    free(input);
    return EXIT_SUCCESS;
}