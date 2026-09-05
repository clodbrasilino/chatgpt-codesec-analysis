#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

void decimal_to_binary(unsigned int num, char *buffer, size_t buffer_size)
{
    size_t i = 0;
    size_t j;

    if (buffer_size == 0) {
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
    char buffer[33];
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