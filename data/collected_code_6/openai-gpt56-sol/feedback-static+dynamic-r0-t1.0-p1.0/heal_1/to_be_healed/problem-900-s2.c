#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool starts_with_number(const char *string, long number)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char prefix[64];
    int length;

    if (string == NULL || number < 0) {
        return false;
    }

    length = snprintf(prefix, sizeof(prefix), "%ld", number);
    if (length < 0 || (size_t)length >= sizeof(prefix)) {
        return false;
    }

    for (int i = 0; i < length; ++i) {
        if (string[i] == '\0' || string[i] != prefix[i]) {
            return false;
        }
    }

    return true;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *end = NULL;
    long number;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number> <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtol(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' || number < 0) {
        fprintf(stderr, "Invalid non-negative number\n");
        return EXIT_FAILURE;
    }

    if (starts_with_number(argv[2], number)) {
        puts("The string starts with the specified number.");
    } else {
        puts("The string does not start with the specified number.");
    }

    return EXIT_SUCCESS;
}