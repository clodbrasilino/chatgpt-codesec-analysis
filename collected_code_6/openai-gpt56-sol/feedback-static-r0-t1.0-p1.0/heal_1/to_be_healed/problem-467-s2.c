#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int decimal_to_octal(uint64_t value, char *output, size_t output_size)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char reversed[23];
    size_t length = 0;

    if (output == NULL || output_size == 0) {
        return -1;
    }

    do {
        reversed[length++] = (char)('0' + (value % UINT64_C(8)));
        value /= UINT64_C(8);
    } while (value != 0);

    if (length + 1 > output_size) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        output[i] = reversed[length - i - 1];
    }

    output[length] = '\0';
    return 0;
}

int main(void)
{
    uint64_t decimal;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char octal[23];

    printf("Enter a non-negative decimal integer: ");

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
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