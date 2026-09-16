#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int count_odd_rotations(const char *binary, size_t *count)
{
    size_t length;
    size_t ones = 0U;

    if (binary == NULL || count == NULL) {
        return -1;
    }

    length = strlen(binary);
    if (length == 0U) {
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

int main(int argc, const char *const argv[])
{
    size_t count;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <binary-string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (count_odd_rotations(argv[1], &count) != 0) {
        fprintf(stderr, "Error: input must be a nonempty binary string.\n");
        return EXIT_FAILURE;
    }

    printf("%zu\n", count);
    return EXIT_SUCCESS;
}