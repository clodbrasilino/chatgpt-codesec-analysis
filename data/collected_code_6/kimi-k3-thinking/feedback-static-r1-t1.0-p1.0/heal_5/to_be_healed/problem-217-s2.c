#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOOKUP_SIZE 256
#define BUFFER_SIZE 1024

char find_first_repeated(const char *str)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char seen[LOOKUP_SIZE] = {0};
    size_t i;

    if (str == NULL) {
        return '\0';
    }

    for (i = 0; i < (size_t)BUFFER_SIZE && str[i] != '\0'; i++) {
        size_t index = (size_t)(unsigned char)str[i];

        if (index >= sizeof(seen)) {
            continue;
        }

        if (seen[index] != 0) {
            return (char)(unsigned char)index;
        }

        seen[index] = 1;
    }

    return '\0';
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    size_t len;
    char result;

    printf("Enter a string: ");

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    len = strcspn(buffer, "\n");

    if (len < sizeof(buffer) && buffer[len] == '\n') {
        buffer[len] = '\0';
    } else {
        int ch;
        size_t discarded = 0;

        while (discarded < (size_t)BUFFER_SIZE &&
               /* Possible weaknesses found:
                * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                */
               (ch = getchar()) != '\n' && ch != EOF) {
            discarded++;
        }
    }

    result = find_first_repeated(buffer);

    if (result != '\0') {
        printf("First repeated character: %c\n", result);
    } else {
        printf("No repeated character found\n");
    }

    return EXIT_SUCCESS;
}