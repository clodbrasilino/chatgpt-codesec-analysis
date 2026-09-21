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
     *  Assignment 'length=sizeof(input)-1', assigned value is 13
     */
    size_t length = sizeof(input) - 1;

    /* Possible weaknesses found:
     *  Condition 'input[length-1]=='\0'' is always false
     *  Condition 'input[length-1]=='\0'' is always false [knownConditionTrueFalse]
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