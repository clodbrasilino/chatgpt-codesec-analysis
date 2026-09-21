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
    
    memcpy(output, input + 8, 2);
    output[2] = '-';
    memcpy(output + 3, input + 5, 2);
    output[5] = '-';
    memcpy(output + 6, input, 4);
    output[10] = '\0';
}

int main(void) {
    const char *input_date = "2023-12-25";
    char output_date[11];
    
    convert_date_format(input_date, output_date, sizeof(output_date));
    
    if (output_date[0] != '\0') {
        printf("%s\n", output_date);
    } else {
        printf("Invalid date format\n");
    }
    
    return 0;
}