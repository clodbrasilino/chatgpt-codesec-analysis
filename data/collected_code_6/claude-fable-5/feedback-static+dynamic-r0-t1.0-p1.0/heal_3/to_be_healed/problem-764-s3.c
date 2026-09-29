#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 256

size_t count_numeric(const char *str)
{
    size_t count;
    size_t i;

    if (str == NULL) {
        return 0;
    }

    count = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if (isdigit((unsigned char)str[i])) {
            count++;
        }
    }

    return count;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    size_t result;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';
    buffer[strcspn(buffer, "\n")] = '\0';

    result = count_numeric(buffer);

    if (printf("Numeric characters: %zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}