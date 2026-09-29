#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

void convert_date_format(const char *input, char *output, size_t output_size) {
    if (input == NULL || output == NULL || output_size < 11) {
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

    memset(output, 0, output_size);
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

int main(void) {
    const char *input_date = "2023-12-25";
    char output_date[11];

    memset(output_date, 0, sizeof(output_date));
    convert_date_format(input_date, output_date, sizeof(output_date));

    if (output_date[0] != '\0') {
        printf("%s\n", output_date);
    } else {
        printf("Invalid date format\n");
    }

    return 0;
}