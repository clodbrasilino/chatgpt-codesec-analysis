#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *to_lower_case(char *str)
{
    size_t i;

    if (str == NULL) {
        return NULL;
    }

    for (i = 0; str[i] != '\0'; i++) {
        str[i] = (char)tolower((unsigned char)str[i]);
    }

    return str;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *result;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    result = to_lower_case(buffer);
    if (result == NULL) {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}