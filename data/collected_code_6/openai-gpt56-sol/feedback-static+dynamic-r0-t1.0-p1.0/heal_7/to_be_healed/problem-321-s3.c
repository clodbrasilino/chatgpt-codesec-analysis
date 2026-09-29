#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <stdint.h>

static int is_demlo_number(unsigned long long number)
{
    unsigned long long low = 0;
    unsigned long long high =
        number < 0xffffffffULL ? number : 0xffffffffULL;

    while (low <= high) {
        unsigned long long root = low + (high - low) / 2;

        if (root != 0 && root > number / root) {
            high = root - 1;
        } else {
            unsigned long long square = root * root;

            if (square == number) {
                break;
            }

            low = root + 1;
        }
    }

    if (low > high) {
        return 0;
    }

    for (;;) {
        if (number % 10ULL != 1ULL) {
            return 0;
        }

        number /= 10ULL;

        if (number == 0ULL) {
            return 1;
        }

        while (number % 10ULL == 2ULL) {
            number /= 10ULL;
        }

        if (number == 0ULL) {
            return 0;
        }
    }
}

static int read_line(FILE *stream, char **line)
{
    char *buffer;
    size_t capacity = 128;
    size_t length = 0;

    if (stream == NULL || line == NULL) {
        return 0;
    }

    *line = NULL;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream) || length == 0) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length == capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

int main(void)
{
    char *input = NULL;
    char *start;
    char *end;
    unsigned long long number;

    if (!read_line(stdin, &input)) {
        return EXIT_FAILURE;
    }

    start = input;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-' || *start == '+') {
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start) {
        free(input);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    puts(is_demlo_number(number) ? "Demlo number" : "Not a Demlo number");

    free(input);
    return EXIT_SUCCESS;
}