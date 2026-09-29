#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

#define INPUT_SIZE 1024

char find_first_repeated(const char *str)
{
    if (str == NULL || str[0] == '\0')
        return '\0';

    int seen[UCHAR_MAX + 1] = {0};
    size_t i;

    for (i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        if (seen[c])
            return (char)c;
        seen[c] = 1;
    }

    return '\0';
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_SIZE];
    char result;
    size_t len;

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    len = strcspn(input, "\n");

    if (len == sizeof(input) - 1 && input[len] != '\n') {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF)
            ;
        if (ferror(stdin)) {
            fprintf(stderr, "Error reading input\n");
            return 1;
        }
    }

    input[len] = '\0';

    result = find_first_repeated(input);

    if (result != '\0')
        printf("First repeated character: %c\n", result);
    else
        printf("No repeated character found\n");

    return 0;
}