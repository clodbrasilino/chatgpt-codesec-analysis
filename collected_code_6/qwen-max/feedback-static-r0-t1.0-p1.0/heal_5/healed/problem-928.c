#include <stdio.h>
#include <string.h>

void convertDateFormat(const char *input, char *output, size_t output_size) {
    if (input == NULL || output == NULL || output_size < 11 || strnlen(input, 11) != 10) return;
    snprintf(output, output_size, "%c%c-%c%c-%c%c%c%c", 
             input[8], input[9], input[5], input[6], input[0], input[1], input[2], input[3]);
}

int main() {
    const char input[11] = "2023-10-05";
    char output[11];
    convertDateFormat(input, output, sizeof(output));
    printf("%s\n", output);
    return 0;
}