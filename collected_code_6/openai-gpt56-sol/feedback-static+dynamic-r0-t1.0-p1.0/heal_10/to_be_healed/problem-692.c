#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 128U

static unsigned int last_two_digits_of_factorial(unsigned long long n)
{
    unsigned int result = 1U;

    if (n >= 10ULL) {
        return 0U;
    }

    for (unsigned int i = 2U; i <= (unsigned int)n; ++i) {
        result = (result * i) % 100U;
    }

    return result;
}

static int read_input(char *buffer, size_t size)
{
    if (buffer == NULL || size < 2U) {
        return -1;
    }

    size_t length = 0U;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length + 1U < size) {
            buffer[length++] = (char)ch;
        } else {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }

            buffer[0] = '\0';

            if (ch == EOF && ferror(stdin)) {
                return -1;
            }

            return 1;
        }
    }

    buffer[length] = '\0';

    if (ch == EOF && ferror(stdin)) {
        return -1;
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_SIZE];
    int read_status = read_input(input, sizeof input);

    if (read_status < 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (read_status > 0) {
        fputs("Input too long.\n", stderr);
        return EXIT_FAILURE;
    }

    char *start = input;

    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    unsigned long long n = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%02u\n", last_two_digits_of_factorial(n)) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}