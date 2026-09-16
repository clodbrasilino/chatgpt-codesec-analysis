#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int decimal_to_octal(uint64_t value, char *output, size_t output_size)
{
    char reversed[23];
    size_t length = 0;

    if (output == NULL || output_size == 0) {
        return -1;
    }

    do {
        reversed[length++] = (char)('0' + (value % 8U));
        value /= 8U;
    } while (value != 0U);

    if (length + 1U > output_size) {
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
    uint64_t decimal;
    char octal[23];

    printf("Enter a non-negative decimal number: ");

    if (scanf("%" SCNu64, &decimal) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (decimal_to_octal(decimal, octal, sizeof(octal)) != 0) {
        fprintf(stderr, "Conversion failed.\n");
        return EXIT_FAILURE;
    }

    printf("Octal: %s\n", octal);
    return EXIT_SUCCESS;
}