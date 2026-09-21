#include <stdio.h>
#include <stdlib.h>

static int count_odd_rotations(const char *binary, size_t length, size_t *count)
{
    size_t ones = 0U;

    if (binary == NULL || count == NULL || length == 0U) {
        return -1;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (binary[i] == '1') {
            ++ones;
        } else if (binary[i] != '0') {
            return -1;
        }
    }

    *count = ones;
    return 0;
}

int main(int argc, char *argv[])
{
    size_t count;
    size_t length = 0U;
    const char *binary;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <binary-string>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    binary = argv[1];

    while (binary[length] != '\0') {
        ++length;
    }

    if (count_odd_rotations(binary, length, &count) != 0) {
        fputs("Error: input must be a nonempty binary string.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%zu\n", count);
    return EXIT_SUCCESS;
}