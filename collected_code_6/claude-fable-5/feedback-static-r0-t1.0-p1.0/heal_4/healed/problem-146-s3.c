#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

static size_t bounded_strlen(const char *str, size_t max_len)
{
    size_t i;

    for (i = 0; i < max_len; i++) {
        if (str[i] == '\0') {
            break;
        }
    }

    return i;
}

long ascii_sum(const char *str, size_t max_len)
{
    long sum = 0;
    size_t i;
    size_t len;

    if (str == NULL) {
        return -1;
    }

    len = bounded_strlen(str, max_len);
    for (i = 0; i < len; i++) {
        sum += (long)(unsigned char)str[i];
    }

    return sum;
}

int main(void)
{
    char *buffer;
    long result;
    size_t len;

    buffer = calloc(BUFFER_SIZE, sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter a string: ");

    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    buffer[BUFFER_SIZE - 1] = '\0';

    len = bounded_strlen(buffer, BUFFER_SIZE);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    result = ascii_sum(buffer, BUFFER_SIZE);
    if (result < 0) {
        fprintf(stderr, "Invalid string\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    printf("Total ASCII value: %ld\n", result);

    free(buffer);

    return EXIT_SUCCESS;
}