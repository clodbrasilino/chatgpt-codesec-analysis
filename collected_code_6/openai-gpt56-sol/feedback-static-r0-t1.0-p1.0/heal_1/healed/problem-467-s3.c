#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define UINT64_OCTAL_DIGITS 22U
#define OCTAL_BUFFER_SIZE (UINT64_OCTAL_DIGITS + 1U)
#define INPUT_BUFFER_SIZE 128U

static int decimal_to_octal(uint64_t value, char *output, size_t output_size)
{
    char reversed[UINT64_OCTAL_DIGITS];
    size_t length = 0U;

    if (output == NULL || output_size == 0U) {
        return -1;
    }

    do {
        if (length >= sizeof(reversed)) {
            return -1;
        }

        reversed[length++] = (char)('0' + (value % UINT64_C(8)));
        value /= UINT64_C(8);
    } while (value != UINT64_C(0));

    if (length >= output_size) {
        return -1;
    }

    for (size_t i = 0U; i < length; ++i) {
        output[i] = reversed[length - i - 1U];
    }

    output[length] = '\0';
    return 0;
}

int main(void)
{
    char input[INPUT_BUFFER_SIZE];
    char octal[OCTAL_BUFFER_SIZE];
    uint64_t decimal;
    char extra;

    fputs("Enter a non-negative decimal number: ", stdout);
    fflush(stdout);

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (sscanf(input, " %" SCNu64 " %c", &decimal, &extra) != 1) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (decimal_to_octal(decimal, octal, sizeof(octal)) != 0) {
        fputs("Conversion failed.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Octal: %s\n", octal);
    return EXIT_SUCCESS;
}