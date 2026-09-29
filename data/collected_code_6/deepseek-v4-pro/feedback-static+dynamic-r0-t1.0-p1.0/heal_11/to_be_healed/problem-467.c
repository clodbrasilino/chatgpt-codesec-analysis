#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

#define BUFFER_SIZE 64

void decimal_to_octal(unsigned int decimal, char *octal, size_t size) {
    size_t index = 0;
    
    if (size == 0) {
        return;
    }
    
    if (decimal == 0) {
        if (size < 2) {
            octal[0] = '\0';
            return;
        }
        octal[0] = '0';
        octal[1] = '\0';
        return;
    }
    
    while (decimal > 0 && index < size - 1) {
        octal[index++] = (decimal & 7) + '0';
        decimal >>= 3;
    }
    octal[index] = '\0';
    
    for (size_t i = 0; i < index / 2; i++) {
        char temp = octal[i];
        octal[i] = octal[index - 1 - i];
        octal[index - 1 - i] = temp;
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[BUFFER_SIZE];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char octal[BUFFER_SIZE];
    unsigned long value;
    char *endptr;
    size_t input_len;
    /* Possible weaknesses found:
     *  Variable 'c' is not assigned a value. [unassignedVariable]
     */
    int c;
    
    printf("Enter a decimal number: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Input error\n");
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_len = strlen(input);
    if (input_len > 0 && input[input_len - 1] == '\n') {
        input[input_len - 1] = '\0';
        input_len--;
    } else if (input_len == sizeof(input) - 1 && input[input_len - 1] != '\n') {
        int ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
    }
    
    if (input_len == 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    value = strtoul(input, &endptr, 10);
    
    if (errno == ERANGE || *endptr != '\0' || endptr == input) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (value > UINT_MAX) {
        fprintf(stderr, "Number too large\n");
        return EXIT_FAILURE;
    }
    
    decimal_to_octal((unsigned int)value, octal, sizeof(octal));
    printf("Octal: %s\n", octal);
    
    (void)c;
    
    return EXIT_SUCCESS;
}