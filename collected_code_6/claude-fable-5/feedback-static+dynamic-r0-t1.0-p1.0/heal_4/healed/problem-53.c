#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

bool first_last_equal(const char *str, size_t max_len)
{
    size_t len;

    if (str == NULL || max_len == 0) {
        return false;
    }

    len = strnlen(str, max_len);

    if (len == 0 || len == max_len) {
        return false;
    }

    return str[0] == str[len - 1];
}

int main(void)
{
    char *buffer;
    size_t len;

    buffer = calloc(BUFFER_SIZE, sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter a string: ");
    fflush(stdout);

    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    buffer[BUFFER_SIZE - 1] = '\0';

    len = strnlen(buffer, BUFFER_SIZE);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    if (first_last_equal(buffer, BUFFER_SIZE)) {
        printf("The first and last characters are equal.\n");
    } else {
        printf("The first and last characters are not equal.\n");
    }

    free(buffer);
    return EXIT_SUCCESS;
}