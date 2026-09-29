#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 128

static bool is_prime(int value)
{
    if (value < 2) {
        return false;
    }

    if (value == 2) {
        return true;
    }

    if (value % 2 == 0) {
        return false;
    }

    for (int divisor = 3; divisor <= value / divisor; divisor += 2) {
        if (value % divisor == 0) {
            return false;
        }
    }

    return true;
}

static bool read_line(char *buffer, size_t size)
{
    if (buffer == NULL || size < 2) {
        return false;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return false;
    }

    size_t length = 0;
    while (length < size && buffer[length] != '\0' &&
           buffer[length] != '\n') {
        ++length;
    }

    if (length < size && buffer[length] == '\n') {
        buffer[length] = '\0';
        return true;
    }

    if (length < size && buffer[length] == '\0' && feof(stdin)) {
        return true;
    }

    int ch;
    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    return false;
}

int main(void)
{
    char *input = malloc(INPUT_SIZE);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    if (!read_line(input, INPUT_SIZE)) {
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    long value = strtol(input, &end, 10);

    if (errno == ERANGE || end == input ||
        value < INT_MIN || value > INT_MAX) {
        free(input);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    int result = printf("%s\n",
                        is_prime((int)value) ? "prime" : "not prime");

    free(input);

    return result < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}