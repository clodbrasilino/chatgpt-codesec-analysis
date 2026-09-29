#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    const char *nul = memchr(buffer, '\0', sizeof(buffer));

    if (nul == NULL)
    {
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    size_t length = (size_t)(nul - buffer);

    printf("Input length: %zu\n", length);

    return EXIT_SUCCESS;
}