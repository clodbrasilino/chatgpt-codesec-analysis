#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define LOOKUP_SIZE ((size_t)UCHAR_MAX + 1u)
#define BUFFER_SIZE 1024

char find_first_repeated(const char *str, size_t str_size)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char seen[LOOKUP_SIZE] = {0};
    size_t i;

    if (str == NULL || str_size == 0) {
        return '\0';
    }

    for (i = 0; i < str_size && str[i] != '\0'; i++) {
        size_t index = (size_t)(unsigned char)str[i];

        if (index >= (size_t)sizeof(seen)) {
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
    char buffer[BUFFER_SIZE] = {0};
    size_t len;
    char result;

    printf("Enter a string: ");

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input\n");
        return EXIT_FAILURE;
    }

    len = strcspn(buffer, "\n");

    if (buffer[len] == '\n') {
        buffer[len] = '\0';
    } else {
        int ch;

        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
            ;
        }
    }

    result = find_first_repeated(buffer, len);

    if (result != '\0') {
        printf("First repeated character: %c\n", result);
    } else {
        printf("No repeated character found\n");
    }

    return EXIT_SUCCESS;
}