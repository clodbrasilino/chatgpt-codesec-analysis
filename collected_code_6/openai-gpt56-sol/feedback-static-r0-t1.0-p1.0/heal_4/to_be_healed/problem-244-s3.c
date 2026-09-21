#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int next_perfect_square(uint64_t number, uint64_t *result)
{
    uint64_t low = 0;
    uint64_t high = UINT32_MAX;
    uint64_t root = 0;

    if (result == NULL) {
        return 0;
    }

    while (low <= high) {
        uint64_t middle = low + (high - low) / 2;
        uint64_t square = middle * middle;

        if (square <= number) {
            root = middle;

            if (middle == UINT32_MAX) {
                break;
            }

            low = middle + 1;
        } else {
            if (middle == 0) {
                break;
            }

            high = middle - 1;
        }
    }

    if (root == UINT32_MAX) {
        return 0;
    }

    ++root;
    *result = root * root;
    return 1;
}

static int read_line(FILE *stream, char **buffer)
{
    size_t capacity = 128;
    size_t length = 0;
    char *line;
    int character;

    if (stream == NULL || buffer == NULL) {
        return 0;
    }

    line = malloc(capacity);
    if (line == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stream)) != EOF && character != '\n') {
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(line);
                return 0;
            }

            new_capacity = capacity * 2;
            resized = realloc(line, new_capacity);
            if (resized == NULL) {
                free(line);
                return 0;
            }

            line = resized;
            capacity = new_capacity;
        }

        line[length++] = (char)character;
    }

    if (character == EOF && ferror(stream)) {
        free(line);
        return 0;
    }

    line[length] = '\0';
    *buffer = line;
    return 1;
}

int main(void)
{
    char *input;
    char *end;
    char *start;
    uintmax_t value;
    uint64_t result;

    if (!read_line(stdin, &input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    start = input;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-' || *start == '+') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || value > UINT64_MAX) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!next_perfect_square((uint64_t)value, &result)) {
        free(input);
        fputs("No representable next perfect square\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}