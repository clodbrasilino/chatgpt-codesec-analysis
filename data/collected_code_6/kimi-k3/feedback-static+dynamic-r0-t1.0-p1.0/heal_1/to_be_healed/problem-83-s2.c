#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char add_all_characters(const char *str)
{
    int sum = 0;
    size_t i;
    size_t len;

    if (str == NULL) {
        return '\0';
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
    for (i = 0; i < len; i++) {
        sum += (unsigned char)str[i];
    }

    return (char)(sum % 256);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char result;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    result = add_all_characters(buffer);
    printf("Resulting character: %c (ASCII: %d)\n", 
           (result >= 32 && result <= 126) ? result : '.', 
           (unsigned char)result);

    return EXIT_SUCCESS;
}