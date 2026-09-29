#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define BUFFER_SIZE 12

int decimal_to_octal(unsigned int decimal, char *buffer, size_t buffer_size) {
    /* Possible weaknesses found:
     *  Assuming condition 'buffer_size<2' is false
     */
    if (buffer == NULL || buffer_size < 2) {
        return -1;
    }
    
    int index = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp[BUFFER_SIZE];
    
    if (decimal == 0) {
        /* Possible weaknesses found:
         *  Condition 'buffer_size<2' is always false
         *  Condition 'buffer_size<2' is always false [knownConditionTrueFalse]
         */
        if (buffer_size < 2) {
            return -1;
        }
        buffer[0] = '0';
        buffer[1] = '\0';
        return 0;
    }
    
    while (decimal > 0 && index < BUFFER_SIZE - 1) {
        temp[index++] = (char)((decimal % 8) + '0');
        decimal /= 8;
    }
    
    if ((size_t)(index + 1) > buffer_size) {
        return -1;
    }
    
    int i;
    for (i = 0; i < index; i++) {
        buffer[i] = temp[index - 1 - i];
    }
    buffer[index] = '\0';
    
    return 0;
}

int main(void) {
    unsigned int decimal;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char octal_buffer[BUFFER_SIZE];
    
    printf("Enter a decimal number: ");
    
    if (scanf("%u", &decimal) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (decimal_to_octal(decimal, octal_buffer, sizeof(octal_buffer)) != 0) {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }
    
    printf("Octal: %s\n", octal_buffer);
    
    return EXIT_SUCCESS;
}