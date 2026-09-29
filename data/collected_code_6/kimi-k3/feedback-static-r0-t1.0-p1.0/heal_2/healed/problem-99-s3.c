#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

void decimal_to_binary(unsigned int num, char *buffer, size_t buffer_size)
{
    size_t i = 0;
    size_t j;
    size_t required_size = 0;
    unsigned int temp = num;

    if (buffer == NULL || buffer_size == 0) {
        return;
    }

    if (num == 0) {
        if (buffer_size < 2) {
            buffer[0] = '\0';
            return;
        }
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    while (temp > 0) {
        required_size++;
        temp /= 2;
    }

    if (required_size + 1 > buffer_size) {
        buffer[0] = '\0';
        return;
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
}

int main(void)
{
    unsigned int num;
    char buffer[CHAR_BIT * sizeof(unsigned int) + 1];
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