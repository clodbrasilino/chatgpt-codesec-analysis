#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

void decimal_to_octal(int decimal, char *octal, size_t size) {
    int index = 0;
    
    if (size == 0) {
        return;
    }
    
    if (decimal == 0) {
        if (size < 2) {
            octal[0] = '\0';
            return;
        }
        octal[index++] = '0';
        octal[index] = '\0';
        return;
    }
    
    while (decimal > 0 && index < size - 1) {
        octal[index++] = (decimal % 8) + '0';
        decimal /= 8;
    }
    octal[index] = '\0';
    
    for (int i = 0; i < index / 2; i++) {
        char temp = octal[i];
        octal[i] = octal[index - 1 - i];
        octal[index - 1 - i] = temp;
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[64];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char octal[64];
    long value;
    char *endptr;
    
    printf("Enter a decimal number: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Input error\n");
        return EXIT_FAILURE;
    }
    
    input[strcspn(input, "\n")] = '\0';
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(input) == 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    value = strtol(input, &endptr, 10);
    
    if (errno == ERANGE || *endptr != '\0' || endptr == input) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (value < 0) {
        fprintf(stderr, "Negative numbers not supported\n");
        return EXIT_FAILURE;
    }
    
    if (value > INT_MAX) {
        fprintf(stderr, "Number too large\n");
        return EXIT_FAILURE;
    }
    
    decimal_to_octal((int)value, octal, sizeof(octal));
    printf("Octal: %s\n", octal);
    
    return EXIT_SUCCESS;
}