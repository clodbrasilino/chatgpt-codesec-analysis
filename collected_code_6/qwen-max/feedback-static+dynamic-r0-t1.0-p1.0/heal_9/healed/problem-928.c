#include <stdio.h>
#include <string.h>

void convertDateFormat(const char *input, char *output, size_t output_size) {
    if (input == NULL || output == NULL || output_size < 12) return;
    if (strlen(input) != 10 || input[4] != '-' || input[7] != '-') return;
    if (memcpy(output, &input[8], 2) != output) return;
    output[2] = '-';
    if (memcpy(&output[3], &input[5], 2) != &output[3]) return;
    output[5] = '-';
    if (memcpy(&output[6], input, 4) != &output[6]) return;
    output[10] = '\0';
}

int main() {
    const char input[] = "2023-10-05";
    char output[12];
    convertDateFormat(input, output, sizeof(output));
    printf("%s\n", output);
    return 0;
}