#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool isUndulating(int num) {
    if (num < 100) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[15];
    if (snprintf(str, sizeof(str), "%d", num) < 0) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    
    if (str[0] == str[1]) {
        return false;
    }

    for (size_t i = 2; i < len; ++i) {
        if (str[i - 2] != str[i]) {
            return false;
        }
    }

    return true;
}

int main() {
    int input;
    
    if (scanf("%d", &input) != 1) {
        return EXIT_FAILURE;
    }

    if (isUndulating(input)) {
        printf("The number is undulating.\n");
    } else {
        printf("The number is not undulating.\n");
    }

    return EXIT_SUCCESS;
}