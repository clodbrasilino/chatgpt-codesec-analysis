#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_INPUT_LENGTH 128

static int has_odd_divisor_count(unsigned long long number)
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

static int read_line(FILE *stream, char *buffer, size_t capacity)
{
    size_t length = 0;
    int ch;

    if (stream == NULL || buffer == NULL || capacity < 2) {
        errno = EINVAL;
        return -1;
    }

    while ((ch = fgetc(stream)) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            while (ch != '\n' && ch != EOF) {
                ch = fgetc(stream);
            }

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
            return -1;
        }

        if (length == 0) {
            errno = 0;
            return 0;
        }
    }

    buffer[length] = '\0';
    return 1;
}

int main(void)
{
    char input[MAX_INPUT_LENGTH];
    char *start;
    char *end;
    unsigned long long number;
    int status;

    errno = 0;
    status = read_line(stdin, input, sizeof(input));

    if (status <= 0) {
        if (status < 0 && errno == EOVERFLOW) {
            fputs("Input is too large.\n", stderr);
        } else {
            fputs("Failed to read input.\n", stderr);
        }
        return EXIT_FAILURE;
    }

    start = input;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-' || !isdigit((unsigned char)*start)) {
        fputs("Invalid positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    number = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start || number == 0) {
        fputs("Invalid positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(has_odd_divisor_count(number) ? "Odd" : "Even");
    return EXIT_SUCCESS;
}