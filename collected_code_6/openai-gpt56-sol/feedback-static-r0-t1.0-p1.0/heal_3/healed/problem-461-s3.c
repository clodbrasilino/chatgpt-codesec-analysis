#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

size_t count_uppercase(const unsigned char *data, size_t length)
{
    size_t count = 0;

    if (data == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        if (isupper(data[i]) != 0) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    unsigned char *buffer = malloc(BUFSIZ);

    if (buffer == NULL) {
        fputs("Failed to allocate input buffer.\n", stderr);
        return EXIT_FAILURE;
    }

    size_t total = 0;
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, BUFSIZ, stdin)) != 0) {
        total += count_uppercase(buffer, bytes_read);
    }

    free(buffer);

    if (ferror(stdin) != 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", total) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}