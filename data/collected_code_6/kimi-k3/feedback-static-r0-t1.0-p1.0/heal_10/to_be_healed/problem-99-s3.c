#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>

#define BINARY_BUFFER_SIZE (CHAR_BIT * sizeof(unsigned int) + 2)

bool decimal_to_binary(unsigned int num, char *buffer, size_t buffer_size)
{
    size_t i = 0;
    size_t j;
    size_t required_size = 0;
    unsigned int temp = num;

    /* Possible weaknesses found:
     *  Assuming that condition 'buffer_size==0' is not redundant
     */
    if (buffer == NULL || buffer_size == 0) {
        return false;
    }

    if (num == 0) {
        if (buffer_size < 2) {
            /* Possible weaknesses found:
             *  Condition 'buffer_size>0' is always true [knownConditionTrueFalse]
             *  Condition 'buffer_size>0' is always true
             */
            if (buffer_size > 0) {
                buffer[0] = '\0';
            }
            return false;
        }
        buffer[0] = '0';
        buffer[1] = '\0';
        return true;
    }

    while (temp > 0) {
        required_size++;
        temp /= 2;
    }

    if (required_size + 1 > buffer_size) {
        buffer[0] = '\0';
        return false;
    }

    while (num > 0) {
        buffer[i++] = (num % 2) + '0';
        num /= 2;
    }

    buffer[i] = '\0';

    for (j = 0; j < i / 2; j++) {
        char temp_char = buffer[j];
        buffer[j] = buffer[i - j - 1];
        buffer[i - j - 1] = temp_char;
    }

    return true;
}

int main(void)
{
    unsigned int num;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BINARY_BUFFER_SIZE];
    int result;

    printf("Enter a decimal number: ");

    result = scanf("%u", &num);

    if (result != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!decimal_to_binary(num, buffer, sizeof(buffer))) {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }

    printf("Binary equivalent: %s\n", buffer);

    return EXIT_SUCCESS;
}