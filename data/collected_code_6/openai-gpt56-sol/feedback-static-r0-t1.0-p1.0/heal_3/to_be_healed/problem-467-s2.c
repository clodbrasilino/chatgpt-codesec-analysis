#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_BUFFER_SIZE 128U
#define OCTAL_BUFFER_SIZE 23U

static int decimal_to_octal(uint64_t value, char *output, size_t output_size)
{
    int result;

    if (output == NULL || output_size == 0U) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder snprintf: If format strings can be influenced by an attacker, they can be exploited, and note that sprintf variations do not always \0-terminate (CWE-134). Use a constant for the format specification. (risk 4, format)
     */
    result = snprintf(output, output_size, "%" PRIo64, value);
    if (result < 0 || (size_t)result >= output_size) {
        output[0] = '\0';
        return -1;
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_BUFFER_SIZE];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char octal[OCTAL_BUFFER_SIZE];
    char *end = NULL;
    uintmax_t parsed_value;

    fputs("Enter a non-negative decimal integer: ", stdout);
    fflush(stdout);

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (input[0] != '\0' && input[0] != '\n') {
        size_t length = 0U;

        while (length < sizeof(input) && input[length] != '\0' &&
               input[length] != '\n') {
            ++length;
        }

        if (length == sizeof(input) || input[length] != '\n') {
            int ch;

            do {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = getchar();
            } while (ch != '\n' && ch != EOF);

            fputs("Invalid input.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    parsed_value = strtoumax(input, &end, 10);

    if (end == input || errno == ERANGE || parsed_value > UINT64_MAX) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0' || input[0] == '-') {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (decimal_to_octal((uint64_t)parsed_value, octal, sizeof(octal)) != 0) {
        fputs("Conversion failed.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Octal: %s\n", octal);
    return EXIT_SUCCESS;
}