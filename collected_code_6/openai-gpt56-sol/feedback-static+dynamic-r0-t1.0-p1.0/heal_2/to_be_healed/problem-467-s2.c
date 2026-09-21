#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define OCTAL_BUFFER_SIZE ((sizeof(uint64_t) * 8U + 2U) / 3U + 1U)
#define INPUT_BUFFER_SIZE 128U

static int decimal_to_octal(uint64_t value, char *output, size_t output_size)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char reversed[OCTAL_BUFFER_SIZE];
    size_t length = 0;

    if (output == NULL || output_size == 0) {
        return -1;
    }

    do {
        if (length >= sizeof(reversed) - 1U) {
            return -1;
        }

        reversed[length++] = (char)('0' + (value % UINT64_C(8)));
        value /= UINT64_C(8);
    } while (value != 0);

    if (length >= output_size) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        output[i] = reversed[length - i - 1U];
    }

    output[length] = '\0';
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
    char *end;
    uintmax_t parsed;
    uint64_t decimal;

    printf("Enter a non-negative decimal integer: ");
    fflush(stdout);

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(input, &end, 10);

    if (end == input || errno == ERANGE || parsed > UINT64_MAX) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n' ||
           *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    decimal = (uint64_t)parsed;

    if (decimal_to_octal(decimal, octal, sizeof(octal)) != 0) {
        fprintf(stderr, "Conversion failed.\n");
        return EXIT_FAILURE;
    }

    printf("Octal: %s\n", octal);
    return EXIT_SUCCESS;
}