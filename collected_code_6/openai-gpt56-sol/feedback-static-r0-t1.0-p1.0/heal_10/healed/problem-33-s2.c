#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

static void print_binary(unsigned long long value)
{
    unsigned int bit = (unsigned int)(sizeof(value) * CHAR_BIT);
    int started = 0;

    while (bit > 0U) {
        unsigned long long mask;

        --bit;
        mask = 1ULL << bit;

        if ((value & mask) != 0ULL) {
            started = 1;
        }

        if (started || bit == 0U) {
            if (putchar((value & mask) != 0ULL ? '1' : '0') == EOF) {
                return;
            }
        }
    }

    (void)putchar('\n');
}

static int discard_line(void)
{
    int ch;

    do {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    return ch == '\n';
}

static int read_line(char *buffer, size_t size)
{
    size_t length;

    if (buffer == NULL || size < 2U || size > (size_t)INT_MAX) {
        return 0;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return 0;
    }

    length = 0U;
    while (buffer[length] != '\0' && buffer[length] != '\n') {
        ++length;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
        return 1;
    }

    if (length < size - 1U) {
        return 1;
    }

    return discard_line() ? 0 : feof(stdin) != 0;
}

int main(void)
{
    char input[128];
    char *start;
    char *end;
    unsigned long long value;

    if (!read_line(input, sizeof(input))) {
        return EXIT_FAILURE;
    }

    start = input;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start) {
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    print_binary(value);

    if (ferror(stdout)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}