#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 64

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
static char buffer[BUFFER_SIZE];

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
     */
    strncpy(buffer, "Hello, world!", sizeof(buffer) - 1U);
    buffer[sizeof(buffer) - 1U] = '\0';
    printf("%s\n", buffer);
    return 0;
}