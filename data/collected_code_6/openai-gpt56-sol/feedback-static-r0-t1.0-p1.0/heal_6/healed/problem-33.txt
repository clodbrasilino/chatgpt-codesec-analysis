#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static int decimal_to_binary(unsigned long long value, char *buffer, size_t size)
{
    char temporary[sizeof value * CHAR_BIT];
    size_t length = 0;

    do {
        temporary[length++] = (char)('0' + (value & 1ULL));
        value >>= 1;
    } while (value != 0);

    if (buffer == NULL || size <= length) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        buffer[i] = temporary[length - i - 1];
    }

    buffer[length] = '\0';
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    char *start;
    char *end;
    unsigned long long value;
    ssize_t length;
    size_t binary_size = sizeof value * CHAR_BIT + 1;
    char *binary = malloc(binary_size);

    if (binary == NULL) {
        return EXIT_FAILURE;
    }

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(binary);
        free(input);
        return EXIT_FAILURE;
    }

    while (length > 0 &&
           (input[length - 1] == '\n' || input[length - 1] == '\r')) {
        input[--length] = '\0';
    }

    start = input;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        free(binary);
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start) {
        free(binary);
        free(input);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' ||
        !decimal_to_binary(value, binary, binary_size)) {
        free(binary);
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%s\n", binary) < 0) {
        free(binary);
        return EXIT_FAILURE;
    }

    free(binary);
    return EXIT_SUCCESS;
}