#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

char add_all_characters(const char *str, size_t max_len)
{
    unsigned int sum = 0;
    size_t i;
    size_t len;

    if (str == NULL || max_len == 0) {
        return '\0';
    }

    len = strnlen(str, max_len);
    for (i = 0; i < len; i++) {
        sum = (sum + (unsigned char)str[i]) % 256;
    }

    return (char)sum;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[257];
    char result;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    result = add_all_characters(buffer, sizeof(buffer));
    printf("Resulting character: %c (ASCII: %d)\n", 
           (result >= 32 && result <= 126) ? result : '.', 
           (unsigned char)result);

    return EXIT_SUCCESS;
}