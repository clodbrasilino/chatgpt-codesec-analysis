#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

void convert_date_format(const char *input, char *output, size_t output_size) {
    if (input == NULL || output == NULL || output_size < 11) {
        return;
    }

    size_t input_len = strnlen(input, output_size);
    
    if (input_len != 10) {
        output[0] = '\0';
        return;
    }

    if (input[4] != '-' || input[7] != '-') {
        output[0] = '\0';
        return;
    }

    for (size_t i = 0; i < 4; i++) {
        if (input[i] < '0' || input[i] > '9') {
            output[0] = '\0';
            return;
        }
    }
    for (size_t i = 5; i < 7; i++) {
        if (input[i] < '0' || input[i] > '9') {
            output[0] = '\0';
            return;
        }
    }
    for (size_t i = 8; i < 10; i++) {
        if (input[i] < '0' || input[i] > '9') {
            output[0] = '\0';
            return;
        }
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp[11];
    temp[0] = input[8];
    temp[1] = input[9];
    temp[2] = '-';
    temp[3] = input[5];
    temp[4] = input[6];
    temp[5] = '-';
    temp[6] = input[0];
    temp[7] = input[1];
    temp[8] = input[2];
    temp[9] = input[3];
    temp[10] = '\0';

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(output, temp, output_size - 1);
    output[output_size - 1] = '\0';
}

int main(void) {
    const char *input_date = "2023-12-25";
    char *output_date = calloc(11, sizeof(char));

    if (output_date == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    convert_date_format(input_date, output_date, 11);

    if (output_date[0] != '\0') {
        printf("%s\n", output_date);
    } else {
        printf("Invalid date format\n");
    }

    free(output_date);
    return 0;
}