#include <stdio.h>
#include <string.h>

char addChars(const char *str, size_t len) {
    int sum = 0;
    for (size_t i = 0; i < len; ++i) {
        sum += (unsigned char)str[i];
    }
    return (char)(sum % 256);
}

int main() {
    const char input[] = "Hello, World!";
    /* Possible weaknesses found:
     *  Assignment 'length=strlen(input)', assigned value is 13
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(input);

    /* Possible weaknesses found:
     *  Condition 'length>0' is always true [knownConditionTrueFalse]
     *  Condition 'length>0' is always true
     */
    if (length > 0 && input[length - 1] == '\0') {
        char result = addChars(input, length - 1);
        printf("Resulting character: %c\n", result);
    } else {
        fprintf(stderr, "Input string is not null-terminated.\n");
        return 1;
    }
    return 0;
}