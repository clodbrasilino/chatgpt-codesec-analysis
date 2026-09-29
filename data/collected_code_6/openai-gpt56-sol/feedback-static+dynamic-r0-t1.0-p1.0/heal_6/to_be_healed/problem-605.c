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

    if (fgets(buffer, size, stdin) == NULL) {
        return false;
    }

    size_t length = 0;
    while (length < size && buffer[length] != '\0' &&
           buffer[length] != '\n') {
        ++length;
    }

    if (length == size) {
        return false;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
        return true;
    }

    if (feof(stdin)) {
        return true;
    }

    int ch;
    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    return false;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_SIZE];

    if (!read_line(input, sizeof input)) {
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    long value = strtol(input, &end, 10);

    if (errno == ERANGE || end == input ||
        value < INT_MIN || value > INT_MAX) {
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    if (printf("%s\n", is_prime((int)value) ? "prime" : "not prime") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}