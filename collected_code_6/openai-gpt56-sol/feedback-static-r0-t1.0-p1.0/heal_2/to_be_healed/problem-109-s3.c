#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
static int count_odd_rotations(const char binary[static 1], size_t *count)
{
    size_t ones = 0U;

    if (binary == NULL || count == NULL || binary[0] == '\0') {
        return -1;
    }

    for (const char *p = binary; *p != '\0'; ++p) {
        if (*p == '1') {
            ++ones;
        } else if (*p != '0') {
            return -1;
        }
    }

    *count = ones;
    return 0;
}

int main(int argc, char *const argv[])
{
    size_t count = 0U;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <binary-string>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    if (count_odd_rotations(argv[1], &count) != 0) {
        fputs("Error: input must be a nonempty binary string.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%zu\n", count);
    return EXIT_SUCCESS;
}