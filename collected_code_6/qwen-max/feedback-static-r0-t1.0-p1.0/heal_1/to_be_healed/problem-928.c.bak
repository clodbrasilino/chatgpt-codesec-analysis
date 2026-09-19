#include <stdio.h>
#include <string.h>

/* Possible weaknesses found:
 *  Parameter 'input' can be declared as pointer to const [constParameterPointer]
 */
void convertDateFormat(char *input, char *output) {
    if (input == NULL || output == NULL) return;
    output[0] = input[8];
    output[1] = input[9];
    output[2] = '-';
    output[3] = input[5];
    output[4] = input[6];
    output[5] = '-';
    output[6] = input[0];
    output[7] = input[1];
    output[8] = input[2];
    output[9] = input[3];
    output[10] = '\0';
}

int main() {
    char input[11] = "2023-10-05";
    char output[11];
    convertDateFormat(input, output);
    printf("%s\n", output);
    return 0;
}