#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>

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

static char *read_line(FILE *stream)
{
    size_t capacity = 32;
    size_t length = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        int ch = fgetc(stream);

        if (ch == '\n' || ch == EOF) {
            if (ch == EOF && (ferror(stream) || length == 0)) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (length == capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                errno = EOVERFLOW;
                return NULL;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input;
    char *end;
    unsigned long long number;

    input = read_line(stdin);
    if (input == NULL) {
        fputs(errno == EOVERFLOW
                  ? "Input is too large.\n"
                  : "Failed to read input.\n",
              stderr);
        return EXIT_FAILURE;
    }

    if (input[0] == '-' || !isdigit((unsigned char)input[0])) {
        free(input);
        fputs("Invalid positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    number = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input || number == 0) {
        free(input);
        fputs("Invalid positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);
    puts(has_odd_divisor_count(number) ? "Odd" : "Even");

    return EXIT_SUCCESS;
}