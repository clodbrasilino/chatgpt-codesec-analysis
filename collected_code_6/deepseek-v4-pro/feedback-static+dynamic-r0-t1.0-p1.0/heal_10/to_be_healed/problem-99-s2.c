#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

void decimal_to_binary(int n, char *binary, size_t size, int *length) {
    size_t index = 0;
    
    if (size == 0) {
        if (length) *length = 0;
        return;
    }
    
    if (n == 0) {
        if (index < size - 1) {
            binary[index++] = '0';
        }
    } else {
        unsigned int un = (unsigned int)n;
        size_t bits_needed = 0;
        unsigned int temp_un = un;
        while (temp_un > 0) {
            bits_needed++;
            temp_un >>= 1;
        }
        
        size_t max_bits = size - 1;
        if (bits_needed > max_bits) {
            bits_needed = max_bits;
        }
        
        char *temp = (char *)malloc(bits_needed + 1);
        if (temp == NULL) {
            if (length) *length = 0;
            return;
        }
        
        temp[bits_needed] = '\0';
        size_t write_index = bits_needed;
        
        while (un > 0 && write_index > 0) {
            temp[--write_index] = (un & 1) + '0';
            un >>= 1;
        }
        
        while (write_index > 0) {
            temp[--write_index] = '0';
        }
        
        size_t copy_index = 0;
        while (copy_index < bits_needed && index < size - 1) {
            binary[index++] = temp[copy_index++];
        }
        
        free(temp);
    }
    
    if (index < size) {
        binary[index] = '\0';
    } else {
        binary[size - 1] = '\0';
        index = size - 1;
    }
    
    if (length) *length = (int)index;
}

int main(void) {
    int decimal;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary[33];
    int length = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_buffer[32];
    /* Possible weaknesses found:
     *  The scope of the variable 'c' can be reduced. [variableScope]
     */
    int c;
    size_t input_len;
    
    printf("Enter a decimal number: ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        printf("Invalid input\n");
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_len = strlen(input_buffer);
    if (input_len > 0 && input_buffer[input_len - 1] != '\n') {
        if (input_len == sizeof(input_buffer) - 1) {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF);
        }
        printf("Input too long\n");
        return EXIT_FAILURE;
    }
    
    input_buffer[strcspn(input_buffer, "\n")] = '\0';
    
    char *endptr;
    errno = 0;
    long val = strtol(input_buffer, &endptr, 10);
    
    if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
        printf("Number out of range\n");
        return EXIT_FAILURE;
    }
    
    if (endptr == input_buffer || *endptr != '\0') {
        printf("Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (val < 0) {
        printf("Please enter a non-negative integer\n");
        return EXIT_FAILURE;
    }
    
    decimal = (int)val;
    
    decimal_to_binary(decimal, binary, sizeof(binary), &length);
    
    printf("Binary equivalent: %s\n", binary);
    
    return EXIT_SUCCESS;
}