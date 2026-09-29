#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

static int print_binary(unsigned long long value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary[sizeof(value) * CHAR_BIT + 1U];
    size_t position = sizeof(binary);

    binary[--position] = '\0';

    do {
        if (position == 0U) {
            return -1;
        }

        binary[--position] = (char)('0' + (value & 1ULL));
        value >>= 1U;
    } while (value != 0ULL);

    return printf("%s\n", &binary[position]) < 0 ? -1 : 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *start;
    char *end;
    unsigned long long value;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    size_t length = 0U;

    while (length < sizeof(input) && input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length == sizeof(input)) {
        return EXIT_FAILURE;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (!feof(stdin)) {
        int ch;

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        }

        return EXIT_FAILURE;
    }

    start = input;

    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
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

    return print_binary(value) == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}