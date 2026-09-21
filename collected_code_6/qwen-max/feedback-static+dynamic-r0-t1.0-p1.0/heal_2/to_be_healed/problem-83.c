#include <stdio.h>
#include <string.h>

char addChars(const char *str, size_t len) {
    int sum = 0;
    for (size_t i = 0; i < len; ++i) {
        sum += str[i];
    }
    return (char)(sum % 256);
}

int main() {
    const char *input = "Hello, World!";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    char result = addChars(input, strlen(input));
    printf("Resulting character: %c\n", result);
    return 0;
}