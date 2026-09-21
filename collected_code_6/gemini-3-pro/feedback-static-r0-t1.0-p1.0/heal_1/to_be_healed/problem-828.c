#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void countCharacters(const char *str, int *alphabets, int *digits, int *specialChars) {
    if (str == NULL || alphabets == NULL || digits == NULL || specialChars == NULL) {
        return;
    }

    *alphabets = 0;
    *digits = 0;
    *specialChars = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha((unsigned char)str[i])) {
            (*alphabets)++;
        } else if (isdigit((unsigned char)str[i])) {
            (*digits)++;
        } else if (!isspace((unsigned char)str[i])) {
            (*specialChars)++;
        }
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[256];
    int alphabets = 0;
    int digits = 0;
    int specialChars = 0;

    if (fgets(str, sizeof(str), stdin) != NULL) {
        countCharacters(str, &alphabets, &digits, &specialChars);
        printf("%d %d %d\n", alphabets, digits, specialChars);
    } else {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}