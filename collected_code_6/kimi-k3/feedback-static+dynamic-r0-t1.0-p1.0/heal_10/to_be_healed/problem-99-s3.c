#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdint.h>

void decimal_to_binary(unsigned int num, char *buffer, size_t buffer_size)
{
    size_t i = 0;
    size_t j;
    size_t required_size;

    if (buffer == NULL || buffer_size == 0) {
        return;
    }

    required_size = sizeof(unsigned int) * CHAR_BIT + 2;
    if (buffer_size < required_size) {
        buffer[0] = '\0';
        return;
    }

    if (num == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    while (num > 0 && i < buffer_size - 1) {
        buffer[i++] = (num % 2) + '0';
        num /= 2;
    }

    if (num > 0) {
        buffer[0] = '\0';
        return;
    }

    buffer[i] = '\0';

    for (j = 0; j < i / 2; j++) {
        char temp = buffer[j];
        buffer[j] = buffer[i - j - 1];
        buffer[i - j - 1] = temp;
    }
}

int main(void)
{
    unsigned int num;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[sizeof(unsigned int) * CHAR_BIT + 2];
    int result;

    printf("Enter a decimal number: ");

    result = scanf("%u", &num);

    if (result != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    decimal_to_binary(num, buffer, sizeof(buffer));

    if (buffer[0] == '\0') {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }

    printf("Binary equivalent: %s\n", buffer);

    return EXIT_SUCCESS;
}