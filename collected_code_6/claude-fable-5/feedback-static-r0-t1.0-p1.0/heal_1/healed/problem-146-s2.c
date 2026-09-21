#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

long ascii_sum(const char *str, size_t max_len)
{
    long sum = 0;
    size_t i;
    size_t len;

    if (str == NULL) {
        return -1;
    }

    len = strnlen(str, max_len);
    for (i = 0; i < len; i++) {
        sum += (long)(unsigned char)str[i];
    }

    return sum;
}

int main(void)
{
    char buffer[BUFFER_SIZE];
    long result;
    size_t len;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    result = ascii_sum(buffer, sizeof(buffer));
    if (result < 0) {
        fprintf(stderr, "Invalid string\n");
        return EXIT_FAILURE;
    }

    printf("Sum of ASCII values: %ld\n", result);

    return EXIT_SUCCESS;
}