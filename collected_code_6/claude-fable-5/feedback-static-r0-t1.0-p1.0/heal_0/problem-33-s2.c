#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void decimal_to_binary(unsigned int decimal, char *buffer, size_t buffer_size)
{
    size_t index = 0;

    if (buffer == NULL || buffer_size < 2) {
        return;
    }

    if (decimal == 0) {
        buffer[index++] = '0';
        buffer[index] = '\0';
        return;
    }

    while (decimal > 0 && index < buffer_size - 1) {
        buffer[index++] = (char)('0' + (decimal % 2U));
        decimal /= 2U;
    }
    buffer[index] = '\0';

    for (size_t i = 0, j = index - 1; i < j; i++, j--) {
        char temp = buffer[i];
        buffer[i] = buffer[j];
        buffer[j] = temp;
    }
}

int main(void)
{
    unsigned int number = 0;
    char binary[sizeof(unsigned int) * CHAR_BIT + 1];
    int result;

    printf("Enter a non-negative decimal number: ");
    result = scanf("%u", &number);

    if (result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    decimal_to_binary(number, binary, sizeof(binary));

    printf("Binary representation: %s\n", binary);

    return EXIT_SUCCESS;
}