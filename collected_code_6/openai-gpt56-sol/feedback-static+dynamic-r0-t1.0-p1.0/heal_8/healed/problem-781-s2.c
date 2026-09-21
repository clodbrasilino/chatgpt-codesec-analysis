#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <ctype.h>

#define MAX_INPUT_LENGTH 128

static int is_perfect_square(unsigned long long number)
{
    unsigned long long low = 1;
    unsigned long long high = number;

    while (low <= high) {
        unsigned long long mid = low + (high - low) / 2;
        unsigned long long quotient = number / mid;

        if (mid == quotient && number % mid == 0) {
            return 1;
        }

        if (mid < quotient) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return 0;
}

static int read_line(FILE *stream, char **line)
{
    char *buffer;
    size_t capacity = MAX_INPUT_LENGTH + 2;
    size_t length = 0;
    int ch;

    if (stream == NULL || line == NULL) {
        errno = EINVAL;
        return -1;
    }

    *line = NULL;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    while ((ch = fgetc(stream)) != '\n' && ch != EOF) {
        if (length >= MAX_INPUT_LENGTH) {
            do {
                ch = fgetc(stream);
            } while (ch != '\n' && ch != EOF);

            free(buffer);

            if (ch == EOF && ferror(stream)) {
                return -1;
            }

            errno = EOVERFLOW;
            return -1;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF) {
        if (ferror(stream)) {
            free(buffer);
            return -1;
        }

        if (length == 0) {
            free(buffer);
            return 0;
        }
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
    int status;

    errno = 0;
    status = read_line(stdin, &input);

    if (status <= 0) {
        fputs("Failed to read input.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    start = input;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-' ||
        !isdigit((unsigned char)*start)) {
        fputs("Invalid positive integer.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start || number == 0) {
        fputs("Invalid positive integer.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid positive integer.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    puts(is_perfect_square(number) ? "Odd" : "Even");

    free(input);
    return EXIT_SUCCESS;
}