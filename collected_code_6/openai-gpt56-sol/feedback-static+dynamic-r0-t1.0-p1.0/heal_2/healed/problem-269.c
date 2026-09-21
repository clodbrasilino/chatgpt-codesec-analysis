#include <stdio.h>
#include <stdlib.h>

static int ascii_value(unsigned char character)
{
    return (int)character;
}

int main(void)
{
    unsigned char input_buffer[1];
    size_t bytes_read = fread(input_buffer, sizeof(input_buffer[0]), 1, stdin);

    if (bytes_read != 1) {
        return EXIT_FAILURE;
    }

    if (printf("%u\n", (unsigned int)ascii_value(input_buffer[0])) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}