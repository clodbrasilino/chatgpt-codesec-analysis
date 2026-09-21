#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t count_characters(const char *str)
{
    size_t count = 0;

    if (str == NULL) {
        return 0;
    }

    while (str[count] != '\0') {
        count++;
    }

    return count;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    size_t length;

    printf("Enter a string: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    length = count_characters(buffer);

    printf("Total characters: %zu\n", length);

    return EXIT_SUCCESS;
}