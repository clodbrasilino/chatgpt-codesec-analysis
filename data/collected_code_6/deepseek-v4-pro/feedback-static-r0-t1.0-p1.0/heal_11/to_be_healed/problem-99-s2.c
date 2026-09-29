#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

void decimal_to_binary(int n, char *binary, size_t binary_size, int *length) {
    size_t index = 0;
    
    if (binary_size == 0) {
        *length = 0;
        return;
    }
    
    if (n == 0) {
        if (binary_size > 1) {
            binary[index++] = '0';
        }
    } else {
        while (n > 0 && index < binary_size - 1) {
            binary[index++] = (n % 2) + '0';
            n = n / 2;
        }
    }
    
    binary[index] = '\0';
    *length = (int)index;
    
    size_t start = 0;
    size_t end = index > 0 ? index - 1 : 0;
    while (start < end) {
        char temp = binary[start];
        binary[start] = binary[end];
        binary[end] = temp;
        start++;
        end--;
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[64];
    long decimal;
    char *endptr;
    
    printf("Enter a decimal number: ");
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input\n");
        return EXIT_FAILURE;
    }
    
    size_t input_len = strnlen(input, sizeof(input));
    if (input_len > 0 && input[input_len - 1] == '\n') {
        input[input_len - 1] = '\0';
        input_len--;
    } else if (input_len >= sizeof(input) - 1) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
            if (c == EOF) break;
        }
        printf("Input too long\n");
        return EXIT_FAILURE;
    }
    
    if (input_len == 0) {
        printf("Invalid input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    decimal = strtol(input, &endptr, 10);
    
    if (errno == ERANGE || decimal > INT_MAX || decimal < 0) {
        printf("Please enter a non-negative integer within valid range\n");
        return EXIT_FAILURE;
    }
    
    if (endptr == input || *endptr != '\0') {
        printf("Invalid input\n");
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary[33];
    int length = 0;
    
    memset(binary, 0, sizeof(binary));
    decimal_to_binary((int)decimal, binary, sizeof(binary), &length);
    
    printf("Binary equivalent: %s\n", binary);
    
    return EXIT_SUCCESS;
}