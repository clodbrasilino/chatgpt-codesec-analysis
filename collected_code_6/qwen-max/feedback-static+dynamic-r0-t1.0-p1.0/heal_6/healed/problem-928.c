#include <stdio.h>
#include <string.h>

void convertDateFormat(const char *input, char *output, size_t output_size) {
    if (input == NULL || output == NULL || output_size < 12) return;
    if (strlen(input) != 10 || strchr(input, '-') == NULL) return;
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
    const char input[] = "2023-10-05";
    char output[12];
    convertDateFormat(input, output, sizeof(output));
    printf("%s\n", output);
    return 0;
}