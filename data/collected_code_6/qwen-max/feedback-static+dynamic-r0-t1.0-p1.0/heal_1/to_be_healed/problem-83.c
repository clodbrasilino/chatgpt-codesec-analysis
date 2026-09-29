#include <stdio.h>
#include <string.h>

char addChars(const char *str) {
    int sum = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    for (int i = 0; i < strlen(str); ++i) {
        sum += str[i];
    }
    return (char)(sum % 256);
}

int main() {
    const char *input = "Hello, World!";
    char result = addChars(input);
    printf("Resulting character: %c\n", result);
    return 0;
}