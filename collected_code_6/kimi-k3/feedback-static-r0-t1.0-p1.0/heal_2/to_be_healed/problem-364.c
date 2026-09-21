#include <stdio.h>
#include <string.h>

int countFlips(const char *str) {
    int flips1 = 0, flips2 = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);

    for (size_t i = 0; i < len; i++) {
        if (str[i] != (i % 2 == 0 ? '0' : '1')) {
            flips1++;
        } else {
            flips2++;
        }
    }

    return (flips1 < flips2) ? flips1 : flips2;
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[100];

    printf("Enter a binary string: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%99s", str) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    int result = countFlips(str);
    printf("Number of flips required: %d\n", result);

    return 0;
}