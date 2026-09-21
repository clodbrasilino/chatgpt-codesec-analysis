#include <stdio.h>
#include <string.h>
#include <limits.h>

char first_non_repeated_char(const char *str) {
    int count[UCHAR_MAX + 1] = {0};
    int first_pos[UCHAR_MAX + 1];
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    size_t i;

    for (i = 0; i <= UCHAR_MAX; i++) {
        first_pos[i] = -1;
    }

    for (i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        count[c]++;
        if (first_pos[c] == -1) {
            first_pos[c] = (int)i;
        }
    }

    int min_pos = INT_MAX;
    for (i = 0; i <= UCHAR_MAX; i++) {
        if (count[i] == 1 && first_pos[i] < min_pos) {
            min_pos = first_pos[i];
        }
    }

    if (min_pos != INT_MAX) {
        return str[min_pos];
    }

    return '\0';
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    input[strcspn(input, "\n")] = '\0';

    char result = first_non_repeated_char(input);

    if (result != '\0') {
        printf("First non-repeated character: %c\n", result);
    } else {
        printf("No non-repeated character found.\n");
    }

    return 0;
}