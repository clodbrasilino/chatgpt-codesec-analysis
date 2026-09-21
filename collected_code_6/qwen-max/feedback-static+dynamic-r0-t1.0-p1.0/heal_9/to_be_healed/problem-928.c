#include <stdio.h>
#include <string.h>

void convertDateFormat(const char *input, char *output, size_t output_size) {
    if (input == NULL || output == NULL || output_size < 12) return;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(input) != 10 || input[4] != '-' || input[7] != '-') return;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(output, &input[8], 2);
    output[2] = '-';
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(&output[3], &input[5], 2);
    output[5] = '-';
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(&output[6], input, 4);
    output[10] = '\0';
}

int main() {
    const char input[] = "2023-10-05";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[12];
    convertDateFormat(input, output, sizeof(output));
    printf("%s\n", output);
    return 0;
}