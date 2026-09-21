#include <stdio.h>
#include <string.h>

void convertDateFormat(const char *input, char *output) {
    if (input == NULL || output == NULL || strlen(input) < 10) return;
    size_t input_len = strnlen(input, 11);
    if (input_len < 10) return;
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
    const char input[11] = "2023-10-05";
    char output[11] = {0};
    convertDateFormat(input, output);
    printf("%s\n", output);
    return 0;
}