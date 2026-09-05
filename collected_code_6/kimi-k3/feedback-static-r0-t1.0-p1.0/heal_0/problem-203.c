#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

unsigned int hamming_distance(unsigned int x, unsigned int y)
{
    unsigned int xor_result = x ^ y;
    unsigned int distance = 0U;

    while (xor_result != 0U) {
        distance += xor_result & 1U;
        xor_result >>= 1U;
    }

    return distance;
}

int main(void)
{
    unsigned int a = 0U;
    unsigned int b = 0U;
    char input_buffer[64];
    char *end_ptr = NULL;
    unsigned long parsed_value = 0UL;

    printf("Enter first integer: ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_value = strtoul(input_buffer, &end_ptr, 10);
    if ((errno == ERANGE) || (parsed_value > UINT_MAX) || (end_ptr == input_buffer)) {
        fprintf(stderr, "Invalid input for first integer.\n");
        return EXIT_FAILURE;
    }
    a = (unsigned int)parsed_value;

    printf("Enter second integer: ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_value = strtoul(input_buffer, &end_ptr, 10);
    if ((errno == ERANGE) || (parsed_value > UINT_MAX) || (end_ptr == input_buffer)) {
        fprintf(stderr, "Invalid input for second integer.\n");
        return EXIT_FAILURE;
    }
    b = (unsigned int)parsed_value;

    printf("Hamming distance: %u\n", hamming_distance(a, b));

    return EXIT_SUCCESS;
}