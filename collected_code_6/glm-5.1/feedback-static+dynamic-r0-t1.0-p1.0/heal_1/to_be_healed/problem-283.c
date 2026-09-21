#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_digit_frequency(const char *input) {
    size_t len;
    size_t i;
    int counts[10] = {0};
    /* Possible weaknesses found:
     *  The scope of the variable 'digit' can be reduced. [variableScope]
     */
    int digit;

    if (input == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    if (len == 0) {
        return 0;
    }

    for (i = 0; i < len; i++) {
        if (input[i] < '0' || input[i] > '9') {
            return 0;
        }
        digit = input[i] - '0';
        counts[digit]++;
        if (counts[digit] > digit) {
            return 0;
        }
    }

    return 1;
}

int main(int argc, char *argv[]) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];
    int result;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    result = check_digit_frequency(buffer);

    printf("%d\n", result);

    return 0;
}