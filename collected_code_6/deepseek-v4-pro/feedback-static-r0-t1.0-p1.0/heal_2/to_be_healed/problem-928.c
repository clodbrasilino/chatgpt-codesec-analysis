#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void convert_date_format(const char *input, char *output, size_t output_size) {
    if (input == NULL || output == NULL || output_size < 11) {
        return;
    }
    
    if (input[0] == '\0') {
        output[0] = '\0';
        return;
    }
    
    size_t input_len = strnlen(input, 11);
    if (input_len != 10) {
        output[0] = '\0';
        return;
    }
    
    if (input[4] != '-' || input[7] != '-') {
        output[0] = '\0';
        return;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(output, input + 8, 2);
    output[2] = '-';
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(output + 3, input + 5, 2);
    output[5] = '-';
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(output + 6, input, 4);
    output[10] = '\0';
}

int main(void) {
    const char *input_date = "2023-12-25";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output_date[11];
    
    convert_date_format(input_date, output_date, sizeof(output_date));
    
    if (output_date[0] != '\0') {
        printf("%s\n", output_date);
    } else {
        printf("Invalid date format\n");
    }
    
    return 0;
}