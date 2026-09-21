#include <stdio.h>
#include <string.h>

char sum_of_chars(const char *str)
{
    unsigned long sum = 0UL;
    size_t i;
    size_t len;

    if (str == NULL) {
        return '\0';
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);

    for (i = 0U; i < len; i++) {
        sum += (unsigned long)(unsigned char)str[i];
    }

    return (char)(((sum - (unsigned long)'a') % 26UL) + (unsigned long)'a');
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char result;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    if (buffer[0] == '\0') {
        fprintf(stderr, "Empty input\n");
        return 1;
    }

    result = sum_of_chars(buffer);

    if (result == '\0') {
        fprintf(stderr, "Invalid string\n");
        return 1;
    }

    if (printf("Resulting character: %c\n", result) < 0) {
        return 1;
    }

    return 0;
}