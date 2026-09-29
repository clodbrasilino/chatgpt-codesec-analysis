#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static void decimal_to_binary(unsigned long long value, char *buffer, size_t size)
{
    size_t index = size - 1U;

    buffer[index] = '\0';

    do {
        buffer[--index] = (char)('0' + (value & 1ULL));
        value >>= 1U;
    } while (value != 0ULL);

    size_t output_index = 0U;
    while (buffer[index] != '\0') {
        buffer[output_index++] = buffer[index++];
    }
    buffer[output_index] = '\0';
}

int main(void)
{
    char input[128];
    char binary[sizeof(unsigned long long) * CHAR_BIT + 1U];
    char *end = NULL;
    unsigned long long value;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    decimal_to_binary(value, binary, sizeof binary);

    if (printf("%s\n", binary) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}