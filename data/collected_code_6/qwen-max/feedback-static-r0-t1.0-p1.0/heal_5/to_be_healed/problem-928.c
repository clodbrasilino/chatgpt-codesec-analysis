#include <stdio.h>
#include <string.h>

void convertDateFormat(const char *input, char *output, size_t output_size) {
    if (input == NULL || output == NULL || output_size < 11 || strnlen(input, 11) < 10) return;
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    const char input[11] = "2023-10-05";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[11] = {0};
    convertDateFormat(input, output, sizeof(output));
    printf("%s\n", output);
    return 0;
}