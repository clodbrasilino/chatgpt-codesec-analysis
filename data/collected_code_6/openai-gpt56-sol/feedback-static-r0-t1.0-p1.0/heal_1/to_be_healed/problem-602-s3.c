#include <limits.h>
#include <stddef.h>
#include <stdio.h>

int first_repeated_character(const char *string, unsigned char *result)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char seen[UCHAR_MAX + 1] = {0};

    if (string == NULL || result == NULL) {
        return -1;
    }

    for (size_t i = 0; string[i] != '\0'; ++i) {
        unsigned char character = (unsigned char)string[i];

        if (seen[character] != 0) {
            *result = character;
            return 1;
        }

        seen[character] = 1;
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    unsigned char repeated_character;

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fprintf(stderr, "Failed to read input.\n");
            return 1;
        }
        return 0;
    }

    int status = first_repeated_character(input, &repeated_character);

    if (status < 0) {
        fprintf(stderr, "Invalid argument.\n");
        return 1;
    }

    if (status == 1) {
        printf("%c\n", repeated_character);
    } else {
        printf("No repeated character found.\n");
    }

    return 0;
}