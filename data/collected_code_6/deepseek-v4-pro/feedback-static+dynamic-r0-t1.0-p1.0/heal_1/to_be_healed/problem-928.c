#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void convert_date_format(const char *input, char *output) {
    if (input == NULL || output == NULL) {
        return;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(input) != 10) {
        output[0] = '\0';
        return;
    }
    
    if (input[4] != '-' || input[7] != '-') {
        output[0] = '\0';
        return;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(output, input + 8, 2);
    output[2] = '-';
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(output + 3, input + 5, 2);
    output[5] = '-';
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(output + 6, input, 4);
    output[10] = '\0';
}

int main(void) {
    const char *input_date = "2023-12-25";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output_date[11];
    
    convert_date_format(input_date, output_date);
    
    if (output_date[0] != '\0') {
        printf("%s\n", output_date);
    } else {
        printf("Invalid date format\n");
    }
    
    return 0;
}