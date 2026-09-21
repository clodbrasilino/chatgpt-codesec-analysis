#include <stdio.h>

#define BUFFER_SIZE 64

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
static char buffer[BUFFER_SIZE];

int main(void)
{
    int result;

    result = snprintf(buffer, sizeof(buffer), "%s", "Hello, world!");
    if (result < 0 || (size_t)result >= sizeof(buffer)) {
        fprintf(stderr, "Error: string truncated or encoding failure\n");
        return 1;
    }

    printf("%s\n", buffer);
    return 0;
}