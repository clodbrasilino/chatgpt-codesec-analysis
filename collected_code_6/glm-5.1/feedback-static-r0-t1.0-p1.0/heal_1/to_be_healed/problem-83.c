#include <stdio.h>
#include <stdlib.h>

char find_char(const char *str) {
    if (str == NULL) {
        return 0;
    }

    unsigned long long sum = 0;
    size_t i = 0;

    while (str[i] != '\0') {
        sum += (unsigned char)str[i];
        i++;
    }

    return (char)(sum % 256);
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 'input1' can be declared as pointer to const [constVariablePointer]
     */
    char *input1 = "abc";
    /* Possible weaknesses found:
     *  Variable 'input2' can be declared as pointer to const [constVariablePointer]
     */
    char *input2 = "hello world";
    /* Possible weaknesses found:
     *  Variable 'input3' can be declared as pointer to const [constVariablePointer]
     */
    char *input3 = "";

    char result1 = find_char(input1);
    char result2 = find_char(input2);
    char result3 = find_char(input3);

    printf("%d\n", result1);
    printf("%d\n", result2);
    printf("%d\n", result3);

    return 0;
}