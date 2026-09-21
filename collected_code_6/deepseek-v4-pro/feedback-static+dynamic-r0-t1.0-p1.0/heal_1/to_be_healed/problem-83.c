#include <stdio.h>
#include <string.h>

char sum_characters(const char *str) {
    char sum = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++) {
        sum += str[i];
    }
    return sum;
}

int main(void) {
    const char *input = "Hello";
    char result = sum_characters(input);
    printf("Result: %d\n", result);
    return 0;
}