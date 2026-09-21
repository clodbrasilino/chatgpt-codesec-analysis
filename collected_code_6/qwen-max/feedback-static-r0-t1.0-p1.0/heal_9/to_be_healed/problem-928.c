#include <stdio.h>
#include <string.h>

void convertDateFormat(const char *input, char *output, size_t output_size) {
    if (input == NULL || output == NULL || output_size < 11 || strnlen(input, 11) != 10) return;
    snprintf(output, output_size, "%c%c-%c%c-%c%c%c%c", 
             input[8], input[9], input[5], input[6], input[0], input[1], input[2], input[3]);
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